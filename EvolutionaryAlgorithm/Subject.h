#ifndef SUBJECT_H
#define SUBJECT_H

/**
 * An abstract class to handle subjects which can be mutated, cloned, and evaluated for fitness
 *
 * By Danny Reilman <reilman@umich.edu>
 */

#include <memory>

namespace EvoAlg
{
class Subject
{
public:
	virtual ~Subject() {}

	//Should be implemented to incrementally change the subject
	virtual void Mutate() = 0;

	//Returns a double to describe the fitness of this subject
	virtual double Evaluate() = 0;

	//Deep copy of this subject
	virtual std::unique_ptr<Subject> Clone() = 0;
};
}

#endif