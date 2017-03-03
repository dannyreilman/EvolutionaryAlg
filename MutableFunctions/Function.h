#ifndef FUNCTION_H
#define FUNCTION_H

/*
 * General function form, for defining valid functions
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include <memory>
#include <iostream>

#include "EvalException.h" 
#include "EvaluateToDouble.h"
#include "FunctionEnum.h"

using std::vector;
using std::unique_ptr;

namespace MutableFuncs
{
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
		 * Calls GetFunctionEnum
		 */
		int GetNumArgs() const;

		/*
		 * Returns the ID associated with this function
		 */
		int GetID() const;
		
		/*
		* Requires: arguments.length == getNumArgs();
		* If this^ is not met, an EvalException will be thrown
		* 
		* Returns the function evaluated over the arguments.
		*/
		virtual double Eval(const vector<MutableFuncs::EvaluateToDouble*>&) const = 0;
		double Eval(const vector< unique_ptr<MutableFuncs::EvaluateToDouble> >& vec) const;

		/*
	 	* Prints a representation of the function
	 	*/
	 	virtual std::string PrintFunction(const std::vector<EvaluateToDouble*>&) const = 0;
	 	std::string PrintFunction(const std::vector<std::unique_ptr<EvaluateToDouble>>&) const;
		
		virtual unique_ptr<Function> Clone() const = 0;

		//Returns the functionEnum associated with this object
		virtual FunctionEnum GetFunctionEnum() const = 0;
	};
}

#endif
