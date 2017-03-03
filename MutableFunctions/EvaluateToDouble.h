#ifndef EVALUATETODOUBLE_H
#define EVALUATETODOUBLE_H

#include <string>
#include <sstream>
#include <memory>

/*
 * A generic class to define anything that can evaluate to a double
 * By Danny Reilman <reilman@umich.edu>
 */
namespace MutableFuncs
{
    class EvaluateToDouble
    {
    public:
        virtual ~EvaluateToDouble() {}

        virtual double GetDouble() const = 0;

        virtual std::string Print() const;

        //Deep copy of this evaluateToDouble
        virtual std::unique_ptr<EvaluateToDouble> Clone() const = 0;
    };
}

#endif
