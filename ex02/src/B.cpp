
#include "../includes/B.hpp"

B::B(void)
{
	std::cout << "[B] Default constructor called. " <<
				std::endl;
	return;
}

B::B(const B& other)
{
	std::cout << "[B] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

B& B::operator=(const B& other)
{
	std::cout << "[B] Copy assignment operator called. " <<
		std::endl;

	if(this != &other)
		return *this;
	return *this;
}

	// Destructor
B::~B(void)
{
	return;
}
