#ifndef ADDITION_H
#define ADDITION_H

#include <memory>

#include "FunctionEnum.h"
#include "FunctionWithIdentity.h"
#include "Function.h"
/* 
 * Interface
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */

namespace MutableFuncs
{
    class Addition : public FunctionWithIdentity
    {
    public:
        Addition();
        virtual ~Addition();

        /*
        * REQUIRES: args.size == NUM_SUPPORTED_ARGS
        * RETURNS: Let args be [a, b], then Eval returns a + b
        * THROWS:  StringException if args is not the correct number of args
        */
        virtual double Eval(const std::vector< MutableFuncs::EvaluateToDouble* >&) const;

        virtual std::string PrintFunction(const std::vector<EvaluateToDouble*>&) const;

        virtual std::unique_ptr<Function> Clone() const;

        virtual FunctionEnum GetFunctionEnum() const;
    };
}

#endif
