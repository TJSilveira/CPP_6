#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <iostream>
#include <iomanip>
#include <ostream>
#include <limits>
#include <cmath>

#define INF_D 'q'
#define NEG_INF_D 'w'
#define INF_F 'e'
#define NEG_INF_F 'r'
#define NAN_D 't'
#define NAN_F 'y'

typedef struct s_convert
{
	char	type;
	char	c;
	int		i;
	float	f;
	double	d;
}	t_convert;

class ScalarConverter
{
private:
	// Constructors
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter& other);

	// Overloaded Operator
	ScalarConverter&		operator=(const ScalarConverter& other);	

	// Destructor
	~ScalarConverter(void);
public:
	static void	convert(std::string& input);

	class Impossible : public std::exception
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

#endif