#Makefile snippet
#Allows concise building of various MutableFunctions
#Compiler
CXX = g++
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic $(debug_or_optimize) 

#Allows the makefile in the root directory to look here 
VPATH += :MutableFunctions

EvaluateToDoubleCore = EvaluateToDouble.cpp SimpleDouble.cpp VariableDouble.cpp

FunctionCore = FunctionEvaluator.cpp Function.cpp $(EvaluateToDoubleCore)
