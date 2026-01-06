
#include "../includes/Serializer.hpp"

Serializer::Serializer(void)
{
	std::cout << "[Serializer] Default constructor called. " <<
				std::endl;
	return;
}

Serializer::Serializer(const Serializer& other)
{
	std::cout << "[Serializer] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

Serializer& Serializer::operator=(const Serializer& other)
{
	std::cout << "[Serializer] Copy assignment operator called. " <<
		std::endl;

	if(this != &other)
		return *this;
	return *this;
}

	// Destructor
Serializer::~Serializer(void)
{
	return;
}

uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
	return(reinterpret_cast<Data*>(raw));
}