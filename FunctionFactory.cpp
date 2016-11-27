/*
 * Functions to handle making functions and functionevaluators
 *
 * By Danny Reilman <reilman@umich.edu>
 */

#include "FunctionEnum.h"
#include "FunctionFactory.h"

#include <memory>

using std::unique_ptr;

namespace MutableFuncs::Factory
{
    unique_ptr<Function> GenerateFunction(FunctionEnum func)
    {
        unique_ptr<Function> genFunc;
        switch (func)
        {
        FunctionEnum::Addition:
            genFunc
            break;
        }
    }
}