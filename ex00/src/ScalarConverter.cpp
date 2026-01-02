#include <iostream>
#include <ostream>
#include <limits>
#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void): _type('n'), _value(0)
{
	std::cout << "[ScalarConverter] Default constructor called. " <<
				std::endl;
	return;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other): _type(other._type), _value(other._value)
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

ScalarConverter::ScalarConverter(std::string& str): _type('n'), _value(0)
{
	this->convert(str);
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


static bool	is_float(std::string& input)
{
	int		i;
	bool	dot;
	bool	has_f;

	i = -1;
	dot = false;
	if (input.length() > 0 && (input[0] == '-' || input[0] == '+'))
		i++;
	if (input[i] >= '0' && input[i] <= '9')
		i++;
	while (input[++i])
	{
		if (dot == true && input[i] == '.')
			return(false);
		else if (input[i] == '.')
			dot = true;
		else if (input[i] == 'f')
		{
			i++;
			has_f = true;
			break;
		}
		else if (input[i] < '0' || input[i] > '9')
			return(false);
	}
	if (input[i] != 0)
		return(false);
	if (dot == true && has_f == true)
		return (true);
	else
		return (false);
}

static bool	is_double(std::string& input)
{
	int		i;
	bool	dot;

	i = -1;
	dot = false;
	if (input.length() > 0 && (input[0] == '-' || input[0] == '+'))
		i++;
	if (input[i] >= '0' && input[i] <= '9')
		i++;
	while (input[++i])
	{
		if (dot == true && input[i] == '.')
			return(false);
		else if (input[i] == '.')
			dot = true;
		else if (input[i] < '0' || input[i] > '9')
			return(false);
	}
	return (true);
}

bool	ScalarConverter::is_int(std::string& input)
{
	int i;

	i = -1;
	if (input.length() > 0 && (input[0] == '-' || input[0] == '+'))
		i++;
	while (input[++i])
	{
		std::cout << "["<<i<<"] Index: " << input[i]<< "\n";
		if (input[i] < '0' || input[i] > '9')
			return(false);
	}
	return (true);
}

bool	ScalarConverter::fits_in_type(void)
{
	if (this->_type == 'i')
	{
		if (this->_value > std::numeric_limits<int>::max() ||
		this->_value < std::numeric_limits<int>::min())
			return (false);
		return (true);
	}
	if (this->_type == 'f')
	{
		if (this->_value > std::numeric_limits<float>::max() ||
		this->_value < std::numeric_limits<float>::min())
			return (false);
		return (true);
	}
	else
	{
		if (this->_value > std::numeric_limits<double>::max() ||
		this->_value < std::numeric_limits<double>::min())
			return (false);
		return (true);
	}
}

void ScalarConverter::convert(std::string& input)
{
	// char	c;
	// int		i;
	// float	f;
	// double	d;

	// check for char
	if (input.length() == 1 && is_character(input[0]))
	{
		// c = input[0];
		this->_type = 'c';
	}
	// check for int
	else if (input.length() > 0 && is_int(input))
		this->_type = 'i';
	// check for double
	else if (input.length() > 0 && is_double(input))
		this->_type = 'd';
	// check for float
	else if (input.length() > 0 && is_float(input))
		this->_type = 'f';
	else if (input.length() == 4 && input.compare("+inf"))
	{
		this->_type = INF_D;
		this->_value = std::numeric_limits<double>::infinity();
	}
	else if (input.length() == 4 && input.compare("-inf"))
	{
		this->_type = NEG_INF_D;
		this->_value = -std::numeric_limits<double>::infinity();
	}
	else if (input.length() == 5 && input.compare("+inff"))
	{
		this->_type = INF_F;
		this->_value = std::numeric_limits<float>::infinity();
	}
	else if (input.length() == 5 && input.compare("-inff"))
	{
		this->_type = NEG_INF_F;
		this->_value = -std::numeric_limits<float>::infinity();
	}
	else if (input.length() == 3 && input.compare("nan"))
		this->_type = NAN_D;
	else if (input.length() == 4 && input.compare("nanf"))
		this->_type = NAN_F;

	std::cout << "[" << input << "]This is the type: " << this->_type << ";\n";

	if (this->_type == 'i' || this->_type == 'f' || this->_type == 'd')
	{
		this->getValue(input);
		std::cout << "[This is the value]: " << this->_value << "\n";
		if (!this->fits_in_type())
			throw ScalarConverter::Impossible();
	}
}

void	ScalarConverter::getValue(std::string& input)
{
	long double	num;
	long double	precision;
	long double	decimal_places;
	long double	sign;
	int 		i;

	num = 0;
	precision = 0;
	decimal_places = 0;
	sign = 1;
	i = -1;

	if (input[0] == '+')
		i++;	
	if (input[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (input[++i])
	{
		if (input[i] == '.')
		{
			i++;
			break;
		}
		num *= 10;
		num += input[i] - '0';
		
	}
	while (input[i])
	{
		if (input[i] == 'f')
			break;		
		precision *= 10;
		precision += input[i] - '0';
		decimal_places++;
		i++;
	}
	while (decimal_places--)
	{
		if (precision > std::numeric_limits<double>::max() ||
		precision < std::numeric_limits<double>::min())
			throw ScalarConverter::Impossible();
		precision /= 10;
	}
	num += precision;
	num *= sign;
	if (this->_value > std::numeric_limits<double>::max() ||
		this->_value < std::numeric_limits<double>::min())
			throw ScalarConverter::Impossible();

	this->setValue(num);
}

void	ScalarConverter::setValue(double num)
{
	this->_value = num;
}

int	ScalarConverter::asInt(void)
{
	if (this->_value > std::numeric_limits<int>::max() ||
		this->_value < std::numeric_limits<int>::min())
	{
		throw ScalarConverter::Overflow();
	}
	return (static_cast<int>(this->_value));
}

float	ScalarConverter::asFloat(void)
{
	if (this->_value > std::numeric_limits<float>::max() ||
		this->_value < std::numeric_limits<float>::min())
	{
		throw ScalarConverter::Overflow();
	}
	return (static_cast<float>(this->_value));
}

const char *ScalarConverter::Impossible::what(void) const throw()
{
	return ("impossible");
}

const char *ScalarConverter::NonDisplayable::what(void) const throw()
{
	return ("Non displayable");
}

const char *ScalarConverter::Overflow::what(void) const throw()
{
	return ("Impossible");
}

// std::ostream&	operator<<(std::ostream& os, const ScalarConverter* obj)
// {
// 		// os <<	"Name: " << obj->getName() << "; " <<
// 		// 		"Signed: " << obj->getSigned() << "; " <<
// 		// 		"SigningGrade: " << obj->getSigningGrade() << "; " <<
// 		// 		"ExecutionGrade: " << obj->getExecutionGrade() << ";";
// 		// return(os);
// }


