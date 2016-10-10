/* 
 * Interface
 * Function for addition
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include "EvaluateToDouble.h"
#include "Function.h"

class Addition : public Function
{
public:
    /*
    * Returns: NUM_SUPPORTED_ARGS, the length of args that eval(args) will accept
    */
    int GetNumArgs() const;

    /*
     * REQUIRES: args.size == NUM_SUPPORTED_ARGS
     * RETURNS: Let args be [a, b], then Eval returns a + b
     */
    double Eval(const vector<EvaluateToDouble*>) const;
private:
    const int NUM_SUPPORTED_ARGS;
};