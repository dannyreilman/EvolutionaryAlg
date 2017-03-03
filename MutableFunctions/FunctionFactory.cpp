#ifndef FUNCTION_FACTORYCPP
#define FUNCTION_FACTORYCPP

#include <memory>

#include "StringException.h"

#include "FunctionFactory.h"
#include "FunctionEnum.h"
#include "Function.h"
#include "Addition.h"
#include "EvaluateToDouble.h"
#include "FunctionEvaluator.h"

/*
 * Useful enums for choosing function types, as well as information about how many args can be passed 
 * All structs and enums are under factory to prevent clutter 
 *
 * By Danny Reilman <reilman@umich.edu>
 */
static int ADDITION_SUPPORTED_ARGS = 2;

namespace MutableFuncs
{

	std::unique_ptr<Function> FunctionFactory::GenerateFunction(FunctionEnum funcType)
	{
		std::unique_ptr<Function> toReturn;

		switch(funcType)
		{
			case FunctionEnum::Addition:
				toReturn.reset(new Addition());
				break;
			default:
				throw StringException("GenerateFunction", "Generation not implemented");
		}

		return toReturn;
	}

	int FunctionFactory::GetSupportedArgs(FunctionEnum in)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return ADDITION_SUPPORTED_ARGS;
			default:
				throw StringException("GetFunctionInformation", "Info not implemented");
		}
	}

	//Generates a functionEvaluator starting from begin, throws exception if end is reached
	//Will only throw an exception if distance(end-begin) > info.supportedArgs
	template<typename argIterator>
	std::unique_ptr<EvaluateToDouble> FunctionFactory::GenerateFunctionEvaluator(FunctionEnum type, argIterator begin, argIterator end)
	{
		std::unique_ptr<Function> func = GenerateFunction(type);
		std::unique_ptr<FunctionEvaluator> funcEval(new FunctionEvaluator(begin, end, func));
		return funcEval;
	}
}

#endif
