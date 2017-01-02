#include "Function.h"
#include "SimpleDouble.h"

#include <iostream>
#include <cassert>
#include <memory>
#include <string>
using namespace std;

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

	for (int i =0; i < GetNumArgs(); i++)
	{
		rawPtrVec.push_back(vec.at(i).get());
	}
	
	return Eval(rawPtrVec);
}

string Function::PrintFunction(const vector<unique_ptr<EvaluateToDouble>>& vec) const
{
	vector<EvaluateToDouble*> rawPtrVec;

	for (int i =0; i < GetNumArgs(); i++)
	{
		rawPtrVec.push_back(vec.at(i).get());
	}
	
	return PrintFunction(rawPtrVec);
}