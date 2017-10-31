#ifndef FUNCTION_SUPPLY_H
#define FUNCTION_SUPPLY_H
/**
 * A ValueSupplier which supplies using an underlying mutablefunc object
 * By Danny Reilman<reilman@umich.edu>
 */

#include "RangedFunctoralSupplier.h"
#include "EvaluateToDouble.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

class FunctionSupply : public RangedFunctoralSupplier
{
public:
	FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in, int sampleSize_in);
protected:
	//This is the implementation of value generation, inputs are guarenteed to be within the range
	virtual double GenerateValue(std::unordered_map<char, double>& inputs);
	
	//This is the implementation which decides how many and named what the variables are
	virtual std::unordered_set<char> GetVariables();
private:
	std::unique_ptr<MutableFuncs::EvaluateToDouble> func; 
};

#endif
