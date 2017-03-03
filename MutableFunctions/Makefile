#Makefile snippet
#Allows concise building of various MutableFunctions
#Compiler
CXX = g++
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic $(debug_or_optimize) 

#Allows the makefile in the root directory to look here 
VPATH += :MutableFunctions

EvaluateToDoubleCore = EvaluateToDouble.cpp SimpleDouble.cpp 

FunctionCore = FunctionFactory.cpp Function.cpp $(EvaluateToDoubleCore)

FunctionEvaluatorCore = FunctionEvaluator.cpp $(FunctionCore)

AlgebraFunctions = Addition.cpp


Addition_test.exe: Addition_test.cpp Addition.cpp $(FunctionEvaluatorCore)
	$(CXX) $(CXXFLAGS) $^ -o $@