/* 
 * Implementation
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include <cassert>
#include <new>
#include <string>

#include "Addition.h"
#include "FunctionWithIdentity.h"
#include "FunctionFactory.h"

using namespace MutableFuncs;
using std::unique_ptr;

/*
 * Default constructor does nothing
 */
Addition::Addition() : FunctionWithIdentity() {}

/*
 * Destructor to do nothing
 */

Addition::~Addition() {}


/*
 * REQUIRES: args.size == NUM_SUPPORTED_ARGS
 * RETURNS: Let args be [a, b], then Eval returns a + b
 * THROWS:  StringException if args is not the correct number of args
 */
double Addition::Eval(const std::vector<EvaluateToDouble*>& args) const
{
    if((int)args.size() == FunctionFactory::GetSupportedArgs(GetFunctionEnum()))
    {
        return args.at(0)->GetDouble() + args.at(1)->GetDouble();
    }
    else
    {
        throw EvalException(args.size(), FunctionFactory::GetSupportedArgs(GetFunctionEnum()), "Addition");
        return 0;
    }
    return 0;
}

string Addition::PrintFunction(const std::vector<EvaluateToDouble*>& args) const
{
    const string symbol = " + ";
    string returnString;

    returnString += "(";

    int maxArgs = FunctionFactory::GetSupportedArgs(GetFunctionEnum());

    for(int i = 0; i < maxArgs; ++i)
    {
        returnString += args.at(i)->Print();

        if(i < maxArgs - 1)
        {
            returnString += symbol;
        }
    }

    returnString += ")";

    return returnString;
}

std::unique_ptr<Function> Addition::Clone() const
{
    unique_ptr<Function> toReturn(new Addition());
    return toReturn;
}

FunctionEnum Addition::GetFunctionEnum() const
{
    return FunctionEnum::Addition;
}
