/*
 * Tests to debug Addition and generic Function evaluators
 * Each test case will throw a string equal to its header if
 * the test is not passed (for printing purposes)
 * 
 * By Danny Reilman <reilman@umich.edu>
 */

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Addition.h"
#include "SimpleDouble.h"

using namespace std;

void addition_test_simple();
void addition_test_function_evaluator();

int main() {
    try
    {
        addition_test_simple();
        addition_test_function_evaluator();
        cout << "All tests passed" << endl; 
    }
    catch(const char* s)
    {
        cout << "Test: " << s << " failed" << endl;
    }
    catch(...)
    {
        cout << "Something went wrong" << endl;
    }
}

void addition_test_simple()
{
    const Addition add;
    const Function* func = &add;

    vector<EvaluateToDouble*> constants;
    vector<EvaluateToDouble*>* constantsPtr = &constants;

    SimpleDouble firstItemToPushBack(5);
    SimpleDouble secondItemToPushBack(4);

    constantsPtr->push_back(&firstItemToPushBack);
    constantsPtr->push_back(&secondItemToPushBack);

    double result = func->Eval(*constantsPtr);
    
    if(result != 9)
    {
        throw "addition_test_simple";
    }

    cout << "addition_test_simple passed!" << endl;
}

void addition_test_function_evaluator()
{
    unique_ptr<EvaluateToDouble> arg1(new SimpleDouble(0));
    unique_ptr<EvaluateToDouble> arg2(new SimpleDouble(5));

    unique_ptr<vector<unique_ptr<EvaluateToDouble>>> args(new vector<unique_ptr<EvaluateToDouble>>());
    args->push_back(move(arg1));
    args->push_back(move(arg2));

    unique_ptr<Function> func(new Addition());

    FunctionEvaluator evaluator(move(args), move(func));
    
    if(evaluator.GetDouble() != 5)
    {
        throw "addition_test_function_evaluator";
    }

    cout << "addition_test_function_evaluator passed!" << endl;
}
