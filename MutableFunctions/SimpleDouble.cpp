/*
 * Implementation
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
#include "SimpleDouble.h"
#include <memory>

using std::unique_ptr;
using namespace MutableFuncs;

SimpleDouble::SimpleDouble(double double_in) :
                    internalDouble(double_in){}

//init to 0
SimpleDouble::SimpleDouble() : internalDouble(0){}

SimpleDouble::~SimpleDouble() {}

double SimpleDouble::GetDouble() const
{
    return internalDouble;
}

void SimpleDouble::SetDouble(double setDouble)
{
    internalDouble = setDouble;
}

unique_ptr<EvaluateToDouble> SimpleDouble::Clone() const
{
    unique_ptr<EvaluateToDouble> toReturn(new SimpleDouble(internalDouble));
    return toReturn;
}
