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

using namespace std;

static int SUBJECT_COUNT = 10;
using mutableFuncObj = unique_ptr<MutableFuncs::EvaluateToDouble>;

int main()
{
    vector<unique_ptr<EvoAlg::Subject> > subjects;
    vector< mutableFuncObj > args;

    args.push_back(mutableFuncObj(new MutableFuncs::VariableDouble('x')));
    args.push_back(mutableFuncObj(new MutableFuncs::SimpleDouble(10)));

    mutableFuncObj toTestObject(
            new MutableFuncs::FunctionEvaluator(args.begin(),
                                    args.end(),
                                    MutableFuncs::FunctionEnum::Addition));

    FunctionSupply toTest(std::move(toTestObject), -1000, 1000);

    MutableFuncs::MutationOptions opt;

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

    //end functions
    valueReader.ignore(250, ' ');
    valueReader >> opt.InputIdentityChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.IdentityReductionChance;

    valueReader.ignore(250, ' ');
    valueReader >> opt.IdentityReductionWidth;

    valueReader.close();
    
    for(int i = 0; i < SUBJECT_COUNT; ++i)
    {
        unique_ptr<EvoAlg::Subject> temp(new MutableFunctionSubject(&opt, &toTest));
        subjects.push_back(std::move(temp));
    }

    for(int i = 0; i < 5; ++i)
    {
        //Do generation
        
        //Sort by fitness
        std::sort(subjects.begin(), subjects.end(), EvoAlg::Subject::SubjectComparator);
        
        //Kill bad ones and replace with good ones
        for(unsigned int i = 0; i < subject.size()/4; ++i)
        {
            subjects[subjects.size() - 1 - i].reset(subjects[i].Clone());
        }
        
        //Mutations
        for(unsigned int i = 0; i < subjects.size(); ++i)
        {
            MutableFuncs::EvaluateToDouble::MutatePointer(subjects[i]);
        }
    }
    std::sort(subjects.begin(), subjects.end(), EvoAlg::Subject::SubjectComparator());    
    
    cout << "Result" << endl;
    for(int i = 0; i < subjects.size(); ++i)
    {
        subjects[i]->Print(cout);
        cout << endl;
    }
}