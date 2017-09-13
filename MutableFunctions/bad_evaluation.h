#ifndef BAD_EVALUATION_H
#define BAD_EVALUATION_H

#include <exception>
#include <string>

/**
 * An exception for handling problems while evaluating, for instance divide by zero or missing variables
 * By Danny Reilman<reilman@umich.edu>
 */

class bad_evaluation : std::exception
{
public:
	explicit bad_evaluation(const std::string& message_in) : message(message_in) {};

	virtual const char* what() const noexcept
	{
		return message.c_str();
	}
private:
	std::string message;
};

#endif
