#ifndef FUNCTIONWITHID_H
#define FUNCTIONWITHID_H	 

#include <vector>
#include <memory>

#include "Function.h"

using std::unique_ptr;

namespace MutableFuncs
{
	class FunctionWithIdentity : public Function
	{
	public:
		FunctionWithIdentity() : Function() {}
		virtual ~FunctionWithIdentity() {}
		/*
		* Requires: HasIdentity()
		* Returns: A pointer to a FunctionEvaluator that evaluates 
		* 		 to the passed in EvaluateToDouble.
		*/
		static virtual std::unique_ptr<FunctionEvaluator> CreateIdentity(std::unique_ptr<EvaluateToDouble>) const = 0;
	};
}

#endif
