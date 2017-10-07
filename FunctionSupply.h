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
	FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in, int sampleSize_in);
	
	virtual std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > GetValues();
	
	virtual const std::unordered_set<char>& PeakVariables();
	virtual void NextGeneration(int generationNumber);
	
private:
	std::unordered_set<char> variablesUsed;
	std::vector<std::unordered_map<char, double> > variableValues;

	std::unique_ptr<MutableFuncs::EvaluateToDouble> func; 
	std::vector<double> values;

	int min;
	int max;

	int sampleSize;
};

#endif
