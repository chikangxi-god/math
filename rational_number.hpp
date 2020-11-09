#include "native_number.hpp"
#include "whole_number.hpp"


#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP
class rational_number
{
private:
	bool is_negative;
	native_number numerator;
	native_number denominator;

public:
	rational_number():is_negative(0),numerator(0u),denominator(1u){}
	rational_number(float x);
	rational_number(const rational_number& b)
		:is_negative(b.is_negative),numerator(b.numerator),denominator(b.denominator){}
	rational_number(rational_number&& b)
		:
		is_negative(b.is_negative),
		numerator(std::move(b.numerator)),
		denominator(std::move(b.denominator)){}
	
	rational_number& operator=(const rational_number&b);
	rational_number& operator=(rational_number&&);
	rational_number& operator+=(const rational_number&);
	rational_number& operator-=(const rational_number&);
	rational_number& operator*=(const rational_number&);
	rational_number& operator/=(const rational_number&);

	void simplify();
	whole_number get_signed_numerator()const {return whole_number(is_negative,numerator);}

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
	friend std::istream& operator>>(std::istream& out, rational_number&);
};

#endif
