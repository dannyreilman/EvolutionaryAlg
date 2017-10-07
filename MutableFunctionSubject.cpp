#include "MutableFunctionSubject.h"
#include "EvaluateToDouble.h"
#include "SimpleDouble.h"
#include "ValueSupplier.h"
#include "MutationOptions.h"

#include <cmath>
#include <iostream>

static double BREVITY_WEIGHT = 10;
static double DOUBLE_SHRINK_WEIGHT = 0.1;

//Loss function used
static double Loss(double incorrect, double correct)
{
	//Square loss
	return std::pow(incorrect - correct, 2.0) / 2.0;
}

MutableFunctionSubject::MutableFunctionSubject(): options(nullptr), generator(nullptr), mutableFuncObject(nullptr) {}

MutableFunctionSubject::MutableFunctionSubject(MutableFunctionSubject&& other): options(other.options), generator(other.generator), 
                                                            mutableFuncObject(std::move(other.mutableFuncObject)) { }

MutableFunctionSubject::MutableFunctionSubject(MutableFuncs::MutationOptions *options_in, ValueSupplier *generator_in): options(options_in), generator(generator_in)
{
    mutableFuncObject = std::move(std::unique_ptr<MutableFuncs::EvaluateToDouble>(new MutableFuncs::SimpleDouble(0)));
	options->validInputMutations.clear();
	
	for(auto it = generator->PeakVariables().cbegin(); it !=  generator->PeakVariables().cend(); ++it)
	{
		options->validInputMutations.push_back(*it);
	}
}

void MutableFunctionSubject::Mutate()
{
	int size = mutableFuncObject->GetSize();
	MutableFuncs::EvaluateToDouble::MutatePointer(mutableFuncObject, *options, size);
}

double MutableFunctionSubject::Evaluate()
{
	std::vector<std::unordered_map<char, double> >* variables = generator->GetValues().first;
	std::vector<double>* values = generator->GetValues().second;	
	
	double average = 0;
	for(unsigned int i = 0; i < values->size(); ++i)
	{	
		average += Loss(mutableFuncObject->GetDouble((*variables)[i]), (*values)[i]);
	}

	average /= values->size();

	//This brevity weight term acts as a normalizing factor to prevent overfitting and large expressions
	return average 
		+ BREVITY_WEIGHT * (double)mutableFuncObject->GetSize()
		+ DOUBLE_SHRINK_WEIGHT * sqrt((double)mutableFuncObject->GetCost());
}

void MutableFunctionSubject::Print(std::ostream& out) const
{
    out << mutableFuncObject->Print();
}

std::unique_ptr<EvoAlg::Subject> MutableFunctionSubject::Clone()
{
	MutableFunctionSubject* toReturn(new MutableFunctionSubject(options, generator));
	toReturn->mutableFuncObject = move(mutableFuncObject->Clone());
	return std::unique_ptr<EvoAlg::Subject>(toReturn);
}