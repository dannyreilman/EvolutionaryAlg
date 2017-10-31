#Makefile 
#Allows concise building of EvoAlg 
MutableFuncDriverName = FunctionBuilder

#Compiler
CXX = g++

MutableFunctionsFlag = -I../EvoAlg/MutableFunctions/srcs
EvolutionaryFlag = -I../EvoAlg/EvolutionaryAlgorithm

#Flag to include breakpoints
debug_or_optimize = -g

#Other useful flags 
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic $(debug_or_optimize)

MutableFunctionAll = MutableFunctions/bin/*.o

Driver: MutableFuncDriver.cpp $(MutableFunctionAll)
	$(CXX) $(CXXFLAGS) $(MutableFunctionsFlag) $(EvolutionaryFlag) $^ -o $(MutableFuncDriverName)

SimulationTest.exe: SimulationTest.cpp MutableFunctionSubject.cpp FunctionSupply.cpp RangedFunctoralSupplier.cpp CppFunctorSupply.h $(MutableFunctionAll)
	$(CXX) $(MutableFunctionsFlag)  $(EvolutionaryFlag) $(CXXFLAGS)  $^ -o $@

clean: 
	del *.exe /s