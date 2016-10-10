/*
 * Interface
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include "EvaluateToDouble.h"

class FunctionEvaluator : public EvaluateToDouble
{
public:
    FunctionEvaluator(const vector<EvaluateToDouble*>, const Function*);
    double EvaluateToDouble() const;
private:
    vector<EvaluateToDouble*> args;
    const Function* func;
};
