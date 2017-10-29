//A temporary proof of concept on how simulations would work
//This functionality will eventually be added into MutableFuncDriver
//  By Danny Reilman <reilman@umich.edu>

#include "MutableFunctionSubject.h"
#include "MutationOptions.h"
#include "FunctionSupply.h"
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

int main()
{
	srand(time(NULL));
	vector<unique_ptr<EvoAlg::Subject> > subjects;

	vector< mutableFuncObj > mainArgs;

	vector< mutableFuncObj > xArgs;
    xArgs.push_back(mutableFuncObj(new MutableFuncs::VariableDouble('x')));
	xArgs.push_back(mutableFuncObj(new MutableFuncs::SimpleDouble(2)));
	mainArgs.push_back(mutableFuncObj(new MutableFuncs::FunctionEvaluator(xArgs.begin(), xArgs.end(), MutableFuncs::FunctionEnum::Multiplication)));
	
	vector< mutableFuncObj > yArgs;
    yArgs.push_back(mutableFuncObj(new MutableFuncs::VariableDouble('y')));
	yArgs.push_back(mutableFuncObj(new MutableFuncs::SimpleDouble(5)));
	mainArgs.push_back(mutableFuncObj(new MutableFuncs::FunctionEvaluator(yArgs.begin(), yArgs.end(), MutableFuncs::FunctionEnum::Multiplication)));


    mutableFuncObj toTestObjectHard(
            new MutableFuncs::FunctionEvaluator(mainArgs.begin(),
                                    mainArgs.end(),
                                    MutableFuncs::FunctionEnum::Addition));

    vector< mutableFuncObj > args;
    args.push_back(mutableFuncObj(new MutableFuncs::VariableDouble('x')));
    args.push_back(mutableFuncObj(new MutableFuncs::SimpleDouble(10)));

    mutableFuncObj toTestObjectEasy(
        new MutableFuncs::FunctionEvaluator(args.begin(),
                                args.end(),
                                MutableFuncs::FunctionEnum::Addition));

    FunctionSupply toTest(std::move(toTestObjectHard), -1000, 1000, 25);

    MutableFuncs::MutationOptions opt;
	MutableFuncs::MutationOptions currentOpt;

    //Load from defaultMutationValues.txt
	ifstream valueReader("DefaultMutationValues.txt");
    
    //Ignore Header
    valueReader.ignore(250, '\n');

    //Ignore Tag
    valueReader.ignore(250, ' ');
    valueReader >> opt.simpleDoubleShift;

    //Functions
    valueReader.ignore(250, ' ');
    valueReader >> opt.AdditionIdentityChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.SubtractionIdentityChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.MultiplicationIdentityChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.DivisionIdentityChance;

    opt.SumOfChances = ceil(opt.AdditionIdentityChance + opt.SubtractionIdentityChance + opt.MultiplicationIdentityChance + opt.DivisionIdentityChance);

	valueReader.ignore(250, ' ');
	valueReader >> opt.ExpectedIdentities;

    //end functions
    valueReader.ignore(250, ' ');
    valueReader >> opt.InputIdentityChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.ExpectedReduction;

	valueReader.ignore(250, ' ');
	valueReader >> opt.IterationChange;
	
    valueReader.close();

	currentOpt  = opt;
	
	int subjectCount;
	cout << "How many subjects?" << endl;
	cin >> subjectCount;

    for(int i = 0; i < subjectCount; ++i)
    {
        unique_ptr<EvoAlg::Subject> temp(new MutableFunctionSubject(&currentOpt, &toTest));
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
				for(unsigned int j = 0; j < subjects.size()/4; ++j)
				{
					subjects[subjects.size() - 1 - j].reset(nullptr);
					subjects[subjects.size() - 1 - j] = std::move(subjects[j]->Clone());
				}
				
				toTest.NextGeneration(generation);
				
				
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
			for(unsigned int i = subjects.size() - 10; i < subjects.size(); ++i)
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