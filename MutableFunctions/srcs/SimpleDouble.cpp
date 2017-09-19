/*
 * Implementation
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
#include "SimpleDouble.h"
#include <memory>
#include <random>
#include <cmath>

using std::unique_ptr;
using namespace MutableFuncs;

SimpleDouble::SimpleDouble(double double_in) :
                    internalDouble(double_in){}

//init to 0
SimpleDouble::SimpleDouble() : internalDouble(0){}

SimpleDouble::~SimpleDouble() {}

double SimpleDouble::GetDouble(const std::unordered_map<char, double>& variables) const
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

void SimpleDouble::Mutate(MutationOptions& opt)
{
    std::normal_distribution<double> dist(internalDouble, opt.simpleDoubleShift);
    internalDouble = dist(opt.generator);
}

void SimpleDouble::ExportBatch(std::ostream& out) const
{
    out << internalDouble << " ";
}

bool SimpleDouble::IsNumber() const
{
    return true;
}  
