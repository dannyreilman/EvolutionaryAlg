#ifndef FUNCTIONENUM
#define FUNCTIONENUM

#include "StringException.h"
/*
 * Useful enums for choosing function types, as well as information about how many args can be passed 
 * All structs and enums are under factory to prevent clutter 
 *
 * By Danny Reilman <reilman@umich.edu>
 */
 
namespace MutableFuncs
{
    namespace Factory
    {
        enum class FunctionEnum;
        enum class FunctionType;

        struct functionInformation
        {
            FunctionEnum func;
            int numArgs;
            FunctionType type;
            bool hasIdentity; 
        };

        enum class FunctionType
        {
            Algebraic
        };

        enum class FunctionEnum
        {
            Addition
        };

        static const functionInformation AdditionInfo
        {
            FunctionEnum::Addition,
            2,
            FunctionType::Algebraic,
            true
        };


        functionInformation GetFunctionInformation(FunctionEnum in)
        {
            switch(in)
            {
                case FunctionEnum::Addition:
                    return AdditionInfo;
                default:
                    throw StringException("GetFunctionInformation", "Info not implemented");
            }
        }

    }
}

#endif
