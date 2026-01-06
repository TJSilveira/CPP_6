
#include "../includes/C.hpp"

C::C(void)
{
	std::cout << "[C] Default constructor called. " <<
				std::endl;
	return;
}

C::C(const C& other)
{
	std::cout << "[C] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

C& C::operator=(const C& other)
{
	std::cout << "[C] Copy assignment operator called. " <<
		std::endl;

	if(this != &other)
		return *this;
	return *this;
}

	// Destructor
C::~C(void)
{
	return;
}
