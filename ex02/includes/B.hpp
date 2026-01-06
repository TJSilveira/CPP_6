#ifndef B_HPP
#define B_HPP
#include <iostream>
#include <ostream>
#include <stdint.h>
#include "Base.hpp"

class B: public Base
{
private:
public:
	// Constructors
	B(void);
	B(const B& other);

	// Overloaded Operator
	B&		operator=(const B& other);	

	// Destructor
	~B(void);
};

#endif