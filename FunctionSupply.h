#ifndef FUNCTION_SUPPLY_H
#define FUNCTION_SUPPLY_H
/**
 * A ValueSupplier which supplies using an underlying mutablefunc object
 * By Danny Reilman<reilman@umich.edu>
 */

#include "ValueSupplier.h"
#include "EvaluateToDouble.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

class FunctionSupply : public ValueSupplier
{
public:
	FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in);
	
	virtual std::pair<const std::unordered_map<char, double>*, double> GetValue();
	
	virtual const std::unordered_set<char>& PeakVariables();
	virtual void NextGeneration(int generationNumber);
	
private:
	std::unordered_set<char> variablesUsed;
	std::unordered_map<char, double> variableValues;

	std::unique_ptr<MutableFuncs::EvaluateToDouble> func; 
	double value;

	int min;
	int max;

};

#endif
