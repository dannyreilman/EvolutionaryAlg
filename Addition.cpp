/* 
 * Implementation
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */

#include "Addition.h"

const int Addition::NUM_SUPPORTED_ARGS = 2;

/*
 * RETURNS: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
 */
int Addition::GetNumArgs()
{
    return NUM_SUPPORTED_ARGS;
}

/*
 * REQUIRES: args.size == NUM_SUPPORTED_ARGS
 * RETURNS: Let args be [a, b], then Eval returns a + b
 */
double Addition::Eval(vector<EvaluateToDouble*> args)
{
    assert(args.size == NUM_SUPPORTED_ARGS);

    return args.at(0) + args.at(1);
}