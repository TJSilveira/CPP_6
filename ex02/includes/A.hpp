#ifndef A_HPP
#define A_HPP
#include <iostream>
#include <ostream>
#include <stdint.h>
#include "Base.hpp"

class A: public Base
{
private:
public:
	// Constructors
	A(void);
	A(const A& other);

	// Overloaded Operator
	A&		operator=(const A& other);	

	// Destructor
	~A(void);
};

#endif