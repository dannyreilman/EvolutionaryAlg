#ifndef ADDITION_H
#define ADDITION_H

/* 
 * Interface
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include "FunctionWithIdentity.h"

class Addition : public FunctionWithIdentity
{
public:
    Addition();
    virtual ~Addition();
    /*
     * Returns: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
     */
    virtual int GetNumArgs() const;

    /*
     * REQUIRES: args.size == NUM_SUPPORTED_ARGS
     * RETURNS: Let args be [a, b], then Eval returns a + b
     */
    virtual double Eval(const std::vector<EvaluateToDouble*>&) const;

    /*
     * Requires: HasIdentity()
     * Returns: A pointer to a FunctionEvaluator that evaluates 
     *  		 to the passed in EvaluateToDouble.
     */
    virtual std::unique_ptr<FunctionEvaluator> CreateIdentity(std::unique_ptr<EvaluateToDouble>) const;

private:
    const static int NUM_SUPPORTED_ARGS = 2;
};

#endif