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

using namespace std;
/*
 * Constructor to assign internal function and argument values
 * Make sure passed in pointers are created with new
 */
FunctionEvaluator::FunctionEvaluator(std::unique_ptr<std::vector<std::unique_ptr<EvaluateToDouble>>> args_in, std::unique_ptr<Function> func_in) 
                                    : args(move(args_in)), func(move(func_in)) {}

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
    return func->Eval(*args);
}