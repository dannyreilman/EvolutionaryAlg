#ifndef VARIABLE_DOUBLE_H
#define VARIABLE_DOUBLE_H

/**
 * A class to hold variables
 * By Danny Reilman <reilman@umich.edu>
 */

#include "EvaluateToDouble.h"

#include <unordered_map>

namespace MutableFuncs
{
class VariableDouble : public EvaluateToDouble
{
public:
	VariableDouble(char variableName_in) : variableName(variableName_in) {}

	//A constructor to automatically instantiate the variable
	VariableDouble(char variableName_in, std::unordered_map<char, double>& variables);

	virtual double GetDouble(const std::unordered_map<char, double>& variables) const;
	
	virtual std::string Print() const;
	
	virtual std::unique_ptr<EvaluateToDouble> Clone() const;
	
	virtual void Mutate(MutationOptions& opt);

	virtual void ExportBatch(std::ostream& out) const;        	

	virtual bool IsInput() const;
	
	virtual void CollectVariables(std::unordered_set<char>& variables) const;	
private:
	char variableName;
};
}

#endif
