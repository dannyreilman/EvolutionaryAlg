#include "MutableFunctionSubject.h"
#include "EvaluateToDouble.h"
#include "SimpleDouble.h"

#include <cmath>

static double BREVITY_WEIGHT = 0.1;

MutableFunctionSubject::MutableFunctionSubject(MutationOptions* options_in, ValueSupplier* generator_in)
: options(options_in), generator(generator_in)
{
	MutableFuncObject = std::unique_ptr<MutableFuncs::EvaluateToDouble>(new MutableFuncs::SimpleDouble());
	options->validInputMutations.clear();
	
	for(auto it = generator->PeakVariables().cbegin(); it !=  generator->PeakVariables().cend(); ++it)
	{
		options->validInputMutations.push_back(*it);
	}
}

void MutableFunctionSubject::Mutate()
{
	MutableFuncs::EvaluateToDouble::MutatePointer(MutableFuncObject, *options);
}

double MutableFunctionSubject::Evaluate()
{
	const std::unordered_map<char, double>* variables = generator->GetValue().first;
	double correctResult = generator->GetValue().second;
	double result = MutableFuncObject->GetDouble(*variables);
	return 1.0 / ((abs(correctResult - result) * BREVITY_WEIGHT * MutableFuncObject->GetHeight()));
}

std::unique_ptr<EvoAlg::Subject> MutableFunctionSubject::Clone()
{
	MutableFunctionSubject* toReturn(new MutableFunctionSubject(options, generator));
	toReturn->MutableFuncObject = move(MutableFuncObject->Clone());
	return std::unique_ptr<EvoAlg::Subject>(toReturn);
}