/*
 * Testing for functions used to help build function hierarchies
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

int main()
{
    try
    {
        
    }
    catch(const StringException& e)
    {
        cout << "Test: " << e.Function() << " failed" << endl;
    }
    catch(...)
    {
        cout << "Something went wrong" << endl;
    }
}