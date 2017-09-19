#include "VariableDouble.h"
#include "bad_evaluation.h"

using namespace MutableFuncs;

VariableDouble::VariableDouble(char variableName_in, std::unordered_map<char, double>& variables): variableName(variableName_in) 
{
	if(variables.find(variableName_in) == variables.end())
	{
		variables[variableName_in] = 0;
	}
}

double VariableDouble::GetDouble(const std::unordered_map<char, double>& variables) const
{
	auto result = variables.find(variableName);
	
	if(result != variables.end())
	{
		return result->second;
	}
	else
	{
		throw bad_evaluation("Variable not found.");
	}
}

std::string VariableDouble::Print() const
{
	return std::string(1, variableName);
}

std::unique_ptr<EvaluateToDouble> VariableDouble::Clone() const
{
	return std::unique_ptr<EvaluateToDouble>(new VariableDouble(variableName));
}

void VariableDouble::Mutate(MutationOptions& opt)
{
	//Do nothing because variables cannot mutate
	return;
}

void VariableDouble::ExportBatch(std::ostream& out) const
{
	out << "gen input " << variableName << " ";
}        	

bool VariableDouble::IsInput() const
{
	return true;
}

void VariableDouble::CollectVariables(std::unordered_set<char>& variables) const
{
	variables.insert(variableName);
}
