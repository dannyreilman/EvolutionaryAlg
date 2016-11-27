#ifndef ADDITION_H
#define ADDITION_H

#include <memory>


/* 
 * Interface
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include "Function.h"

namespace MutableFuncs
{
    class Addition : public MutableFuncs::Function
    {
    public:
        Addition();
        virtual ~Addition();

        /*
        * Returns: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
        */
        virtual int GetNumArgs() const;

        /*
        * REQUIRES: args.size == NUM_SUPPORTED_ARGS
        * RETURNS: Let args be [a, b], then Eval returns a + b
        * THROWS:  StringException if args is not the correct number of args
        */
        virtual double Eval(const std::vector< MutableFuncs::EvaluateToDouble* >&) const;
    private:
        const static int NUM_SUPPORTED_ARGS = 2;
    };
}

#endif
