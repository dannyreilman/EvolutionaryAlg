#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H

/*
 * Interface
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include <memory>
#include <string>

#include "EvaluateToDouble.h"
#include "FunctionEnum.h"

namespace MutableFuncs
{
    //Forward declaration
    class Function;

    class FunctionEvaluator : public EvaluateToDouble
    {
    public:        
        template<typename ArgIter>
        FunctionEvaluator(ArgIter argsStart, ArgIter argsEnd, FunctionEnum func_in);

        virtual ~FunctionEvaluator();
        
        virtual double GetDouble(const std::unordered_map<char, double>& variables) const;

        FunctionEnum GetFunctionEnum() const;
        
        virtual std::string Print() const;

        virtual std::unique_ptr<EvaluateToDouble> Clone() const;
        virtual void Mutate(MutationOptions& opt);

        virtual void ExportBatch(std::ostream& out) const;        

        virtual std::unique_ptr<EvaluateToDouble> Reduce(double width);        
        
        virtual void CollectVariables(std::unordered_set<char>& variables) const;	  
        virtual int GetHeight() const;        
    private:
        std::vector < std::unique_ptr < EvaluateToDouble > > args;
        FunctionEnum func;
    };
}


#endif
