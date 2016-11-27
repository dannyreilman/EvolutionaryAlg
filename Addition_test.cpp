/*
 * Tests to debug Addition and generic Function evaluators
 * Each test case will throw a StringException with information on the function that failed if
 * the test is not passed
 * 
 * By Danny Reilman <reilman@umich.edu>
 */

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "StringException.h"

#include "Addition.h"
#include "SimpleDouble.h"

using namespace std;
using namespace MutableFuncs;

void addition_test_simple();
void addition_test_function_evaluator();
void addition_test_function_compounding();

int main() {
    try
    {
        addition_test_simple();
        addition_test_function_evaluator();
        addition_test_function_compounding();
        
        cout << "All tests passed" << endl; 
    }
    catch(const StringException& e)
    {
        cout << "Test: " << e.Function() << " failed" << endl;
        cout << "Reason: " << e.Reason() << endl;
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

    SimpleDouble firstItemToPushBack(5);

    SimpleDouble secondItemToPushBack(4);

    constants.push_back(&firstItemToPushBack);
    constants.push_back(&secondItemToPushBack);

    double result = func->Eval(constants);
    
    if(result != 9)
    {
        throw StringException("addition_test_simple", "incorrect result");
    }

    cout << "addition_test_simple passed!" << endl;
}

void addition_test_function_evaluator()
{
    unique_ptr<EvaluateToDouble> arg1(new SimpleDouble(0));
    unique_ptr<EvaluateToDouble> arg2(new SimpleDouble(5));

    unique_ptr<vector<unique_ptr<EvaluateToDouble>>> args(new vector<unique_ptr<EvaluateToDouble> >());
    args->push_back(move(arg1));
    args->push_back(move(arg2));

    unique_ptr<Function> func(new Addition());

    FunctionEvaluator evaluator(move(args), move(func));
    
    if(evaluator.GetDouble() != 5)
    {
        throw StringException("addition_test_function_evaluator", "incorrect result");
    }

    cout << "addition_test_function_evaluator passed!" << endl;
}

void addition_test_function_compounding()
{
    unique_ptr<EvaluateToDouble> base1(new SimpleDouble(1));
    unique_ptr<EvaluateToDouble> base2(new SimpleDouble(2));
    unique_ptr<EvaluateToDouble> base3(new SimpleDouble(3));
    unique_ptr<EvaluateToDouble> base4(new SimpleDouble(4));

    unique_ptr<EvaluateToDouble> base5(new SimpleDouble(5));
    unique_ptr<EvaluateToDouble> base6(new SimpleDouble(6));
    unique_ptr<EvaluateToDouble> base7(new SimpleDouble(7));
    unique_ptr<EvaluateToDouble> base8(new SimpleDouble(8));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args1(new vector<unique_ptr<EvaluateToDouble> >());

    args1->push_back(move(base1));
    args1->push_back(move(base2));

    unique_ptr<Function> add1(new Addition());

    unique_ptr<EvaluateToDouble> addLayer1_1(new FunctionEvaluator(move(args1), move(add1)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args2(new vector<unique_ptr<EvaluateToDouble> >());

    args2->push_back(move(base3));
    args2->push_back(move(base4));

    unique_ptr<Function> add2(new Addition());

    unique_ptr<EvaluateToDouble> addLayer1_2(new FunctionEvaluator(move(args2), move(add2)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args3(new vector<unique_ptr<EvaluateToDouble> >());

    args3->push_back(move(base5));
    args3->push_back(move(base6));

    unique_ptr<Function> add3(new Addition());

    unique_ptr<EvaluateToDouble> addLayer1_3(new FunctionEvaluator(move(args3), move(add3)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args4(new vector<unique_ptr<EvaluateToDouble> >());

    args4->push_back(move(base7));
    args4->push_back(move(base8));

    unique_ptr<Function> add4(new Addition());

    unique_ptr<EvaluateToDouble> addLayer1_4(new FunctionEvaluator(move(args4), move(add4)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args5(new vector<unique_ptr<EvaluateToDouble> >());

    args5->push_back(move(addLayer1_1));
    args5->push_back(move(addLayer1_2));

    unique_ptr<Function> add5(new Addition());

    unique_ptr<EvaluateToDouble> addLayer2_1(new FunctionEvaluator(move(args5), move(add5)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args6(new vector<unique_ptr<EvaluateToDouble> >());

    args6->push_back(move(addLayer1_3));
    args6->push_back(move(addLayer1_4));

    unique_ptr<Function> add6(new Addition());

    unique_ptr<EvaluateToDouble> addLayer2_2(new FunctionEvaluator(move(args6), move(add6)));

    unique_ptr<vector<unique_ptr<EvaluateToDouble> > > args7(new vector<unique_ptr<EvaluateToDouble> >());

    args7->push_back(move(addLayer2_1));
    args7->push_back(move(addLayer2_2));

    unique_ptr<Function> add7(new Addition());

    unique_ptr<EvaluateToDouble> addLayer3(new FunctionEvaluator(move(args7), move(add7)));

    double result = addLayer3->GetDouble();

    if(result != 36)
    {
        cout << "Incorrect result: " << result << endl; 
        throw StringException("addition_test_function_compounding", "incorrect result");
    }

    cout << "addition_test_function_compounding passed!" << endl;
}
