#include "../includes/ScalarConverter.hpp"

int main()
{
	float a = 3.0f/0.0;
	std::string strb = "this";
	std::string strc = "3";
	std::string strd = "3f";
	std::string stre = "3.";
	std::string strf = "3.f";
	std::string strg = "3.9.";
	std::string stri = "-2147483648";
	std::string strj = "-2147483649";

	std::cout << "This is the " << a << std::endl;
	ScalarConverter b = ScalarConverter(strb);
	ScalarConverter c = ScalarConverter(strc);
	ScalarConverter d = ScalarConverter(strd);
	ScalarConverter e = ScalarConverter(stre);
	ScalarConverter f = ScalarConverter(strf);
	ScalarConverter g = ScalarConverter(strg);
	ScalarConverter i = ScalarConverter(stri);
	ScalarConverter j = ScalarConverter(strj);
}