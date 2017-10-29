#ifndef EVALUATETODOUBLE_H
#define EVALUATETODOUBLE_H

#include "MutationOptions.h"
#include "Function.h"

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

/*
 * A generic class to define anything that can evaluate to a double
 * and can be mutated
 * By Danny Reilman <reilman@umich.edu>
 */
namespace MutableFuncs
{
	//Forward declaration
    class Function;
    
    class EvaluateToDouble
    {
    public:
        virtual ~EvaluateToDouble() {}

        virtual double GetDouble() const;
        virtual double GetDouble(const std::unordered_map<char, double>& variables) const = 0;

        virtual std::string Print() const;

        //Deep copy of this evaluateToDouble
        virtual std::unique_ptr<EvaluateToDouble> Clone() const = 0;

        //Individual mutation, identity spawning is handled elsewhere
        virtual void Mutate(MutationOptions& opt, int size) = 0;

        //Generates a batch command to create this object again
        virtual void ExportBatch(std::ostream& out) const = 0;

        virtual bool IsNumber() const;
        virtual bool IsInput() const;
        virtual std::unique_ptr<EvaluateToDouble> Reduce() const;

        //puts all used variables in "variables"
        virtual void CollectVariables(std::unordered_set<char>& variables) const;

        //Returns the height of this evaluateToDouble when represented as a tree
        virtual int GetHeight() const;
        //Returns the node count of this evaluateToDouble when represented as a tree
        virtual int GetSize() const;

        virtual double GetCost() const;
        
        virtual double GetComplexity(double grain) const;

        static void MutatePointer(std::unique_ptr<EvaluateToDouble>& pointer, MutationOptions& opt, int size);
        
        static void MutatePointer(std::unique_ptr<EvaluateToDouble>& pointer, MutationOptions& opt)
        {
            MutatePointer(pointer, opt, pointer->GetSize());
        }

        static void ExportPointer(std::unique_ptr<EvaluateToDouble>& pointer, 
                                                    const std::string& name, std::ostream& out);

    };
}

#endif
