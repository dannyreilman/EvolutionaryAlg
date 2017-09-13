#include "FunctionSupply.h"

FunctionSupply::FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in) : func(move(func_in)), min(min_in), max(max_in)
{
	func->CollectVariables(variablesUsed);

	int range = max - min;
	variableValues.clear();
	for(auto it = variablesUsed.begin(); it != variablesUsed.end(); ++it)
	{
		variableValues[*it] = (rand() % range) + min;
	}

	value = func->GetDouble(variableValues);
}

void FunctionSupply::NextGeneration(int generationNumber) 
{
	int range = max - min;
	variableValues.clear();
	for(auto it = variablesUsed.begin(); it != variablesUsed.end(); ++it)
	{
		variableValues[*it] = (rand() % range) + min;
	}

	value = func->GetDouble(variableValues);
}

std::pair<const std::unordered_map<char, double>*, double> FunctionSupply::GetValue()
{
	std::pair<const std::unordered_map<char, double>*, double> toReturn(&variableValues, value);
	return toReturn;
}

const std::unordered_set<char>& FunctionSupply::PeakVariables()
{
	return variablesUsed;
}