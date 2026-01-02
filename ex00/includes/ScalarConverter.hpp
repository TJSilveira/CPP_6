#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <iostream>

#define INF_D 'q'
#define NEG_INF_D 'w'
#define INF_F 'e'
#define NEG_INF_F 'r'
#define NAN_D 't'
#define NAN_F 'y'

class ScalarConverter
{
private:
	char			_type;
	long double		_value;

	void	convert(std::string& input);
	bool	is_int(std::string& input);
	bool	fits_in_type(void);
	int		asInt(void);
	float	asFloat(void);

public:
	// Constructors
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter(std::string& str);

	// Overloaded Operator
	ScalarConverter&		operator=(const ScalarConverter& other);	

	// Destructor
	~ScalarConverter(void);

	// Setters
	void	setValue(double num);
	void	getValue(std::string& input);

	class Impossible : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class NonDisplayable : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class Overflow : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

// ostream Overload
std::ostream&	operator<<(std::ostream& os, const ScalarConverter* obj);

#endif