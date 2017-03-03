#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H

/*
 * Interface
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include <memory>
#include <string>

#include "Function.h"
#include "EvaluateToDouble.h"
#include "FunctionEnum.h"

namespace MutableFuncs
{
    //Forward declaration
    class Function;

    class FunctionEvaluator : public EvaluateToDouble
    {
    public:
        template<typename ArgIter>
        FunctionEvaluator(ArgIter argsStart, ArgIter argsEnd, FunctionEnum func);

        virtual ~FunctionEvaluator();
        virtual double GetDouble() const;
        virtual std::string Print() const;

        virtual std::unique_ptr<EvaluateToDouble> Clone() const;
    private:
        std::vector < std::unique_ptr < EvaluateToDouble > > args;
        std::unique_ptr<Function> func;
    };
}


#endif
