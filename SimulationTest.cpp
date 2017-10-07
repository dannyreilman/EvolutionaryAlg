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

static double EPSILON = 0.01;

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

    FunctionSupply toTest(std::move(toTestObjectHard), -1000, 1000, 10);

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
	while(running)
	{
		cout << "Move forward how many iterations? (0 to run until completion)" << endl;
		cin >> iters;

		currentOpt = opt;
		
		bool stopOnSlowdown = false;
		if(iters == 0)
		{
			stopOnSlowdown = true;
			iters = 100000;
		}
		
		if(iters >= 0)
		{
			double secondLastError = 0;
			double lastError = 0;

            //Second term checks every ten iters if the last error was small enough to end iterations
            //Starts checking on the third iteration so last two errors are defined
			for(int i = 0; i < iters && (!stopOnSlowdown || ((i % 10 != 3) || (abs(secondLastError - lastError) > EPSILON))); ++i)
			{
				//Do generation
								
				//Mutations
				for(unsigned int j = 0; j < subjects.size(); ++j)
				{
					subjects[j]->Mutate();
				}
		
				//Sort by error, lower is better
				std::sort(subjects.begin(), subjects.end(), EvoAlg::Subject::SubjectComparator());
				

				//Kill bad ones and replace with good ones
				for(unsigned int j = 0; j < subjects.size()/2; ++j)
				{
					subjects[subjects.size() - 1 - j].reset(nullptr);
					subjects[subjects.size() - 1 - j] = std::move(subjects[j]->Clone());
				}
				
				toTest.NextGeneration(i);
				
				secondLastError = lastError;
				lastError = subjects[0]->Evaluate();
				
				currentOpt.simpleDoubleShift /= currentOpt.IterationChange;
				currentOpt.ExpectedIdentities /= currentOpt.IterationChange;
            }
            
			std::sort(subjects.rbegin(), subjects.rend(), EvoAlg::Subject::SubjectComparator());    
			
            
			for(unsigned int i = 0; i < subjects.size(); ++i)
			{
				subjects[i]->Print(cout);
				cout << " " << subjects[i]->Evaluate() << endl;
			}
		}
		else
		{
			running = false;
		}
	}
}