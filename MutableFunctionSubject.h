#ifndef MUTABLE_FUNCTION_SUBJECT_H
#define MUTABLE_FUNCTION_SUBJECT_H

/**
 * A wrapper class to allow EvaluateToDoubles to conform to the Subject interface
 * By Danny Reilman <reilman@umich.edu>
 */

#include "Subject.h"
#include "ValueSupplier.h"

#include "EvaluateToDouble.h"
#include "MutationOptions.h"


class MutableFunctionSubject : public EvoAlg::Subject
{
public:
	MutableFunctionSubject(MutationOptions* options_in, ValueSupplier* generator_in);
	virtual ~MutableFunctionSubject() {}

	virtual void Mutate();
	
	virtual double Evaluate();

	virtual std::unique_ptr<Subject> Clone();

private:
	MutationOptions* options;
	ValueSupplier* generator;

	std::unique_ptr<MutableFuncs::EvaluateToDouble> MutableFuncObject;
};

#endif
