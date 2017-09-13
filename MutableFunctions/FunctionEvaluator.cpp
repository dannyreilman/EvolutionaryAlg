/*
 * Implementation
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */

#include <vector>
#include <memory>
#include <cmath>
#include <utility>

#include "FunctionEvaluator.h"
#include "Function.h"
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
: func(func_in)
{
    int numArgs = Function::GetSupportedArgs(func_in);
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
}


/*
 * Destructor to deallocate various fields
 */
FunctionEvaluator::~FunctionEvaluator()
{}

/*
 * RETURNS: Func evaluated over args
 */
double FunctionEvaluator::GetDouble(const std::unordered_map<char, double>& variables) const
{
    return Function::Eval(func, args, variables);
}

string FunctionEvaluator::Print() const
{
    return Function::Print(func, args);
}

unique_ptr<EvaluateToDouble> FunctionEvaluator::Clone() const
{
     vector<unique_ptr<EvaluateToDouble> > newVec;

     for(auto it = args.begin(); it != args.end(); ++it)
     {
         newVec.push_back((*it)->Clone());
     }

     unique_ptr<EvaluateToDouble> newTop(new FunctionEvaluator(newVec.begin(), newVec.end(), func));

     return newTop;
}

void FunctionEvaluator::Mutate(MutationOptions& opt)
{
    for(unsigned int i = 0; i < args.size(); ++i)
    {
        EvaluateToDouble::MutatePointer(args[i], opt);
    }
}

FunctionEnum FunctionEvaluator::GetFunctionEnum() const
{
    return func;
}

void FunctionEvaluator::ExportBatch(std::ostream& out) const
{
    out << "gen " << Function::GetGenerativeCommand(func) << " ";

    for(auto it = args.begin(); it != args.end(); ++it)
    {
        (*it)->ExportBatch(out);
    }
}

std::unique_ptr<EvaluateToDouble> FunctionEvaluator::Reduce(double width)
{
    for(unsigned int i = args.size() - 1; i > 0; --i)
    {
        if((args[i]->IsNumber() && abs(args[i]->GetDouble() - Function::GetIdentity(func)) < width) || args[i]->IsInput())
        {
            return move(args[0]);
        }
    }

    if(Function::IsSecondArgSafe(func) && 
    ((args[0]->IsNumber() && (abs(args[0]->GetDouble() - Function::GetIdentity(func)) < width)) || args[0]->IsInput()))
    {
        return move(args[1]);
    }

    return std::unique_ptr<EvaluateToDouble>(nullptr);
} 

void FunctionEvaluator::CollectVariables(std::unordered_set<char>& variables) const
{
    for(auto it = args.cbegin(); it != args.cend(); ++it)
    {
        (*it)->CollectVariables(variables);
    }
}

int FunctionEvaluator::GetHeight() const
{
    int max = 0;
    for(auto it = args.cbegin(); it != args.cend(); ++it)
    {
        int result = (*it)->GetHeight();
        if(result > max)
        {
            max = result;
        }
    }
    return max + 1;
}
