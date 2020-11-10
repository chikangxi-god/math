#ifndef SQRT_NUMBER_HPP
#define SQRT_NUMBER_HPP

#include "rational_number.hpp"

class sqrt_number
{
private:
	rational_number multiple;
	rational_number root;
	
public:
	sqrt_number():multiple(1),root(1){}
	sqrt_number(const sqrt_number& b):multiple(b.multiple),root(b.root){}
	sqrt_number(sqrt_number&& b):multiple(std::move(b.multiple)),root(std::move(b.root)){}
	sqrt_number(const rational_number& b):multiple(b),root(1){}
	sqrt_number(rational_number&& b):multiple(std::move(b)), root(1){}

	sqrt_number& operator=(const sqrt_number&);
	sqrt_number& operator=(sqrt_number&&);
	sqrt_number& operator=(const rational_number&);
	sqrt_number& operator=(rational_number&&);
	sqrt_number& operator*=(const sqrt_number&);
	sqrt_number& operator/=(const sqrt_number&);

	friend sqrt_number sqrt(const rational_number& b);
	friend sqrt_number sqrt(rational_number&& b);
	
	friend sqrt_number operator*(const sqrt_number&, const sqrt_number&);
	friend sqrt_number operator/(const sqrt_number&, const sqrt_number&);

	friend std::ostream& operator<<(std::ostream& out, const sqrt_number&);

};
sqrt_number sqrt(const rational_number&);
sqrt_number sqrt(rational_number&&);

#endif
