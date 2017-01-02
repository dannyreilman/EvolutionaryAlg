#ifndef FUNCTION_H
#define FUNCTION_H

/*
 * General function form, for defining valid functions
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include <memory>
#include <iostream>

#include "EvaluateToDouble.h"
#include "FunctionEvaluator.h"

//Forward declaration
class FunctionEvaluator;

class Function {
public:
	/*
	 * Constructor
	 */
	Function();

	/*
	 * Destructor
	 */
	virtual ~Function();

	/*
	 * Returns the number of arguments that should be sent into evaluate
	 */
	virtual int GetNumArgs() const = 0;

	/*
	 * Requires: arguments.length == getNumArgs();
	 * Returns the function evaluated over the arguments.
	 */
	virtual double Eval(const std::vector<EvaluateToDouble*>&) const = 0;
	double Eval(const std::vector<std::unique_ptr<EvaluateToDouble>>&) const;

	/*
	 * Prints a representation of the function
	 */
	 virtual std::string PrintFunction(const std::vector<EvaluateToDouble*>&) const = 0;
	 std::string PrintFunction(const std::vector<std::unique_ptr<EvaluateToDouble>>&) const;
};

#endif