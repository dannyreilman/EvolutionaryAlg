#ifndef FUNCTIONFACTORY
#define FUNCTIONFACTORY

#include "FunctionEnum.h"
#include <memory>

/*
 * Functions to handle making functions and functionevaluators
 *
 * By Danny Reilman <reilman@umich.edu>
 */

namespace MutableFuncs::Factory
{

    /*
     * Creates a function from a functionenum
     */
    std::unique_ptr<Function> GenerateFunction(FunctionEnum func);
    
    /*
     * Creates a function evaluator that uses the function func evaluated over arg 1 and 2
     */
    std::unique_ptr<FunctionEvaluator> GenerateEvaluator(FunctionEnum func, std::unique_ptr<EvaluateToDouble> arg1, std::unique_ptr<EvaluateToDouble> arg2);

    /*
     * REQUIRES: func has an identity
     * Creates a function evaluator that uses the function func and evaluates to arg
     * Will throw StringException if the func does not have an identity
     */
    std::unique_ptr<FunctionEvaluator> GenerateIdentity(FunctionEnum func, std::unique_ptr<EvaluateToDouble> arg);

}

#endif
