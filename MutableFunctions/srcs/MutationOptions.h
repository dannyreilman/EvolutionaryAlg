#ifndef MUTATION_OPTIONS_H
#define MUTATION_OPTIONS_H

#include <random>
#include <vector>
#include <fstream>

namespace MutableFuncs
{
    struct MutationOptions
    {
        std::vector<char> validInputMutations;

        std::mt19937 generator;
        
        double simpleDoubleShift;
        
        int AdditionIdentityChance;
        int SubtractionIdentityChance;
        int MultiplicationIdentityChance;
        int DivisionIdentityChance;
        int PowerIdentityChance;

        int SumOfChances;
        double ExpectedIdentities;

        double InputIdentityChance;

        double ExpectedReduction;

        double IterationChange;

        static void ReadInput(MutationOptions& opt, std::ifstream& valueReader)
        {
            //Ignore Header
            valueReader.ignore(250, '\n');
    
            //Ignore Tag
            valueReader.ignore(250, ' ');
            valueReader >> opt.simpleDoubleShift;

            //Functions
            valueReader.ignore(250, ' ');
            valueReader >> opt.AdditionIdentityChance;

            valueReader.ignore(250, ' ');
            valueReader >> opt.SubtractionIdentityChance;

            valueReader.ignore(250, ' ');
            valueReader >> opt.MultiplicationIdentityChance;

            valueReader.ignore(250, ' ');
            valueReader >> opt.DivisionIdentityChance;
            
            valueReader.ignore(250, ' ');
            valueReader >> opt.PowerIdentityChance;

            opt.SumOfChances = ceil(opt.AdditionIdentityChance + opt.SubtractionIdentityChance + opt.MultiplicationIdentityChance + opt.DivisionIdentityChance + opt.PowerIdentityChance);

            valueReader.ignore(250, ' ');
            valueReader >> opt.ExpectedIdentities;

            //end functions
            valueReader.ignore(250, ' ');
            valueReader >> opt.InputIdentityChance;

            valueReader.ignore(250, ' ');
            valueReader >> opt.ExpectedReduction;

            valueReader.ignore(250, ' ');
            valueReader >> opt.IterationChange;
        }
    };
}    
#endif