#ifndef SIMPLEDOUBLE_H
#define SIMPLEDOUBLE_H

/*
 * Interface
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
#include "EvaluateToDouble.h"

namespace MutableFuncs
{
    class SimpleDouble : public EvaluateToDouble
    {
    public: 
        SimpleDouble(double);
        SimpleDouble();
        virtual ~SimpleDouble();

        double GetDouble() const;
        void SetDouble(double);
    private:
        double internalDouble;
    };
}

#endif
