#ifndef MUTATION_OPTIONS_H
#define MUTATION_OPTIONS_H

#include <random>
#include <vector>

namespace MutableFuncs
{
    struct MutationOptions
    {
        std::vector<char> validInputMutations;

        std::mt19937 generator;
        
        double simpleDoubleShift;
        
        double AdditionIdentityChance;
        double SubtractionIdentityChance;
        double MultiplicationIdentityChance;
        double DivisionIdentityChance;

        int SumOfChances;
        double InputIdentityChance;

        double IdentityReductionChance;
        double IdentityReductionWidth;

        double IterationChange;
    };
}    
#endif