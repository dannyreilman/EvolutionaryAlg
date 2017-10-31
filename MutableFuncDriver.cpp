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
 * 		More complete documentation can be found in MutableFunctions/Generator.cpp
 * By Danny Reilman <reilman@umich.edu>
 */
 
//Type to hold all objects that can be evaluated
#include "Generator.h"

#include <iostream>

using namespace std;

int main()
{
	MutableFuncs::Generator generator;
	generator.LoadMutationValues("DefaultMutationValues.txt");

	bool running = true;
	
	while(running)
	{
		cout << ">";

		running = generator.Run(cin);
	}
}
