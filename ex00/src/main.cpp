#include "../includes/ScalarConverter.hpp"

int main()
{
	std::string array[] = {
		"this",
		"3",
		"3f", 
		"3.",
		"3.f",
		"3.9.",
		"-2147483648",
		"-2147483649",
		"-2147483649.0",
		"-2147483647",
		"-2147483646",
		"-2147483645",
		"-21"
	};

	for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		ScalarConverter::convert(array[i]);
	}

	std::string testCases[] = {
		// Basic Scalar Literals
		"'a'", "'z'", "'0'", "' '", "'*'", "'#'", "0", "42", "-42", "0.0f", 
		"4.2f", "-4.2f", "0.0", "4.2", "-4.2", 

		// Limits and Overflows
		"2147483647", "-2147483648", "2147483648", "-2147483649", 
		"3.40282e+38f", "-3.40282e+38f", "1.79769e+308", "-1.79769e+308",
		"127", "128", "255", "256", "-1", "32", "31",

		// Pseudo-literals
		"nan", "nanf", "inf", "+inf", "-inf", "inff", "+inff", "-inff",

		// Complex and Edge Formatting
		"00042", "42.0000f", ".0f", "0.f", "42.", ".42", "+42", "+4.2f",

		// Invalid Inputs (Should be handled as impossible)
		"", "   ", "42.42.42", "42ff", "f", "42f.0", "++42", "42a"
	};

	for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
		std::cout << "--- Test Case " << i + 1 << ": [" << testCases[i] << "] ---" << std::endl;
		ScalarConverter::convert(testCases[i]);
		std::cout << std::endl;
	}
}