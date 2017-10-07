#include "FunctionSupply.h"

FunctionSupply::FunctionSupply(std::unique_ptr<MutableFuncs::EvaluateToDouble> func_in, int min_in, int max_in, int sampleSize_in) : func(move(func_in)), min(min_in), max(max_in), sampleSize(sampleSize_in)
{
	func->CollectVariables(variablesUsed);
	values.resize(sampleSize);
	variableValues.resize(sampleSize);
	NextGeneration(0);
}

void FunctionSupply::NextGeneration(int generationNumber) 
{
	int range = max - min;
	variableValues.clear();

	for(int i = 0; i < sampleSize; ++i)
	{
		for(auto it = variablesUsed.begin(); it != variablesUsed.end(); ++it)
		{
			variableValues[i][*it] = (rand() % range) + min;
		}

		values[i] = func->GetDouble(variableValues[i]);
	}
}

std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > FunctionSupply::GetValues()
{
	std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > toReturn(&variableValues, &values);
	return toReturn;
}

const std::unordered_set<char>& FunctionSupply::PeakVariables()
{
	return variablesUsed;
}