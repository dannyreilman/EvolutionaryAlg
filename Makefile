#Makefile 
#Allows concise building of EvoAlg 
MutableFuncDriverName = FunctionBuilder

include MutableFunctions/Makefile

#Compiler
CXX = g++

MutableFunctionsFlag = -I../EvoAlg/MutableFunctions
EvolutionaryFlag = -I../EvoAlg/EvolutionaryAlgorithm

#Flag to include breakpoints
debug_or_optimize = -g

#Other useful flags 
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic $(debug_or_optimize) 

Driver: MutableFuncDriver.cpp $(FunctionCore) 
	$(CXX) $(CXXFLAGS) $(MutableFunctionsFlag) $^ -o $(MutableFuncDriverName)

SimulationTest.exe: SimulationTest.cpp MutableFunctionSubject.cpp FunctionSupply.cpp $(FunctionCore) 
	$(CXX) $(CXXFLAGS) $(MutableFunctionsFlag)  $(EvolutionaryFlag) $^ -o $@

clean: 
	del *.exe /s