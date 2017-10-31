#ifndef MUTABLE_FUNC_GENERATOR_H
#define MUTABLE_FUNC_GENERATOR_H
/**
 *  A class to encapsulate mutableFuncDriver's batch and export abilities
 *  by Danny Reilman <reilman@umich.edu>
 */

#include "EvaluateToDouble.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

using std::unordered_map;
using std::string;
using std::unique_ptr;
using std::ostream;
using std::istream;

namespace MutableFuncs
{
	class Generator
	{
	public:
		struct Workspace
		{
			unordered_map<string, unique_ptr<EvaluateToDouble> > variables;
			unique_ptr<EvaluateToDouble> ans;
			unordered_map<char, double> inputs;

			MutationOptions options;
		};
		
		Generator(ostream& output = std::cout) 
		: output(&output) {}

		//Load mutationValues from a file
		void LoadMutationValues(string filename);

		/**
		 * Run will simulate commands 
		 */
		bool Run(istream& commands);
		unique_ptr<EvaluateToDouble> CopyObject(string name);

	private:
		Workspace space;
		ostream* output;
	};
}
#endif