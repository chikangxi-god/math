#include "native_number.hpp"
#include "whole_number.hpp"


#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP
class rational_number
{
private:
	whole_number numerator;
	native_number denominator;

public:
	rational_number():numerator(0u),denominator(1u){}
	rational_number(float x);
	rational_number(const rational_number& b)
		:numerator(b.numerator),denominator(b.denominator){}
	rational_number(rational_number&& b)
		:
		numerator(std::move(b.numerator)),
		denominator(std::move(b.denominator)){}
	
	rational_number& operator=(const rational_number&b);
	rational_number& operator=(rational_number&&);
	rational_number& operator+=(const rational_number&);
	rational_number& operator-=(const rational_number&);
	rational_number& operator*=(const rational_number&);
	rational_number& operator/=(const rational_number&);

	void simplify();

	friend rational_number operator+(const rational_number&, const rational_number&);
	friend rational_number operator-(const rational_number&, const rational_number&);
	friend rational_number operator*(const rational_number&, const rational_number&);
	friend rational_number operator/(const rational_number&, const rational_number&);
	
	friend bool operator==(const rational_number&, const rational_number&);
	friend bool operator!=(const rational_number&, const rational_number&);
	friend bool operator>(const rational_number&, const rational_number&);
	friend bool operator>=(const rational_number&, const rational_number&);
	friend bool operator<(const rational_number&, const rational_number&);
	friend bool operator<=(const rational_number&, const rational_number&);

	friend std::ostream& operator<<(std::ostream& out, const rational_number&);
};

#endif
