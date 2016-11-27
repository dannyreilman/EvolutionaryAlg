/* 
 * Implementation
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include <cassert>
#include <new>

#include "Addition.h"
#include "SimpleDouble.h"
#include "FunctionWithIdentity.h"

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
 * RETURNS: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
 */
int Addition::GetNumArgs() const
{
    return NUM_SUPPORTED_ARGS;
}

/*
 * REQUIRES: args.size == NUM_SUPPORTED_ARGS
 * RETURNS: Let args be [a, b], then Eval returns a + b
 * THROWS:  StringException if args is not the correct number of args
 */
double Addition::Eval(const std::vector<EvaluateToDouble*>& args) const
{
    if(args.size() == NUM_SUPPORTED_ARGS)
    {
        return args.at(0)->GetDouble() + args.at(1)->GetDouble();
    }
    else
    {
        throw StringException("Addition.Eval", "Incorrect number of arguments given, correct NumArgs is :" + std::to_string(NUM_SUPORTED_ARGS));
    }
}

/*
 * Returns: A pointer to a FunctionEvaluator that evaluates 
 * 		 to the passed in EvaluateToDouble.
 */
static unique_ptr<FunctionEvaluator> Addition::CreateIdentity(unique_ptr<EvaluateToDouble> arg_in) 
{
    unique_ptr<SimpleDouble> idArg(new SimpleDouble(0));

    return CreateEvaluator(move(arg_in),move(idArg));
}

/*
 *  Static function to generate an evaluator with given args
 */
static unique_ptr<MutableFuncs::FunctionEvaluator> CreateEvaluator(unique_ptr<MutableFuncs::EvaluateToDouble> arg1, unique_ptr<MutableFuncs::EvaluateToDouble> arg2)
{
    unique_ptr<Function> instance(new Addition);
    unique_ptr<vector<unique_ptr<EvaulateToDouble> > > args(new vector<unique_ptr<EvaluateToDouble>>());

    args->push_back(move(arg1));
    args->push_back(move(arg2));

    unique_ptr<FunctionEvaluator> evaluator(new FunctionEvaluator(move(args), move(instance)));
    return evaluator;
}
