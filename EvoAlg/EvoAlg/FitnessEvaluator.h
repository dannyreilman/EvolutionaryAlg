/*
 * Generic class to handle fitness evaluation of subjects 
 * By Danny Reilman <reilman@umich.edu>
 */

#include "Subject.h"

class FitnessEvaluator
{
public:
	virtual double Evaluate(Subject);
};
