#ifndef FUNCTIONWITHID_H
#define FUNCTIONWITHID_H	 

#include <vector>
#include <memory>

#include "Function.h"


class FunctionWithIdentity : public Function
{
public:
	FunctionWithIdentity();
	/*
	 * Requires: HasIdentity()
	 * Returns: A pointer to a FunctionEvaluator that evaluates 
	 * 		 to the passed in EvaluateToDouble.
	 */
	virtual std::unique_ptr<FunctionEvaluator> CreateIdentity(std::unique_ptr<EvaluateToDouble>) const = 0;
};

#endif