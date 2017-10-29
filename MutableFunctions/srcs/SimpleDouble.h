#ifndef SIMPLEDOUBLE_H
#define SIMPLEDOUBLE_H

/*
 * Interface
 * An EvaluateToDouble that simply acts as a double
 * By Danny Reilman <reilman@umich.edu>
 */
#include "EvaluateToDouble.h"
#include <memory>

namespace MutableFuncs
{
    class SimpleDouble : public EvaluateToDouble
    {
    public: 
        SimpleDouble(double);
        SimpleDouble();
        virtual ~SimpleDouble();

        double GetDouble(const std::unordered_map<char, double>& variables) const;
        void SetDouble(double);

        virtual std::unique_ptr<EvaluateToDouble> Clone() const;

        virtual void Mutate(MutationOptions& opt, int size);

        virtual void ExportBatch(std::ostream& out) const;        

        virtual bool IsNumber() const;      
        virtual double GetCost() const;
        virtual double GetComplexity(double grain) const;	
        
    private:
        double internalDouble;
    };
}

#endif
