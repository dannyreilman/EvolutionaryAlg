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

void SimpleDouble::Mutate(MutationOptions& opt, int size)
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

double SimpleDouble::GetCost() const
{
    return pow(internalDouble, 2);
}

double SimpleDouble::GetComplexity(double grain) const
{
    return (grain / 2) - abs(fmod(internalDouble, grain) - (grain / 2));
}