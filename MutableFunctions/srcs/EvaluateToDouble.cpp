#include "EvaluateToDouble.h"
#include "FunctionEvaluator.h"
#include "SimpleDouble.h"
#include "VariableDouble.h"

#include <string>
#include <sstream>

using namespace MutableFuncs;

/*
 * Defaults to printing a string representation of the double
 */
std::string EvaluateToDouble::Print() const
{
	std::ostringstream out;
	out << GetDouble();
	return out.str();
}

/**
 * Defaults to not use variables
 */
double EvaluateToDouble::GetDouble() const
{
	std::unordered_map<char, double> dummyVariables;
	return GetDouble(dummyVariables);
}

void EvaluateToDouble::MutatePointer(std::unique_ptr<EvaluateToDouble>& pointer, MutationOptions& opt, int size)
{
	double numIdentity = ((rand() % 10000) / 10000.0);

	//Reduce if possible
	if(numIdentity < (opt.ExpectedReduction / size))
	{
		std::unique_ptr<EvaluateToDouble> temp = pointer->Reduce();
		if(temp)
		{
			pointer = move(temp);
		}
	}

	//Mutate (This is the recursive part)
	pointer->Mutate(opt, size);
	
	//While heading back up the stack, possibly increase the size of the tree below you by generating an identity
	pointer = Function::PossibleIdentity(pointer, opt, size);
}

void EvaluateToDouble::ExportPointer(std::unique_ptr<EvaluateToDouble>& pointer, const std::string& name, std::ostream& out)
{
	out << "move ";
	pointer->ExportBatch(out);
	out << name;
	out << '\n';
}

bool EvaluateToDouble::IsNumber() const
{
	return false;
}

bool EvaluateToDouble::IsInput() const
{
	return false;
}

std::unique_ptr<EvaluateToDouble> EvaluateToDouble::Reduce() const
{
	return std::unique_ptr<EvaluateToDouble>(nullptr);
}

void EvaluateToDouble::CollectVariables(std::unordered_set<char>& variables) const
{
	//No variables needed in general
}

int EvaluateToDouble::GetHeight() const
{
	return 1;
}

int EvaluateToDouble::GetSize() const
{
    return 1;
}

//Measures the relative magnitude of 
double EvaluateToDouble::GetCost() const
{
	return 0;
}

double EvaluateToDouble::GetComplexity(double grain) const
{
	return 0;
}
