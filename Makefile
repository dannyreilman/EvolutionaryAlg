#Makefile 
#Allows concise building of EvoAlg 
MutableFuncDriverName = FunctionBuilder

include MutableFunctions/Makefile

#Compiler
CXX = g++

MutableFunctionsFlag = -I../EvoAlg/MutableFunctions

#Flag to include breakpoints
debug_or_optimize = -g

#Other useful flags 
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic $(debug_or_optimize) 

Driver: MutableFuncDriver.cpp $(FunctionEvaluatorCore) $(AlgebraFunctions)
	$(CXX) $(MutableFunctionsFlag) $(CXXFLAGS) $^ -o $(MutableFuncDriverName)

clean: 
	del *.exe /s