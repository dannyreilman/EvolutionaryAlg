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
#include "Function.h"
#include "EvaluateToDouble.h"

namespace MutableFuncs
{
    //Forward declaration
    class Function;

    class FunctionEvaluator : public EvaluateToDouble
    {
    public:
        FunctionEvaluator(std::unique_ptr < std::vector < std::unique_ptr < EvaluateToDouble > > >, std::unique_ptr < Function > );
        virtual ~FunctionEvaluator();
        virtual double GetDouble() const;
    private:
        std::unique_ptr< std::vector < std::unique_ptr < EvaluateToDouble > > > args;
        std::unique_ptr< Function > func;
    };
}

#endif
