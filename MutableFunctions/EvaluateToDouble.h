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
        static void MutatePointer(std::unique_ptr<EvaluateToDouble>& pointer, MutationOptions& opt);
        static void ExportPointer(std::unique_ptr<EvaluateToDouble>& pointer, 
                                                    const std::string& name, std::ostream& out);

        virtual ~EvaluateToDouble() {}

        virtual double GetDouble() const;
        virtual double GetDouble(const std::unordered_map<char, double>& variables) const = 0;

        virtual std::string Print() const;

        //Deep copy of this evaluateToDouble
        virtual std::unique_ptr<EvaluateToDouble> Clone() const = 0;

        //Individual mutation, identity spawning is handled elsewhere
        virtual void Mutate(MutationOptions& opt) = 0;

        //Generates a batch command to create this object again
        virtual void ExportBatch(std::ostream& out) const = 0;

        virtual bool IsNumber() const;
        virtual bool IsInput() const;
        virtual std::unique_ptr<EvaluateToDouble> Reduce(double width) const;

        virtual void CollectVariables(std::unordered_set<char>& variables) const;
        virtual int GetHeight() const;
    };
}

#endif
