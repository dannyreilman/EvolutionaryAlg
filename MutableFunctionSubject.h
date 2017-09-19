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
    MutableFunctionSubject();
    MutableFunctionSubject(MutableFunctionSubject&& other);    
    MutableFunctionSubject(MutableFuncs::MutationOptions* options_in, ValueSupplier* generator_in);
    
	virtual ~MutableFunctionSubject() {}

	virtual void Mutate();
	
    virtual double Evaluate();
    
    virtual void Print(std::ostream& out) const;    

	virtual std::unique_ptr<Subject> Clone();

private:
	MutableFuncs::MutationOptions* options;
	ValueSupplier* generator;

	std::unique_ptr<MutableFuncs::EvaluateToDouble> mutableFuncObject;
};

#endif
