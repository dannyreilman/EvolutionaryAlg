#include "Function.h"
#include "SimpleDouble.h"
#include <cassert>

bool Function::HasIdentity() const
{
    return false;
}

FunctionEvaluator* Function::CreateIdentity() const
{
    assert(HasIdentity());
    FunctionEvaluator returnEval = new FunctionEvaluator(new vector<EvaluateToDouble>(2, new SimpleDouble(0)));
    return &FunctionEvaluator;
}