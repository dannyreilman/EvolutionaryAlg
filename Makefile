#Makefile 
#Allows concise building of various EvoAlg tests

#Compiler
CXX = g++

#Flag to include breakpoints
debug_or_optimize = -g

#Other useful flags 
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 $(debug_or_optimize)

EvaluateToDoubleCore = EvaluateToDouble.cpp SimpleDouble.cpp 

FunctionCore = Function.cpp Addition.cpp FunctionWithIdentity.cpp $(EvaluateToDoubleCore)

FunctionEvaluatorCore = FunctionEvaluator.cpp $(FunctionCore)

Addition_test.exe: Addition_test.cpp $(FunctionEvaluatorCore)
	$(CXX) $(CXXFLAGS) $^ -o $@
