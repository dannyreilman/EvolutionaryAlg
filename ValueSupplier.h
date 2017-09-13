#ifndef VALUE_SUPPLIER_H
#define VALUE_SUPPLIER_H
/**
 * An interface to supply test values to the MutableFunctionSubject object
 * These values are used to test fitness of MutableFunc objects
 * By Danny Reilman<reilman@umich.edu>
 */
 
#include <unordered_map>
#include <unordered_set>

class ValueSupplier
{
public:
	virtual ~ValueSupplier() {}
	virtual std::pair<const std::unordered_map<char, double>*, double> GetValue() = 0;

	virtual const std::unordered_set<char>& PeakVariables() = 0;

	//Allows changing behaviour over time
	virtual void NextGeneration(int generationNumber) {}
};

#endif