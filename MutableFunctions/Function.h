#ifndef FUNCTION_H
#define FUNCTION_H

#include "FunctionEnum.h"
#include "EvaluateToDouble.h"
#include "MutationOptions.h"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace MutableFuncs
{
	//Forward declaration
	class EvaluateToDouble;

	class Function
	{
	public:
		static int GetSupportedArgs(FunctionEnum in);
		static double GetIdentity(FunctionEnum in);
		static bool IsSecondArgSafe(FunctionEnum in);
		
		static double Eval(FunctionEnum in, const std::vector<std::unique_ptr<EvaluateToDouble> >& args, const std::unordered_map<char, double>& variables);
		static std::string Print(FunctionEnum in, const std::vector<std::unique_ptr<EvaluateToDouble> >& args);

		static std::unique_ptr<EvaluateToDouble> PossibleIdentity(std::unique_ptr<EvaluateToDouble>& arg, const MutationOptions& opt);

		static std::string GetGenerativeCommand(FunctionEnum in);
	private:
		Function() {}
	};
}

#endif
