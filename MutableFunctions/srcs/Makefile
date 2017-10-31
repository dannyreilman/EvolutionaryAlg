#Makefile snippet
#Allows concise building of various MutableFunctions
#Compiler
CXX = g++
CXXFLAGS = -Wall -Werror --std=c++11 -pedantic
OPTIMIZE = -O3
DEBUG = -g
BINPATH = ../bin/
SOURCEPATH = MutableFunctions/srcs

define compile
$(CXX) -o $(addprefix $(BINPATH), $@) $< -c $(CXXFLAGS) -I $(SOURCEPATH)
endef

debug: CXXFLAGS += $(DEBUG)
debug: all
release: CXXFLAGS += $(OPTIMIZE)
release: all

all: EvaluateToDouble.o SimpleDouble.o FunctionEvaluator.o VariableDouble.o Function.o Generator.o

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

Generator.o: Generator.cpp EvaluateToDouble.h SimpleDouble.h FunctionEvaluator.h VariableDouble.h EvaluateToDouble.h
	$(compile) 
