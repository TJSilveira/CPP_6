
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

	// is_type functions

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

static bool	is_int(std::string& input)
{
	int i;

	i = -1;
	if (input.length() > 0 && (input[0] == '-' || input[0] == '+'))
		i++;
	while (input[++i])
	{
		if (input[i] < '0' || input[i] > '9')
			return(false);
	}
	return (true);
}

	// helper functions for convert 
static bool	fits_in_type(long double num, t_convert *con_struct)
{
	if (con_struct->type == 'i')
	{
		if (num > static_cast<long double>(std::numeric_limits<int>::max()) ||
		num < static_cast<long double>(std::numeric_limits<int>::min()))
			return (false);
		return (true);
	}
	if (con_struct->type == 'f')
	{
		if (num > std::numeric_limits<float>::max() ||
		num < -std::numeric_limits<float>::max())
			return (false);
		return (true);
	}
	else
	{
		if (num > std::numeric_limits<double>::max() ||
		num < -std::numeric_limits<double>::max())
			return (false);
		return (true);
	}
}

static long double	getValue(std::string& input)
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
		precision < -std::numeric_limits<double>::max())
			throw ScalarConverter::Impossible();
		precision /= 10;
	}
	num += precision;
	num *= sign;
	std::cout << "This si the final number tthat we are converting:"<< std::setprecision(12) << num << ";\n";
	if (num > std::numeric_limits<long double>::max() ||
		num < -std::numeric_limits<long double>::max())
			throw ScalarConverter::Impossible();
	return (num);
}

static void	setValue(long double num, t_convert *con_struct)
{
	if (!(con_struct->type == 'i' || con_struct->type == 'f' || con_struct->type == 'd'))
		return;
	if (!fits_in_type(num, con_struct))
		throw ScalarConverter::Impossible();
	if (con_struct->type == 'i')
		con_struct->i = static_cast<int>(num);
	else if (con_struct->type == 'f')
		con_struct->f = static_cast<float>(num);
	else if (con_struct->type == 'd')
		con_struct->d = static_cast<double>(num);
}

void	init_t_convert(t_convert *con_struct)
{
	con_struct->type = 'n';
	con_struct->c = 0;
	con_struct->i = 0;
	con_struct->f = 0.f;
	con_struct->d = 0.;
}

void	convert_get_type(std::string& input, t_convert *con_struct)
{
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
	{
		con_struct->type = 'c';
		con_struct->c = static_cast<char>(input[1]);
	}
	else if (input.length() > 0 && is_int(input))
		con_struct->type = 'i';
	else if (input.length() > 0 && is_double(input))
		con_struct->type = 'd';
	else if (input.length() > 0 && is_float(input))
		con_struct->type = 'f';
	else if (input.length() == 4 && input.compare("+inf") == 0)
	{
		con_struct->type = INF_D;
		con_struct->d = std::numeric_limits<double>::infinity();
	}
	else if (input.length() == 4 && input.compare("-inf") == 0)
	{
		con_struct->type = NEG_INF_D;
		con_struct->d = -std::numeric_limits<double>::infinity();
	}
	else if (input.length() == 5 && input.compare("+inff") == 0)
	{
		con_struct->type = INF_F;
		con_struct->f = std::numeric_limits<float>::infinity();
	}
	else if (input.length() == 5 && input.compare("-inff") == 0)
	{
		con_struct->type = NEG_INF_F;
		con_struct->f = -std::numeric_limits<float>::infinity();
	}
	else if (input.length() == 3 && input.compare("nan") == 0)
	{
		con_struct->type = NAN_D;
		con_struct->d = static_cast<double>(NAN);
	}
	else if (input.length() == 4 && input.compare("nanf") == 0)
	{
		con_struct->type = NAN_F;
		con_struct->f = static_cast<float>(NAN);
	}
}

static int	safe_double_to_int(double d)
{
	if (d < static_cast<double>(std::numeric_limits<int>::min()) || 
		d > static_cast<double>(std::numeric_limits<int>::max()))
	{
		throw ScalarConverter::Overflow();
	}
	return (static_cast<int>(d));
}

static char	safe_double_to_char(double d)
{
	if (d < static_cast<double>(std::numeric_limits<char>::min()) || 
		d > static_cast<double>(std::numeric_limits<char>::max()))
	{
		throw ScalarConverter::Overflow();
	}
	return (static_cast<char>(d));
}

static float	safe_double_to_float(double d)
{
	if (d < static_cast<double>(-std::numeric_limits<float>::max()) || 
		d > static_cast<double>(std::numeric_limits<float>::max()))
	{
		throw ScalarConverter::Overflow();
	}
	return (static_cast<float>(d));
}

	// helper functions for print 
void	print_char(t_convert *con_struct)
{
	char to_print;

	if (con_struct->type == INF_D ||
		con_struct->type == NEG_INF_D ||
		con_struct->type == INF_F ||
		con_struct->type == NEG_INF_F ||
		con_struct->type == NAN_D ||
		con_struct->type == NAN_F)
	{
		std::cout << "impossible";
		return;
	}
	else if (con_struct->type == 'c')
		to_print = con_struct->c;
	else if (con_struct->type == 'i')
	{
		try
		{
			to_print = safe_double_to_char(static_cast<double>(con_struct->i));
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	else if (con_struct->type == 'f')
	{
		try
		{
			to_print = safe_double_to_char(static_cast<double>(con_struct->f));
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	else
	{
		try
		{
			to_print = safe_double_to_char(con_struct->d);
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	if (std::isprint(to_print))
		std::cout << "\'" << to_print << "\'";
	else
		std::cout << "Non displayable";	
}

void	print_int(t_convert *con_struct)
{
	int to_print;

	if (con_struct->type == INF_D ||
		con_struct->type == NEG_INF_D ||
		con_struct->type == INF_F ||
		con_struct->type == NEG_INF_F ||
		con_struct->type == NAN_D ||
		con_struct->type == NAN_F)
	{
		std::cout << "impossible";
		return;
	}

	if (con_struct->type == 'i')
		to_print = con_struct->i;
	else if (con_struct->type == 'c')
		to_print = static_cast<int>(con_struct->c);
	else if (con_struct->type == 'f')
	{
		try
		{
			to_print = safe_double_to_int(static_cast<double>(con_struct->f));
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	else
	{
		try
		{
			to_print = safe_double_to_int(con_struct->d);
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	std::cout << to_print;
}

void	print_float(t_convert *con_struct)
{
	float	to_print;

	if (con_struct->type == INF_F ||
		con_struct->type == NEG_INF_F ||
		con_struct->type == NAN_F)
	{
		to_print = con_struct->f;
	}
	else if (con_struct->type == INF_D ||
		con_struct->type == NEG_INF_D ||
		con_struct->type == NAN_D)
	{
		to_print = static_cast<float>(con_struct->d);
	}
	else if (con_struct->type == 'i')
		to_print = static_cast<float>(con_struct->i);
	else if (con_struct->type == 'c')
		to_print = static_cast<float>(con_struct->c);
	else if (con_struct->type == 'f')
		to_print = con_struct->f;
	else
	{
		try
		{
			to_print = safe_double_to_float(con_struct->d);
		}
		catch(const ScalarConverter::Overflow& e)
		{
			std::cout << "overflow";
			return;
		}
	}
	std::cout << std::fixed << std::setprecision(1)<< to_print << 'f';
}

void	print_double(t_convert *con_struct)
{
	double	to_print;

	if (con_struct->type == INF_F ||
		con_struct->type == NEG_INF_F ||
		con_struct->type == NAN_F)
	{
		to_print = static_cast<double>(con_struct->f);
	}
	else if (con_struct->type == INF_D ||
		con_struct->type == NEG_INF_D ||
		con_struct->type == NAN_D)
	{
		to_print = con_struct->d;
	}
	else if (con_struct->type == 'i')
		to_print = static_cast<double>(con_struct->i);
	else if (con_struct->type == 'c')
		to_print = static_cast<double>(con_struct->c);
	else if (con_struct->type == 'f')
		to_print = static_cast<double>(con_struct->f);
	else
		to_print = con_struct->d;
	std::cout << to_print;
}

void	print_conversion_summary(t_convert *con_struct)
{
	std::cout << "char: ";
	print_char(con_struct); 
	std::cout << "\nint: ";
	print_int(con_struct);
	std::cout << "\nfloat: ";
	print_float(con_struct);
	std::cout << "\ndouble: ";
	print_double(con_struct);
	std::cout << "\n";
}

void	print_conversion_summary_impossible()
{
	std::cout << "char: impossible\n" <<
		"int: impossible\n" <<
		"float: impossible\n" << 
		"double: impossible\n";	
}

void ScalarConverter::convert(std::string& input)
{
	t_convert con_struct;

	init_t_convert(&con_struct);
	convert_get_type(input, &con_struct);
	std::cout << "[" << input << "]This is the con_struct.type: " << con_struct.type << ";\n\n";

	if (con_struct.type == 'n')
	{
		print_conversion_summary_impossible();
		return;
	}

	try
	{
		if (con_struct.type == 'i' || con_struct.type == 'f' || con_struct.type == 'd')
		{
			setValue(getValue(input), &con_struct);
		}		
	}
	catch(const ScalarConverter::Impossible& e)
	{
		std::cout << "char: impossible\n" <<
			"int: impossible\n" <<
			"float: impossible\n" << 
			"double: impossible\n";
		return;
	}
	print_conversion_summary(&con_struct);
}

const char *ScalarConverter::Impossible::what(void) const throw()
{
	return ("impossible");
}

const char *ScalarConverter::Overflow::what(void) const throw()
{
	return ("Overflow");
}
