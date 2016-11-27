#ifndef EVALUATETODOUBLE_H
#define EVALUATETODOUBLE_H

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
    };
}

#endif
