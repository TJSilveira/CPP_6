#include <iostream>
#include <ostream>
#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
	std::cout << "[ScalarConverter] Default constructor called. " <<
				std::endl;
	return;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	std::cout << "[ScalarConverter] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	std::cout << "[ScalarConverter] Copy assignment operator called. " <<
		std::endl;

	if(this != &other)
		return *this;
	return *this;
}

	// Destructor
ScalarConverter::~ScalarConverter(void)
{
	return;
}

static bool	is_character(char c)
{
	if (c < '0' || c > '9')
		return (true);
	else
		return (false);	
}

static bool	is_int(std::string& input)
{
	int i;
	int sign;

	i = -1;
	sign = 0;
	if (input.length() > 0 && (input[0] == '-' || input[0] == '+'))
	{
		sign = 1;
		i++;
	}
	while (input[++i])
	{
		if (input[i] < '0' || input[i] > '9')
			return(false);
	}
	return (true);
}

static bool	is_float(std::string& input)
{
	// Do another
}

static bool	is_double(std::string& input)
{
	// Do another
}

static void convert(std::string& input)
{
	char	type;
	char	c;
	int		i;
	float	f;
	double	d;

	type = 'n';
	// check for char
	if (input.length() == 1 && is_character(input[0]))
	{
		c = input[0];
		type = 'c';
	}
	// check for int
	else if (input.length() > 0 && is_int(input))
		type = 'i';
	// check for float
	else if (input.length() > 0 && is_float(input))
		type = 'f';
	// check for double
	else if (input.length() > 0 && is_double(input))
		type = 'f';
	
}
