#ifndef C_HPP
#define C_HPP
#include <iostream>
#include <ostream>
#include <stdint.h>
#include "Base.hpp"

class C: public Base
{
private:
public:
	// Constructors
	C(void);
	C(const C& other);

	// Overloaded Operator
	C&		operator=(const C& other);	

	// Destructor
	~C(void);
};

#endif