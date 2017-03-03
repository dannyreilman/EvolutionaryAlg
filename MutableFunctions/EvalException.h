#ifndef EVAL_EXCEPTION_H
#define EVAL_EXCEPTION_H

#include <string>
#include "StringConversion.h"
using std::string;

namespace MutableFuncs
{
	class EvalException : public std::exception
	{
	public:
		EvalException(int numArgsGiven_in, int numArgsNeeded_in, const std::string& function_in, const std::string& message_in) : numArgsGiven(numArgsGiven_in), numArgsNeeded(numArgsNeeded_in), function(function_in), message(message_in) 
		{SetFullWhatMessage(true); }

		EvalException(int numArgsGiven_in, int numArgsNeeded_in, const std::string& function_in) : numArgsGiven(numArgsGiven_in), numArgsNeeded(numArgsNeeded_in), function(function_in), message("")
		{SetFullWhatMessage(false); }

		~EvalException() throw () {}
		
		const char* what() const throw()  
		{
			return fullWhatMessage.c_str();
		}
		
	private:
		int numArgsGiven;
		int numArgsNeeded;
		string function;
		string message;
		
		string fullWhatMessage;

		void SetFullWhatMessage(bool messagePassed)
		{
			fullWhatMessage = function + " does not accept " + to_string(numArgsGiven) + " arguments, " + to_string(numArgsNeeded) + " arguments are required.";

			if(messagePassed)
			{
				fullWhatMessage += "\nError message: " + message;
			}
		}
	};
}
#endif