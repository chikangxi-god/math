#include "rational_number.hpp"

rational_number& rational_number::operator=(const rational_number& b)
{
	numerator = b.numerator;
	denominator = b.denominator;
	return *this;
}
rational_number& rational_number::operator=(rational_number&& b)
{
	numerator = std::move(b.numerator);
	denominator = std::move(b.denominator);
	return *this;
}

rational_number& rational_number::operator+=(const rational_number& b)
{
	*this = *this + b;
	return *this;
}
rational_number& rational_number::operator-=(const rational_number& b)
{
	*this = *this - b;
	return *this;
}
rational_number& rational_number::operator*=(const rational_number& b)
{
	*this = *this * b;
	return *this;
}
rational_number& rational_number::operator/=(const rational_number& b)
{
	*this = *this / b;
	return *this;
}

rational_number operator+(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator*b.denominator + a.denominator * b.numerator;
	return result;
}


rational_number operator-(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator*b.denominator - a.denominator * b.numerator;
	return result;
}

rational_number operator*(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator * b.numerator;
	return result;
}

rational_number operator/(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.denominator = a.denominator * abs(b.numerator);
	result.numerator = a.numerator * b.denominator;
	if (b.numerator.is_neg())
	{
		result.numerator = -result.numerator;
	}
	return result;
}

bool operator==(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator*b.denominator == a.denominator* b.numerator;
	return result;
}
bool operator!=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator*b.denominator != a.denominator* b.numerator;
	return result;
}
bool operator>(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator*b.denominator > a.denominator * b.numerator;
	return result;
}
bool operator>=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator*b.denominator >= a.denominator * b.numerator;
	return result;
}
bool operator<(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator* b.denominator < a.denominator * b.numerator;
	return result;
}
bool operator<=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.numerator * b.denominator <= a.denominator * b.numerator;
	return result;
}
