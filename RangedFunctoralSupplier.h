#ifndef RANGED_FUNCTORAL_SUPPLIER_H
#define RANGED_FUNCTORAL_SUPPLIER_H
/**
 * An abstract class for value suppliers which generate values in some deterministic way over an interval of floats
 * Also samples multiple points at once
 * By Danny Reilman<reilman@umich.edu>
 */

#include "ValueSupplier.h"
#include "EvaluateToDouble.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

class RangedFunctoralSupplier : public ValueSupplier
{
public:
	RangedFunctoralSupplier(int min_in, int max_in, int sampleSize_in);
	
	virtual std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > GetValues();
	
	virtual const std::unordered_set<char>& PeakVariables();
	
	virtual void NextGeneration(int generationNumber);
protected:
	//This is the implementation of value generation, inputs are guarenteed to be within the range
	virtual double GenerateValue(std::unordered_map<char, double>& inputs) = 0;

	//This is the implementation which decides how many and named what the variables are
	virtual std::unordered_set<char> GetVariables() = 0;

private:
	bool setup;
	void InitSetup();
	std::unordered_set<char> variablesUsed;
	std::vector<std::unordered_map<char, double> > variableValues;
	std::vector<double> values;

	int min;
	int max;

	int sampleSize;
};

#endif
