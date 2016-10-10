/*
 * Implementation
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */

#include <vector>
#include "FunctionEvaluator.h"

/*
 * Constructor to assign internal function and argument values
 */
FunctionEvaluator::FunctionEvaluator(vector<EvaluateToDouble*> args_in, 
                                    Function* func_in) : args(args_in), func(func_in) {}

/*
 * RETURNS: Func evaluated over args
 */
double FunctionEvaluator::EvaluateToDouble() const
{
    return func->Eval(args);
}