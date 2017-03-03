#include "EvaluateToDouble.h"
#include <sstream>

using namespace MutableFuncs;

/*
 * Defaults to printing a string representation of the double
 */
std::string EvaluateToDouble::Print() const
{
	std::ostringstream out;
	out << GetDouble();
	return out.str();
}