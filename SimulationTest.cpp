//A temporary proof of concept on how simulations would work
//This functionality will eventually be added into MutableFuncDriver
//  By Danny Reilman <reilman@umich.edu>

#include "MutableFunctionSubject.h"
#include "MutationOptions.h"
#include "Generator.h"
#include "FunctionSupply.h"
#include "CppFunctorSupply.h"
#include "VariableDouble.h"
#include "EvaluateToDouble.h"
#include "SimpleDouble.h"
#include "FunctionEvaluator.h"
#include "FunctionEnum.h"

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <utility>
#include <time.h>      
#include <stdlib.h>   

using namespace std;

using mutableFuncObj = unique_ptr<MutableFuncs::EvaluateToDouble>;

static int BAIL_NUM = 5;


class Fibonacci
{
public:
	Fibonacci ()
	{
		//Populate array
		solutions[0] = 0;
		solutions[1] = 1;
		for(int i = 2; i < 110; ++i)
		{
			solutions[i] = solutions[i - 1] + solutions[i - 2];
		}
	}

	double operator()(vector<double>& variables)
	{
		double exact = variables[0];
		int lowerBound = (int)floor(exact);
		int upperBound = (int)ceil(exact);

		//Linearly interpolate between the integers
		double delta = exact - (double)lowerBound;
		return (delta) * solutions[upperBound]
				+ (1 - delta) * solutions[lowerBound];
	}
private:
	int solutions[110];
};

int main()
{
	srand(time(NULL));
	vector<unique_ptr<EvoAlg::Subject> > subjects;

	MutableFuncs::Generator toTestObjectGenerator;
	
	ifstream toFitBatch("ToFitBatch.txt");
	toTestObjectGenerator.Run(toFitBatch);
	toFitBatch.close();

    FunctionSupply toTestBatch(std::move(toTestObjectGenerator.CopyObject("fit")), -1000, 1000, 25);
	CppFunctorSupply<Fibonacci> toTestFib(Fibonacci(), 0, 100, 25, 1);

    MutableFuncs::MutationOptions opt;
	MutableFuncs::MutationOptions currentOpt;

    //Load from defaultMutationValues.txt
	ifstream valueReader("DefaultMutationValues.txt");
    
    MutableFuncs::MutationOptions::ReadInput(opt, valueReader);
	
    valueReader.close();

	currentOpt  = opt;
	
	int subjectCount;
	cout << "How many subjects?" << endl;
	cin >> subjectCount;

    for(int i = 0; i < subjectCount; ++i)
    {
        unique_ptr<EvoAlg::Subject> temp(new MutableFunctionSubject(&currentOpt, &toTestFib));
        subjects.push_back(std::move(temp));
    }
    
	bool running = true;
	int iters;
	int generation = 0;
	
	unique_ptr<EvoAlg::Subject> bestSoFar = subjects[0]->Clone();
	while(running)
	{
		cout << "Move forward how many iterations? (0 to run until completion)" << endl;
		cin >> iters;
		
		bool stopOnSlowdown = false;
		if(iters == 0)
		{
			stopOnSlowdown = true;
			iters = 250;
		}
		

		if(iters >= 0)
		{
			int failsInARow = 0;
			int goalGeneration = generation + iters;

			//Second term checks every ten iters if the last error was small enough to end iterations
            //Starts checking on the third iteration so last two errors are defined
			for(; generation < goalGeneration && (!stopOnSlowdown || failsInARow < BAIL_NUM); ++generation)
			{
				//Do generation
								
				//Mutations
				for(unsigned int j = 0; j < subjects.size(); ++j)
				{
					subjects[j]->Mutate();
				}
		
				//Sort by error, lower is better
				std::sort(subjects.begin(), subjects.end(), EvoAlg::Subject::SubjectComparator(generation));
				

				//Kill bad ones and replace with good ones
				for(unsigned int j = 0; j < subjects.size()/2; ++j)
				{
					subjects[subjects.size() - 1 - j].reset(nullptr);
					subjects[subjects.size() - 1 - j] = std::move(subjects[j]->Clone());	
				}
				
				toTestFib.NextGeneration(generation);
				
				
				//currentOpt.simpleDoubleShift /= currentOpt.IterationChange;
				//currentOpt.ExpectedIdentities /= currentOpt.IterationChange;

				if(bestSoFar->Evaluate(generation) > subjects[subjects.size() - 1]->Evaluate(generation))
				{
					bestSoFar = subjects[subjects.size() - 1]->Clone();
					failsInARow = 0;
				}
				else
				{
					++failsInARow;
				}
            }
            
			std::sort(subjects.rbegin(), subjects.rend(), EvoAlg::Subject::SubjectComparator(generation));    
			
            cout << "Generation " << generation << endl;
			for(int i = max((int)(subjects.size()) - 10, 0); i < (int)subjects.size(); ++i)
			{
				subjects[i]->Print(cout);
				cout << " " << subjects[i]->Evaluate(generation) << endl;
			}
			cout << "Best So far ";
			bestSoFar->Print(cout);
			cout << endl << endl;

			subjects.clear();
			for(int i = 0; i < subjectCount; ++i)
			{
				subjects.push_back(std::move(bestSoFar->Clone()));
			}
		}
		else
		{
			running = false;
		}
	}
}