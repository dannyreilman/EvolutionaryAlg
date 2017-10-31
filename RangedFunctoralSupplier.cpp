#include "RangedFunctoralSupplier.h"
#include <iostream>

RangedFunctoralSupplier::RangedFunctoralSupplier(int min_in, int max_in, int sampleSize_in) : min(min_in), max(max_in), sampleSize(sampleSize_in)
{
	values.resize(sampleSize_in);
	variableValues.resize(sampleSize_in);
	setup = false;
}


void RangedFunctoralSupplier::NextGeneration(int generationNumber) 
{
	if(!setup)
	{
		variablesUsed = GetVariables();
		setup = true;
	}

	int range = max - min;
	for(int i = 0; i < sampleSize; ++i)
	{
		for(auto it = variablesUsed.begin(); it != variablesUsed.end(); ++it)
		{
			variableValues[i][*it] = (rand() % range) + min;
		}

		values[i] = GenerateValue(variableValues[i]);
	}
}

std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > RangedFunctoralSupplier::GetValues()
{
	if(!setup)
	{
		InitSetup();
	}
	std::pair<std::vector<std::unordered_map<char, double> >*, std::vector<double>* > toReturn(&variableValues, &values);
	return toReturn;
}

const std::unordered_set<char>& RangedFunctoralSupplier::PeakVariables()
{
	if(!setup)
	{
		InitSetup();
	}
	return variablesUsed;
}

void RangedFunctoralSupplier::InitSetup()
{
	setup = true;
	variablesUsed = GetVariables();
	NextGeneration(0);
}