#include "FunctionSupply.h"

FunctionSupply::FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in, int sampleSize_in)
: RangedFunctoralSupplier(min_in, max_in, sampleSize_in), func(std::move(func_in))
{ }

double FunctionSupply::GenerateValue(std::unordered_map<char, double>& inputs)
{
	return func->GetDouble(inputs);
}

//This is the implementation which decides how many and named what the variables are
std::unordered_set<char> FunctionSupply::GetVariables()
{
	std::unordered_set<char> variables;
	func->CollectVariables(variables);
	return variables;
}
