#ifndef SUBJECT_H
#define SUBJECT_H

/**
 * An abstract class to handle subjects which can be mutated, cloned, and evaluated for fitness
 *
 * By Danny Reilman <reilman@umich.edu>
 */

#include <memory>
#include <iostream>

namespace EvoAlg
{
class Subject
{
public:
    class SubjectComparator
    {
    public: 
        SubjectComparator(int generation)
        {
            this->generation = generation;
        }

        bool operator()(std::unique_ptr<Subject>& a, std::unique_ptr<Subject>& b)
        {
            return a->Evaluate(generation) < b->Evaluate(generation);
        }
    private:
        int generation;
    };

	virtual ~Subject() {}

	//Should be implemented to incrementally change the subject
	virtual void Mutate() = 0;

	//Returns a double to describe the fitness of this subject
    virtual double Evaluate(int generation) = 0;
    
    virtual void Print(std::ostream& out) const = 0;

	//Deep copy of this subject
    virtual std::unique_ptr<Subject> Clone() = 0;
    
};
}

#endif