#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <iostream>
#include "ScalarConverter.hpp"

class ScalarConverter
{
private:
	const std::string	_name;
	int					_grade;

	// Constructors
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter& other);

	// Overloaded Operator
	ScalarConverter&		operator=(const ScalarConverter& other);	

public:

	// Destructor
	~ScalarConverter(void);

};

#endif