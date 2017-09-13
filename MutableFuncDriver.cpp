/**
 * A command line interface for working with MutableFunc objects and for testing various elements manually
 *
 * Valid commands are:
 * 		quit: ends the program
 *		print: prints all variables, all input variables, or parseable objects later in the line, will print an 
 * 			   error message if the element cannot be printed
 *		save: Copies argument 1 into argument 2 
 *		move: Moves argument 1 into argument 2
 *		eval: Prints the evaluation of the arguments given
 *		input: Set the input variable named arg1 to be equal to the evaluation of arg2
 *		mutate: Mutates all other arguments given
 *			(note: change will not necessarily happen when you call mutate)
 *		batch [filename]: read commands from a file as if they were given through command line
 *		export [object(s)] to [filename]: 
 *
 * To generate function evaluators and other complex arguments use the following in the place of an argument name:
 *		gen [function name] [argument list]: creates a function evaluator
 *			combine with the same usage will move the argument list into the new argument (things in argument list will be invalidated)
 *		gen input [input variable name (single char)]: creates an input variable which will take the value set through the input command
 * 
 * By Danny Reilman <reilman@umich.edu>
 */
 
//Type to hold all objects that can be evaluated
#include "EvaluateToDouble.h"

//Basic EvaluateToDouble type for simple numbers
#include "SimpleDouble.h"

//Basic EvaluateToDouble type for simple variables
#include "VariableDouble.h"

//Basic EvaluateToDouble type for function evaluation
#include "FunctionEvaluator.h"
#include "Function.h"

//Options needed to tune mutation
#include "MutationOptions.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <cassert>
#include <cmath>
#include <fstream>
#include <unordered_set>
#include <time.h>
#include <algorithm>

using std::vector;

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::move;
using std::stringstream;

using std::unique_ptr;

using namespace MutableFuncs;

struct Workspace
{
	unordered_map<string, unique_ptr<EvaluateToDouble> > variables;
	unique_ptr<EvaluateToDouble> ans;
	unordered_map<char, double> inputs;

	MutationOptions options;
};

class VariableNameSorter
{
public:
	bool operator()(std::pair<string, string> const a, std::pair<string, string > const b)
	{
		return a.first < b.first;
	}
	
	bool operator()(std::pair<string, double> const a, std::pair<string, double > const b)
	{
		return a.first < b.first;
	}
};

static bool IsNumber(const string& s) { return (s[0] == '.' || std::isdigit(s[0])) 
									|| (s[0] == '-' && (s[1] == '.' || std::isdigit(s[1])));}
static bool CheckVariableName(const string& s);
static double ParseDouble(const string& s);

static void StartLine(std::istream& terms, Workspace& space, bool& running);

/**
 * Interprets an object term 
 * This term could be a number(simple double), a variable, or a function call
 * If the term is a variable, one of two things will happen based on the copy parameter
 *		true:		the variable remains in place and is cloned
 *		false: 		ownership of the variable is passed to the caller, and the variable is removed from variables
 * If this term cannot be parsed, invalid_argument will be thrown
 */
static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy, const string& term);
static unique_ptr<EvaluateToDouble> InterpretObject(std::istream& terms, Workspace& space, bool copy);

//Prints all terms found in terms by extracting until nothing is left
//If something cannot be parsed, the system will attempt to continue
static void PrintCommand(std::istream& terms, Workspace& space);

//Works same as print but evaluates each term instead of printing each term
static void EvalCommand(std::istream& terms, Workspace& space);

//Generates an input variable with arg1 and gives it the value Eval(arg2), discarding extra terms
static void InputCommand(std::istream& terms, Workspace& space);

//Works similar to eval and print but calls Mutate on each term instead
static void MutateCommand(std::istream& terms, Workspace& space);

//Calls commands from a file as if they were passed through the command line
static void BatchCommand(std::istream& terms, Workspace& space);

//Exports the following objects until "to" is reached. The objects are exported to a filename listed after the to
//This file will be a batch that will generate all objects afterwards
static void ExportCommand(std::istream& terms, Workspace& space);

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
	Workspace space;

	//Load from defaultMutationValues.txt
	std::ifstream valueReader("DefaultMutationValues.txt");

	//Ignore Header
	valueReader.ignore(250, '\n');

	//Ignore Tag
	valueReader.ignore(250, ' ');
	valueReader >> space.options.simpleDoubleShift;

	
	//Functions
	valueReader.ignore(250, ' ');
	valueReader >> space.options.AdditionIdentityChance;

	valueReader.ignore(250, ' ');
	valueReader >> space.options.SubtractionIdentityChance;

	valueReader.ignore(250, ' ');
	valueReader >> space.options.MultiplicationIdentityChance;

	valueReader.ignore(250, ' ');
	valueReader >> space.options.DivisionIdentityChance;

	//end functions
	valueReader.ignore(250, ' ');
	valueReader >> space.options.InputIdentityChance;

	valueReader.ignore(250, ' ');
	valueReader >> space.options.IdentityReductionChance;

	valueReader.ignore(250, ' ');
	valueReader >> space.options.IdentityReductionWidth;

	valueReader.close();

	bool running = true;
	
	while(running)
	{
		cout << ">";

		StartLine(cin, space, running);
	}
}

//Pulls one line from instream and follows commands
static void StartLine(std::istream& instream, Workspace& space, bool& running)
{
	string input;
	getline(instream, input); 
	
	std::stringstream lineParse(input);

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
			else if(term.compare("help") == 0)
			{
				cout << "A command line interface for working with MutableFunc objects and for testing various elements manually" << endl;
				 cout << "Valid commands are:" << endl;
				 cout << "quit: ends the program" << endl;
				 cout << "print [object(s)]: prints objects later in the line" << endl;
				cout << "eval [object(s)]: Prints the evaluation of objects later in the line" << endl;
				 cout << "save [object] [variable]: Copies an object into a variable" << endl;
				 cout << "move [object] [variable]: Moves an object into a variable (object will no longer be accessible if it is a variable)" << endl;
				cout << "[object]: Stores [object] in ans (equivalent to move [object] ans" << endl;
				cout << "---" << endl;
				cout << "[object] can be a variable, gen or combine command" << endl;
				cout << "gen [function] [object1] [object2]: generates a functionEvaluator object with copies of object1 and object2 as arguments" << endl;
				cout << "combine [function] [object1] [object2]: same as gen except objects are moved over" << endl;
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
			else if(term.compare("input") == 0)
			{
				InputCommand(lineParse, space);
			}
			else if(term.compare("mutate") == 0)
			{
				MutateCommand(lineParse, space);
			}
			else if(term.compare("batch") == 0)
			{
				BatchCommand(lineParse, space);
			}
			else if(term.compare("export") == 0)
			{
				ExportCommand(lineParse, space);
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


/*
 * Variable names are acceptable if they cannot be interpreted as a number, and are not on the following list
 * [gen, combine, ans, all, input, to]
 * This list is the list of commands that return an evaluateToDouble and therefore are interpreted as ans
 * 		object for parsing purposes, as well as some keywords that are used in place of objects
 */
static bool CheckVariableName(const string& s)
{
	return !(IsNumber(s) || s.compare("combine") == 0 || 
			s.compare("gen") == 0 || s.compare("ans") == 0 || 
			s.compare("all") == 0|| s.compare("input") == 0 
			|| s.compare("to") == 0 || s.compare("sorted") == 0);
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
		else if(term.compare("sorted") == 0)
		{
			if(space.ans)
			{
				cout << "ans:\t" << space.ans->Print() << endl;
			}

			vector<std::pair<string, string> > sorted;

			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				sorted.push_back(std::make_pair(it->first, it->second->Print()));
			}
			
			std::sort(sorted.begin(), sorted.end(), VariableNameSorter());

			for(auto it = sorted.begin(); it != sorted.end(); ++it)
			{
				cout << it->first << ":\t" << it->second << endl;
			}
		}
		else if(term.compare("input") == 0)
		{
			if(space.inputs.empty())
			{
				cout << "No input variables exist yet, call \"input\" first." << endl;
			}
			else
			{
				for(auto it = space.inputs.begin(); it != space.inputs.end(); ++it)
				{
					cout << it->first << ":\t" << it->second << endl;
				}
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
				cout << "ans:\t" << space.ans->GetDouble(space.inputs) << endl;
			}
			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				cout << it->first << ":\t" << it->second->GetDouble(space.inputs) << endl;
			}
		}
		else if(term.compare("sorted") == 0)
		{
			if(space.ans)
			{
				cout << "ans:\t" << space.ans->GetDouble(space.inputs) << endl;
			}

			vector<std::pair<string, double> > sorted;
			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				string name = it->first;
				sorted.push_back(std::make_pair(name, it->second->GetDouble(space.inputs)));
			}
			
			std::sort(sorted.begin(), sorted.end(), VariableNameSorter());

			for(auto it = sorted.begin(); it != sorted.end(); ++it)
			{
				cout << it->first << ":\t" << it->second << endl;
			}
		}
		else if(term.compare("ans") == 0)
		{
			if(space.ans)
			{
				cout << space.ans->GetDouble(space.inputs) << endl;
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
			cout << space.variables.at(term)->GetDouble(space.inputs) << endl;
		}
		else
		{
			cout << "I can't find a variable or command called " << term << ", ignoring..." << endl;
		}
	}
}

static void MutateCommand(std::istream& terms, Workspace& space)
{
	string term;
	srand(time(NULL));

	while(terms >> term)
	{
		if(term.compare("all") == 0)
		{
			if(space.ans)
			{
				EvaluateToDouble::MutatePointer(space.ans, space.options);
			}

			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				EvaluateToDouble::MutatePointer(it->second, space.options);
			}
		}
		else if(term.compare("ans") == 0)
		{
			if(space.ans)
			{
				EvaluateToDouble::MutatePointer(space.ans, space.options);
			}
			else
			{
				cout << "Nothing is in ans yet, call a generating function first." << endl;
			}
		}
		else if(IsNumber(term))
		{
			cout << "Error, mutation cannot be called on a literal." << endl;
		}
		else if(space.variables.find(term) != space.variables.end())
		{
			EvaluateToDouble::MutatePointer(space.variables.find(term)->second, space.options);
		}
		else
		{
			cout << "I can't find a variable or command called " << term << ", ignoring..." << endl;
		}
	}
}

static void InputCommand(std::istream& terms, Workspace& space)
{
	string term;

	terms >> term;
	char name = term[0];
	if(term.size() > 1)
	{
		cout << "WARNING: input variables can only have single character names, at least one extra character was discarded" << endl;
	}

	double initialValue = 0;
	if(terms)
	{
		initialValue = InterpretObject(terms, space, true)->GetDouble(space.inputs);
	}

	space.inputs[name] = initialValue;
	if(space.inputs.size() > space.options.validInputMutations.size())
	{
		space.options.validInputMutations.push_back(name);
	}
}

static void BatchCommand(std::istream& terms, Workspace& space)
{
	string fileName;
	terms >> fileName;
	std::ifstream batchReader(fileName);

	bool running = true;

	while(batchReader && running)
	{
		StartLine(batchReader, space, running);
	}
}

static void ExportCommand(std::istream& terms, Workspace& space)
{
	unordered_set<string> toBeExported;
	
	string term;
	while(terms >> term && term.compare("to") != 0)
	{
		if(CheckVariableName(term))
		{
			toBeExported.insert(term);
		}
		else if(term.compare("all") == 0)
		{
			for(auto it = space.variables.begin(); it != space.variables.end(); ++it)
			{
				toBeExported.insert(it->first);
			}
		}
	}

	string fileName;
	terms >> fileName;
	
	std::ofstream exporter(fileName);

	if(exporter.good())
	{
		for(auto it = toBeExported.begin(); it != toBeExported.end(); ++it)
		{
			EvaluateToDouble::ExportPointer(space.variables[*it], *it, exporter);
		}
	}
	else
	{
		cout << "Something went wrong opening the export file" << endl;
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
		if(term1.compare("input") == 0)
		{
			char variableName;
			terms >> variableName;
			unique_ptr<EvaluateToDouble> toReturn =  unique_ptr<EvaluateToDouble>(new VariableDouble(variableName, space.inputs));
			
			if(space.inputs.size() > space.options.validInputMutations.size())
			{
				space.options.validInputMutations.push_back(variableName);
			}

			return toReturn;
		}
		else if(term1.compare("add") == 0 || term1.compare("addition") == 0)
		{
			funcEnum = FunctionEnum::Addition;
		}
		else if(term1.compare("sub") == 0 || term1.compare("subtraction") == 0)
		{
			funcEnum = FunctionEnum::Subtraction;
		}
		else if(term1.compare("mult") == 0 || term1.compare("multiplication") == 0)
		{
			funcEnum = FunctionEnum::Multiplication;
		}
		else if(term1.compare("div") == 0 || term1.compare("division") == 0)
		{
			funcEnum = FunctionEnum::Division;
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

	for(int i = 0; i < Function::GetSupportedArgs(funcEnum); ++i)
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
	unsigned int i = 0;
	bool negative = false;
	if(in[0] == '-')
	{
		negative = true;
		//start at 1
		i = 1;
	}

	double returnDouble;
	
	bool beforeDecimal = true;
	int decimalIndex = -1;

	bool good = true;
	
	for(; i < in.size() && good; ++i)
	{
		if((in[i] == '.') && beforeDecimal)
		{
			beforeDecimal = false;
			decimalIndex = i;
			
			returnDouble = 0;
			stringstream parser(in.substr( negative ? 1 : 0 , i));
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

			value /= pow(10, numDigits);

			returnDouble += value;
		}
	}
	return returnDouble * (negative ? -1 : 1);
}

