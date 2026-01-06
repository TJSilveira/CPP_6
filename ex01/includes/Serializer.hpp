#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include <iostream>
#include <ostream>
#include <stdint.h>

typedef struct Data
{
	int			important_number;
	std::string	import_str;
} Data;

class Serializer
{
private:
	// Constructors
	Serializer(void);
	Serializer(const Serializer& other);

	// Overloaded Operator
	Serializer&		operator=(const Serializer& other);	

	// Destructor
	~Serializer(void);
public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

#endif