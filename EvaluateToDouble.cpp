#include "EvaluateToDouble.h"

using namespace std;

/*
 * Defaults to printing a string representation of the double
 */
string EvaluateToDouble::Print() const
{
	ostringstream out;
	out << GetDouble();
	return out.str();
}