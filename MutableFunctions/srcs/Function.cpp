#ifndef FUNCTION_FACTORYCPP
#define FUNCTION_FACTORYCPP

#include "StringException.h"

#include "Function.h"
#include "FunctionEnum.h"
#include "EvaluateToDouble.h"
#include "FunctionEvaluator.h"
#include "SimpleDouble.h"
#include "VariableDouble.h"

#include <memory>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

/*
 * Useful enums for choosing function types, as well as information about how many args can be passed 
 *
 * By Danny Reilman <reilman@umich.edu>
 */

static int ADDITION_SUPPORTED_ARGS = 2;
static int SUBTRACTION_SUPPORTED_ARGS = 2;
static int MULTIPLICATION_SUPPORTED_ARGS = 2;
static int DIVISION_SUPPORTED_ARGS = 2;

static double ADDITION_IDENTITY = 0.0;
static double SUBTRACTION_IDENTITY = 0.0;
static double MULTIPLICATION_IDENTITY = 1.0;
static double DIVISION_IDENTITY = 1.0;

static std::string ADDITION_COMMAND = "add";
static std::string SUBTRACTION_COMMAND = "sub";
static std::string MULTIPLICATION_COMMAND = "mult";
static std::string DIVISION_COMMAND = "div";

namespace MutableFuncs
{
	int Function::GetSupportedArgs(FunctionEnum in)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return ADDITION_SUPPORTED_ARGS;
			case FunctionEnum::Subtraction:
				return SUBTRACTION_SUPPORTED_ARGS;
			case FunctionEnum::Multiplication:
				return MULTIPLICATION_SUPPORTED_ARGS;
			case FunctionEnum::Division:
				return DIVISION_SUPPORTED_ARGS;
			default:
				throw StringException("GetFunctionInformation", "Info not implemented");
		}
		return 0;
	}

	//Arg1 is guaranteed to be safe if there exists an identity, this function asks if the second arg can be used if the first arg evaluates to identity
	//(In the case of reducing identities)
	bool Function::IsSecondArgSafe(FunctionEnum in)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return true;
			case FunctionEnum::Subtraction:
				return false;
			case FunctionEnum::Multiplication:
				return true;
			case FunctionEnum::Division:
				return false;
			default:
				throw StringException("GetFunctionInformation", "Info not implemented");
		}
		return 0;
	}

	double Function::GetIdentity(FunctionEnum in)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return ADDITION_IDENTITY;
			case FunctionEnum::Subtraction:
				return SUBTRACTION_IDENTITY;
			case FunctionEnum::Multiplication:
				return MULTIPLICATION_IDENTITY;
			case FunctionEnum::Division:
				return DIVISION_IDENTITY;
			default:
				throw StringException("GetFunctionInformation", "Info not implemented");
		}
		return 0;
	}

	std::string Function::GetGenerativeCommand(FunctionEnum in)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return ADDITION_COMMAND;
			case FunctionEnum::Subtraction:
				return SUBTRACTION_COMMAND;
			case FunctionEnum::Multiplication:
				return MULTIPLICATION_COMMAND;
			case FunctionEnum::Division:
				return DIVISION_COMMAND;
			default:
				throw StringException("GetGenerativeCommand", "Info not implemented");
		}
		return "";
	}
	

	double Function::Eval(FunctionEnum in, const std::vector< std::unique_ptr<EvaluateToDouble> >& args, const std::unordered_map<char, double>& variables)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return args[0]->GetDouble(variables) + args[1]->GetDouble(variables);
			case FunctionEnum::Subtraction:
				return args[0]->GetDouble(variables) - args[1]->GetDouble(variables);
			case FunctionEnum::Multiplication:
				return args[0]->GetDouble(variables) * args[1]->GetDouble(variables);
			case FunctionEnum::Division:
				return args[0]->GetDouble(variables) / args[1]->GetDouble(variables);
			default:
				throw StringException("Eval", "Evaluation not implemented");
		}
		return 0;
	}

	std::string Function::Print(FunctionEnum in, const std::vector<std::unique_ptr<EvaluateToDouble> >& args)
	{
		switch(in)
		{
			case FunctionEnum::Addition:
				return "(" + args[0]->Print() + " + " + args[1]->Print() + ")";
			case FunctionEnum::Subtraction:
				return "(" + args[0]->Print() + " - " + args[1]->Print() + ")";
			case FunctionEnum::Multiplication:
				return "(" + args[0]->Print() + " * " + args[1]->Print() + ")";
			case FunctionEnum::Division:
				return "(" + args[0]->Print() + " / " + args[1]->Print() + ")";
			default:
				throw StringException("Eval", "Evaluation not implemented");
		}
		return "";
	}
	
	static std::unique_ptr<EvaluateToDouble> MakeIdentity(FunctionEnum in, std::unique_ptr<EvaluateToDouble>& arg)
	{
		std::vector<std::unique_ptr<EvaluateToDouble> > arguments;
		arguments.push_back(move(arg));
		
		std::unique_ptr<EvaluateToDouble> identityArg(new SimpleDouble(Function::GetIdentity(in)));
		arguments.push_back(move(identityArg));

		std::unique_ptr<EvaluateToDouble> returnPtr(new FunctionEvaluator(arguments.begin(), arguments.end(), in));

		return move(returnPtr);
	}

	
	static std::unique_ptr<EvaluateToDouble> MakeInputIdentity(FunctionEnum in, std::unique_ptr<EvaluateToDouble>& arg, const std::vector<char>& validMutations)
	{
		std::vector<std::unique_ptr<EvaluateToDouble> > arguments;
		arguments.push_back(move(arg));
		
		int num = rand() % validMutations.size();

		std::unique_ptr<EvaluateToDouble> identityArg(new VariableDouble(validMutations[num]));
		arguments.push_back(move(identityArg));

		std::unique_ptr<EvaluateToDouble> returnPtr(new FunctionEvaluator(arguments.begin(), arguments.end(), in));

		return move(returnPtr);
	}


	//Sometimes causes identities to form, not changing the overall value, unless an input variable is inserted
	std::unique_ptr<EvaluateToDouble> Function::PossibleIdentity(std::unique_ptr<EvaluateToDouble>& arg, const MutationOptions& opt, int size)
	{
		//This function is based of isolating the expected value of a binomial distribution
		//E(X) = np, E(X)/n = p
		//Use definition of 1/10000
		double numIdentity = ((rand() % 10000) / 10000.0);
		int identityChoice = (rand() % opt.SumOfChances);
		int numInput = rand() % 100;

		double sum = 0;
		if(numIdentity < opt.ExpectedIdentities / size)
		{
			sum += opt.AdditionIdentityChance;
			if(identityChoice < sum)
			{
				if(numInput < opt.InputIdentityChance && opt.validInputMutations.size() > 0)
				{
					return move(MakeInputIdentity(FunctionEnum::Addition, arg, opt.validInputMutations));
				}
				return move(MakeIdentity(FunctionEnum::Addition, arg));
			}

			sum += opt.SubtractionIdentityChance;
			if(identityChoice < sum)
			{
				if(numInput < opt.InputIdentityChance && opt.validInputMutations.size() > 0)
				{
					return move(MakeInputIdentity(FunctionEnum::Subtraction, arg, opt.validInputMutations));
				}
				return move(MakeIdentity(FunctionEnum::Subtraction, arg));
			}

			sum += opt.MultiplicationIdentityChance;
			if(identityChoice < sum)
			{
				if(numInput < opt.InputIdentityChance && opt.validInputMutations.size() > 0)
				{
					return move(MakeInputIdentity(FunctionEnum::Multiplication, arg, opt.validInputMutations));
				}
				return move(MakeIdentity(FunctionEnum::Multiplication, arg));
			}

			sum += opt.DivisionIdentityChance;
			if(identityChoice < sum)
			{
				if(numInput < opt.InputIdentityChance && opt.validInputMutations.size() > 0)
				{
					return move(MakeInputIdentity(FunctionEnum::Division, arg, opt.validInputMutations));
				}
				return move(MakeIdentity(FunctionEnum::Division, arg));
			}
		}

		return move(arg);
	}
}

#endif
