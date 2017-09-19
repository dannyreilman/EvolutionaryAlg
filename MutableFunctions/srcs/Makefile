#Makefile snippet
#Allows concise building of various MutableFunctions
#Compiler
CXX = g++
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic
BINPATH = ../bin/
SOURCEPATH = MutableFunctions/srcs

define compile
$(CXX) -o $(addprefix $(BINPATH), $@) $< -c $(CXXFLAGS) -I $(SOURCEPATH)
endef

all: EvaluateToDouble.o SimpleDouble.o FunctionEvaluator.o VariableDouble.o Function.o

EvaluateToDouble.o: EvaluateToDouble.cpp EvaluateToDouble.h MutationOptions.h
	$(compile)
	
SimpleDouble.o: SimpleDouble.cpp SimpleDouble.h MutationOptions.h EvaluateToDouble.h
	$(compile) 

FunctionEvaluator.o: FunctionEvaluator.cpp FunctionEvaluator.h FunctionEnum.h EvaluateToDouble.h
	$(compile) 

VariableDouble.o: VariableDouble.cpp VariableDouble.h EvaluateToDouble.h
	$(compile)

Function.o: Function.cpp Function.h MutationOptions.h FunctionEnum.h EvaluateToDouble.h
	$(compile) 

