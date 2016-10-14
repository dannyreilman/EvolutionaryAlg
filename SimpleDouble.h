#ifndef SIMPLEDOUBLE_H
#define SIMPLEDOUBLE_H

/*
 * Interface
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
#include "EvaluateToDouble.h"

class SimpleDouble : public EvaluateToDouble
{
public: 
    SimpleDouble(double);
    SimpleDouble();
    double GetDouble() const;
    void SetDouble(double);
private:
    double internalDouble;
};

#endif