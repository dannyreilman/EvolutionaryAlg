#ifndef CPP_FUNCTION_SUPPLY_H
#define CPP_FUNCTION_SUPPLY_H
/**
 * A value supplier which calls a c++ function
 * This functor must accept a vector<double> of length numVariables as its argument
 * numVariables must be <= 26 because this implementation uses char variables and I don't want to mix lower and upper case
 * a is the first variable, b is the second and so on
 * By Danny Reilman <reilman@umich.edu>
 */
#include "RangedFunctoralSupplier.h"
#include <iostream>

template<typename Func>
class CppFunctorSupply : public RangedFunctoralSupplier
{
public:
	CppFunctorSupply(Func f_in, int min_in, int max_in, int sampleSize_in, int numVariables_in)
	: RangedFunctoralSupplier(min_in, max_in, sampleSize_in), f(f_in), numVariables(numVariables_in) { }

	//This is the implementation of value generation, inputs are guarenteed to be within the range
	virtual double GenerateValue(std::unordered_map<char, double>& inputs)
	{
		std::vector<double> args;
		for(int i = 0; i < numVariables; ++i)
		{
			args.push_back(inputs[(char)('a' + i)]);
		}
		return f(args);
	}
	
	//This is the implementation which decides how many and named what the variables are
	virtual std::unordered_set<char> GetVariables()
	{
		std::unordered_set<char> variables;
		for(int i = 0; i < numVariables; ++i)
		{
			variables.insert((char)('a' + i));
		}
		return variables;
	}

private:
	Func f;
	int numVariables;
};

#endif