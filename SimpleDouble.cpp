/*
 * Implementation
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
 #include "SimpleDouble.h"

SimpleDouble::SimpleDouble(double double_in) :
                    internalDouble(double_in){}

//init to 0
SimpleDouble::SimpleDouble() : internalDouble(0){}

double SimpleDouble::GetDouble() const
{
    return internalDouble;
}

void SimpleDouble::SetDouble(double setDouble)
{
    internalDouble = setDouble;
}

