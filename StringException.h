#ifndef STRINGEXCEPTION_H
#define STRINGEXCEPTION_H

#include <string>

/*
 * Exception handler, allows throwing of strings
 * 
 * By Danny Reilman <reilman@umich.edu>
 */

class StringException : public std::exception
{
public: 
    StringException(const std::string& func_in, const std::string& why_in) :func(func_in), why(why_in) {}
    StringException(const std::string& func_in) :func(func_in), why() {}

    ~StringException() throw () {}

    const std::string& Function() const throw() { return func; }

    const std::string& Reason() const throw() { return why; }
private:  
    std::string func;
    std::string why;
};

#endif
