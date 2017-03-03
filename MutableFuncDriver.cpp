/**
 * A command line interface for working with MutableFunc objects and for testing various elements manually
 *
 * Valid commands are:
 * 		quit: ends the program
 *		print: prints all variables or parseable objects later in the line, will print an 
 * 			   error message if the element cannot be printed
 *
 * By Danny Reilman <reilman@umich.edu>
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <cassert>

#include "Addition.h"
#include "SimpleDouble.h"
#include "FunctionEvaluator.h"
#include "FunctionFactory.h"

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::endl;
using std::move;
using std::stringstream;
using std::unique_ptr;

using namespace MutableFuncs;

struct Workspace
{
	map<string, unique_ptr<EvaluateToDouble> > variables;
	unique_ptr<EvaluateToDouble> ans;
	vector<double> inputs;
};

static bool IsNumber(const string& s) { return s[0] == '.' || std::isdigit(s[0]);}
static bool CheckVariableName(const string& s);
static double ParseDouble(const string& s);

/**
 *Interprets an object term 
 *This term could be a number(simple double), a variable, or a function call
 *If the term is a variable, one of two things will happen based on the copy parameter
 *		true:		the variable remains in place and is cloned
 *		false: 		ownership of the variable is passed to the caller, and the variable is removed from variables
 *If this term cannot be parsed, invalid_argument will be thrown
 */
static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy, const string& term);
static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy);

//Prints all terms found in terms by extracting until nothing is left
//If something cannot be parsed, the system will attempt to continue
static void PrintCommand(std::istream& terms, Workspace& space);

//Works same as print but evaluates each term instead of printing each term
static void EvalCommand(std::istream& terms, Workspace& space);

/**
 * Saves the next term interpreted as either a variable, a generate function, or a number into the term after that,
 * in other words
 *
 * save 10 x 						will leave x as 10
 * save y x 						will leave x as a copy of y, and not change y
 * save gen addition 0 1 x 			will save (0 + 1) into x, since gen addition 0 1 will evaluate to (0+1)
 *
 * If incorrect syntax is given, or any term cannot be parsed, invalid_argument will be thrown
 */
static void SaveOrMove(std::istream& terms, Workspace& space, bool copy);
static void SaveCommand(std::istream& terms, Workspace& space)
{
	SaveOrMove(terms, space, true);
}

//Same as save, except objects change ownership instead of being cloned
static void MoveCommand(std::istream& terms, Workspace& space)
{
	SaveOrMove(terms, space, false);
}

/**
 * Generates the type of functionEvaluator described by the next term, with arguments passed in later terms.
 * The result is stored in ans
 * For example
 * 
 * gen add 1 2				will return (1 + 2)
 * gen add x 2				will return (x + y)
 *
 * If incorrect syntax is given, or any term cannot be parsed, invalid_argument will be thrown
 * 
 * This function is can also be used in place of a variable, in which case instead of the result being stored in ans, the
 * command will evaluate to the result
 *
 * nested example:
 *
 * gen add gen add 1 2 gen add 3 4 		will return ((1 + 2) + (3 + 4))
 */
static unique_ptr<EvaluateToDouble> GenerateCommand(std::istream& terms, Workspace& space, bool copy);

int main()
{
	bool running = true;
	string input;

	Workspace space;

	while(running)
	{
		cout << ">";

		getline(cin, input); 

		std::stringstream lineParse(input);
		std::stringstream lineParseCopy(input);
		string term;
		int termNum = 0;

		try{
			while(lineParse >> term && running)
			{
				++termNum;

				if(term.compare("quit") == 0)
				{
					running = false;
				}
				else if(term.compare("print") == 0)
				{
					PrintCommand(lineParse, space);
				}
				else if(term.compare("save") == 0)
				{
					SaveCommand(lineParse, space);
				}
				else if(term.compare("move") == 0)
				{
					MoveCommand(lineParse, space);
				}
				else if(term.compare("eval") == 0)
				{
					EvalCommand(lineParse, space);
				}
				else
				{
					space.ans = InterpretObject(lineParse, space, true, term);
				}
				//End of term
			}
			//End of line
		}
		catch(const std::invalid_argument& e)
		{
			cout << "Your command reached a fatal syntactical error. Please check your syntax and try again." << endl;
		}
	}
}

/*
 * Variables are acceptable if they cannot be interpreted as a number, and are not on the following list
 * [gen, combine, ans]
 * This list is the list of commands that return an evaluateToDouble and therefore are interpreted as ans
 * 		object for parsing purposes
 */
static bool CheckVariableName(const string& s)
{
	return !(IsNumber(s) || s.compare("combine") == 0 || s.compare("gen") == 0 || s.compare("ans") == 0);
}

static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy, const string& term)
{
	if(IsNumber(term))
	{
		double parsed = ParseDouble(term);
		unique_ptr<EvaluateToDouble> temp(new SimpleDouble(parsed));
		return move(temp);
	}
	else if(term.compare("ans") == 0)
	{
		if(copy)
		{
			return space.ans->Clone();
		}
		else
		{
			return move(space.ans);
		}
	}
	else if(term.compare("gen") == 0)
	{
		return move(GenerateCommand(terms, space, true));
	}
	else if(term.compare("combine") == 0)
	{
		return move(GenerateCommand(terms, space, false));
	}
	else if(space.variables.find(term) != space.variables.end())
	{
		if(copy)
		{
			return space.variables.at(term)->Clone();
		}
		else
		{
			 unique_ptr<EvaluateToDouble> toReturn = move(space.variables.at(term));
			 space.variables.erase(term);
			 return toReturn;
		}
	}
	else
	{
		throw std::invalid_argument("Term could not be read");
	}
}

static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy)
{
	string term;
	if(terms >> term)
	{
		return InterpretObject(terms, space, copy, term);
	}
	else
	{
		throw std::invalid_argument("End of line found prematurely");
	}
}

static void PrintCommand(std::istream& terms, Workspace& space)
{
	string term;

	while(terms >> term)
	{
		if(term.compare("all") == 0)
		{
			if(space.ans)
			{
				cout << "ans:\t" << space.ans->Print() << endl;
			}
			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				cout << it->first << ":\t" << it->second->Print() << endl;
			}
		}
		else if(term.compare("ans") == 0)
		{
			if(space.ans)
			{
				cout << space.ans->Print() << endl;
			}
			else
			{
				cout << "Nothing is in ans yet, call a generating function first." << endl;
			}
		}
		else if(IsNumber(term))
		{
			cout << ParseDouble(term) << endl;
		}
		else if(space.variables.find(term) != space.variables.end())
		{
			cout << space.variables.at(term)->Print() << endl;
		}
		else
		{
			cout << "I can't find a variable or command called " << term << ", ignoring..." << endl;
		}
	}
}

static void EvalCommand(std::istream& terms, Workspace& space)
{
	string term;

	while(terms >> term)
	{
		if(term.compare("all") == 0)
		{
			if(space.ans)
			{
				cout << "ans:\t" << space.ans->GetDouble() << endl;
			}
			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				cout << it->first << ":\t" << it->second->Print() << endl;
			}
		}
		else if(term.compare("ans") == 0)
		{
			if(space.ans)
			{
				cout << space.ans->Print() << endl;
			}
			else
			{
				cout << "Nothing is in ans yet, call a generating function first." << endl;
			}
		}
		else if(IsNumber(term))
		{
			cout << ParseDouble(term) << endl;
		}
		else if(space.variables.find(term) != space.variables.end())
		{
			cout << space.variables.at(term)->Print() << endl;
		}
		else
		{
			cout << "I can't find a variable or command called " << term << ", ignoring..." << endl;
		}
	}
}

static void SaveOrMove(std::istream& terms, Workspace& space, bool copy)
{
	
	unique_ptr<EvaluateToDouble> toBeSaved = InterpretObject(terms, space, copy);

	string term2;
	if(terms >> term2 && CheckVariableName(term2))
	{
		space.variables[term2] = move(toBeSaved);
	}
	else
	{
		throw std::invalid_argument("Variable name not allowed");
	}
}


static unique_ptr<EvaluateToDouble> GenerateCommand(std::istream& terms, Workspace& space, bool copy)
{
	string term1;
	FunctionEnum funcEnum;
	
	if(terms >> term1)
	{
		if(term1.compare("add") == 0 || term1.compare("addition") == 0)
		{
			funcEnum = FunctionEnum::Addition;
		}
		else
		{
			throw std::invalid_argument("Not implemented function found");
		}
	}
	else
	{
		throw std::invalid_argument("End of line found prematurely");
	}

	vector<unique_ptr<EvaluateToDouble> > args;

	for(int i = 0; i < FunctionFactory::GetSupportedArgs(funcEnum); ++i)
	{
		args.push_back(InterpretObject(terms, space, copy));
	}

	unique_ptr<EvaluateToDouble> top(new FunctionEvaluator(args.begin(), args.end(), funcEnum));
	return move(top);
}

//Reads doubles from a string, stops reading if something is reached that cannot be parsed
// 1.0 returns 1
// .5 return 0.5
// 1. returns 1
//1..9 returns 1 (.9 is skipped because the second decimal cannot be parsed)
static double ParseDouble(const string& in)
{
	double returnDouble;
	
	bool beforeDecimal = true;
	int decimalIndex = -1;

	bool good = true;

	for(unsigned int i = 0; i < in.size() && good; ++i)
	{
		if((in[i] == '.') && beforeDecimal)
		{
			beforeDecimal = false;
			decimalIndex = i;
			
			returnDouble = 0;
			stringstream parser(in.substr(0,i));
			parser >> returnDouble;
		}
		else if(!std::isdigit(in[i]))
		{
			good = false;
		}
	}

	if(beforeDecimal)
	{
		stringstream parser(in);
		parser >> returnDouble; 
	}
	else
	{
		double value;
		//This is the number of digits past the decimal point
		int numDigits = in.size() - decimalIndex - 1;
		
		if(numDigits != 0)
		{
			stringstream parser(in.substr(decimalIndex + 1));
			parser >> value;

			value /= (numDigits * 10);

			returnDouble += value;
		}
	}
	return returnDouble;
}

