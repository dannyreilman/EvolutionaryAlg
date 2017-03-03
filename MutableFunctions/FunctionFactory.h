#ifndef FUNCTION_FACTORY_H
#define FUNCTION_FACTORY_H

#include <memory>

#include "Function.h"
#include "FunctionEnum.h"
#include "EvaluateToDouble.h"

namespace MutableFuncs
{
	class FunctionFactory
	{
	public:
		static std::unique_ptr<Function> GenerateFunction(FunctionEnum funcType);
		static int GetSupportedArgs(FunctionEnum in);
		template<typename argIterator>
		static std::unique_ptr<EvaluateToDouble> GenerateFunctionEvaluator(FunctionEnum type, argIterator begin, argIterator end);
	private:
		FunctionFactory() {}
	};
}

#endif
