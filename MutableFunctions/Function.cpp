#include "Function.h"
#include "SimpleDouble.h"
#include "FunctionFactory.h"

#include <iostream>
#include <memory>
#include <string>

using std::vector;
using std::unique_ptr;
using std::string;

using namespace MutableFuncs;

/*
 * Default constructor does nothing
 */
Function::Function() {}

/*
 * Destructor to do nothing
 */ 
Function::~Function() {}

/*
 * Allows for evaluation of unique_ptrs
 */
double Function::Eval(const vector<unique_ptr<EvaluateToDouble>>& vec) const
{
	vector<EvaluateToDouble*> rawPtrVec;
	rawPtrVec.reserve(vec.size());

	for (int i =0; i < GetNumArgs(); i++)
	{
		rawPtrVec.push_back(vec.at(i).get());
	}
	
	return Eval(rawPtrVec);
}


string Function::PrintFunction(const vector<unique_ptr<EvaluateToDouble>>& vec) const
{
	vector<EvaluateToDouble*> rawPtrVec;
	rawPtrVec.reserve(vec.size());

	for (int i = 0; i < GetNumArgs(); i++)
	{
		rawPtrVec.push_back(vec.at(i).get());
	}
	
	return PrintFunction(rawPtrVec);
}

int Function::GetNumArgs() const
{
	return FunctionFactory::GetSupportedArgs(GetFunctionEnum());
}

int Function::GetID() const
{
	return (int)GetFunctionEnum();
}