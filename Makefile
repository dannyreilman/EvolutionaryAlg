#Makefile 
#Allows concise building of various EvoAlg tests

#Compiler
CXX = g++

#Flag to include breakpoints
debug_or_optimize = -g

#Other useful flags 
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 $(debug_or_optimize)


Addition_test.exe: Addition_test.cpp Addition.cpp SimpleDouble.cpp Function.cpp FunctionEvaluator.cpp FunctionWithIdentity.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
