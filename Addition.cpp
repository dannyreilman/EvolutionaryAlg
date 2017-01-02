/* 
 * Implementation
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include <cassert>
#include <new>
#include <string>

#include "Addition.h"
#include "SimpleDouble.h"
#include "FunctionWithIdentity.h"

using namespace std;

/*
 * Default constructor does nothing
 */
Addition::Addition() : FunctionWithIdentity() {}

/*
 * Destructor to do nothing
 */

Addition::~Addition() {}

/*
 * RETURNS: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
 */
int Addition::GetNumArgs() const
{
    return NUM_SUPPORTED_ARGS;
}

/*
 * REQUIRES: args.size == NUM_SUPPORTED_ARGS
 * RETURNS: Let args be [a, b], then Eval returns a + b
 */
double Addition::Eval(const std::vector<EvaluateToDouble *>& args) const
{
    assert(args.size() == NUM_SUPPORTED_ARGS);

    return args.at(0)->GetDouble() + args.at(1)->GetDouble();
}

/*
 * Requires: HasIdentity()
 * Returns: A pointer to a FunctionEvaluator that evaluates 
 * 		 to the passed in EvaluateToDouble.
 */
unique_ptr<FunctionEvaluator> Addition::CreateIdentity(unique_ptr<EvaluateToDouble> arg_in) const
{
    unique_ptr<Function> instance(new Addition);

    unique_ptr<vector<unique_ptr<EvaluateToDouble>>> args(new vector<unique_ptr<EvaluateToDouble>>());
    
    args->push_back(move(arg_in));
    args->push_back(unique_ptr<EvaluateToDouble>(new SimpleDouble(0)));
    
    unique_ptr<FunctionEvaluator> identity(new FunctionEvaluator(move(args), move(instance)));
    return identity;
}

string Addition::PrintFunction(const std::vector<EvaluateToDouble*>& args) const
{
    const string symbol = " + ";
    string returnString;

    returnString += "(";

    for(int i = 0; i < NUM_SUPPORTED_ARGS; ++i)
    {
        returnString += args.at(i)->Print();

        if(i < NUM_SUPPORTED_ARGS - 1)
        {
            returnString += symbol;
        }
    }

    returnString += ")";

    return returnString;
}

