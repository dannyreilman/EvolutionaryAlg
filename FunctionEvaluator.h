/*
 * A class that holds a function
 * and evaluates it to an EvaluateToDouble
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include "EvaluateToDouble.h"

class FunctionEvaluator : public EvaluateToDouble
{
public:
    FunctionEvaluator(vector<EvaluateToDouble*>, Function*);
    double EvaluateToDouble();
private:
    vector<EvaluateToDouble*> args;
    Function* fun;
};
