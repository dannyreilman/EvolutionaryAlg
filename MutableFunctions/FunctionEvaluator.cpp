/*
 * Implementation
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */

#include <vector>
#include <memory>
#include <utility>

#include "FunctionEvaluator.h"
#include "FunctionFactory.h"
#include "StringException.h"

using namespace MutableFuncs;
using namespace std;

/*
 * Constructor to assign internal function and argument values
 * Make sure passed in pointers are created with new
 * 
 */
template<typename ArgIter>
FunctionEvaluator::FunctionEvaluator(ArgIter argsStart, ArgIter argsEnd, FunctionEnum func_in)
{
    int numArgs = FunctionFactory::GetSupportedArgs(func_in);
    args.reserve(numArgs);

    for(int i = 0; i < numArgs; ++i)
    {
        if(argsStart == argsEnd)
        {
            throw StringException("GenerateFunctionEvaluator", "Not enough arguments given");
        }
        else
        {
            args.push_back(move(*argsStart));

            ++argsStart;
        }
    }
    func = FunctionFactory::GenerateFunction(func_in);
}


/*
 * Destructor to deallocate various fields
 */
FunctionEvaluator::~FunctionEvaluator()
{}

/*
 * RETURNS: Func evaluated over args
 */
double FunctionEvaluator::GetDouble() const
{
    return func->Eval(args);
}

string FunctionEvaluator::Print() const
{
    return func->PrintFunction(args);
}

unique_ptr<EvaluateToDouble> FunctionEvaluator::Clone() const
{
     vector<unique_ptr<EvaluateToDouble> > newVec;

     for(auto it = args.begin(); it != args.end(); ++it)
     {
         newVec.push_back((*it)->Clone());
     }

     unique_ptr<EvaluateToDouble> newTop(new FunctionEvaluator(newVec.begin(), newVec.end(), func->GetFunctionEnum()));

     return newTop;
}
