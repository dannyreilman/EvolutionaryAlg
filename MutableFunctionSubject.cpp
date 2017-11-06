#include "MutableFunctionSubject.h"
#include "EvaluateToDouble.h"
#include "SimpleDouble.h"
#include "ValueSupplier.h"
#include "MutationOptions.h"

#include <cmath>
#include <algorithm>
#include <iostream>

//Loss is accuracyWeight(training error) + size(brevity weight + CAP_GENERATION * complexity_weight * average complexity) in the limit
static double ACCURACY_WEIGHT = 1;
static double BREVITY_WEIGHT = 0.25;

//Variables contribute 2 to complexity, doubles give up to 1
static double COMPLEXITY_WEIGHT = 0;
static double COMPLEXITY_GRAIN = 0.25;

//Loss function used
static double Loss(double incorrect, double correct)
{
	//squared hinge loss
	return std::pow(incorrect - correct, 2.0) / 2.0;
	
	//Percent Error
	//return abs(100 * (double)(incorrect - correct) / (double)correct);
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

double MutableFunctionSubject::Evaluate(int generation)
{
	std::vector<std::unordered_map<char, double> >* variables = generator->GetValues().first;
	std::vector<double>* values = generator->GetValues().second;	
	
	double average = 0;
	for(unsigned int i = 0; i < values->size(); ++i)
	{	
		average += Loss(mutableFuncObject->GetDouble((*variables)[i]), (*values)[i]) / values->size();
	}

	//Accuracy -> Loss
	//Brevity weight -> Normalization using Number of elements
	//Complexity Weight -> Normalization based on roundness of numbers, scales up and caps at cap generation
	//averageComplexity-> variables give 2, numbers give between 0 and 1
	double averageComplexity = mutableFuncObject->GetComplexity(COMPLEXITY_GRAIN) / (mutableFuncObject->GetSize() * COMPLEXITY_GRAIN);

	//(Wa + WcAvg * C + Wb * b)a
	return average *
		(ACCURACY_WEIGHT + mutableFuncObject->GetSize() *
		(BREVITY_WEIGHT +  COMPLEXITY_WEIGHT * averageComplexity));
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