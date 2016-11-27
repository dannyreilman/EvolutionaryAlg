#ifndef FUNCTION_H
#define FUNCTION_H

/*
 * General function form, for defining valid functions
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include <memory>

#include "EvaluateToDouble.h"
#include "FunctionEvaluator.h"

using std::vector;
using std::unique_ptr;

namespace MutableFuncs
{
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
		virtual double Eval(const vector<MutableFuncs::EvaluateToDouble*>&) const = 0;
		double Eval(const vector< unique_ptr<MutableFuncs::EvaluateToDouble> >& vec) const;
	};
}

#endif
