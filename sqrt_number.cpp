#include "sqrt_number.hpp"

sqrt_number& sqrt_number::operator=(const sqrt_number& b)
{
	multiple = b.multiple;
	root = b.root;
	return *this;
}

sqrt_number& sqrt_number::operator=(sqrt_number&& b)
{
	multiple = std::move(b.multiple);
	root = std::move(b.root);
	return *this;
}

sqrt_number& sqrt_number::operator=(const rational_number& b)
{
	multiple = b;
	root = 1;
	return *this;
}

sqrt_number& sqrt_number::operator=(rational_number&& b)
{
	multiple = std::move(b);
	root = 1;
	return *this;
}

sqrt_number& sqrt_number::operator*=(const sqrt_number& b)
{
	*this = *this * b;
	return *this;
}

sqrt_number& sqrt_number::operator/=(const sqrt_number& b)
{
	*this = *this / b;
	return *this;
}

sqrt_number sqrt(const rational_number& b)
{
	sqrt_number result;
	result.multiple = 1;
	result.root = b;
	return result;
}

sqrt_number sqrt(rational_number&& b)
{
	sqrt_number result;
	result.multiple = 1;
	result.root = std::move(b);
	return result;
}

sqrt_number operator*( const sqrt_number& a, const sqrt_number& b)
{
	sqrt_number result;
	result.multiple = a.multiple * b.multiple;
	if (a.root == b.root)
	{
		result.multiple *= a.root;
		result.root = 1;
	}
	else
	{
		result.root = a.root * b.root;
	}
	return result;
}

sqrt_number operator/(const sqrt_number& a, const sqrt_number& b)
{
	sqrt_number result;
	result.multiple = a.multiple / b.multiple;
	result.root = a.root / b.root;
	return result;
}

std::ostream& operator<<(std::ostream& out, const sqrt_number& b)
{
	if (b.multiple != 1)
		out << b.multiple;
	if (b.root !=1)
		out << "sqrt(" << b.root << ")";
	if (b.multiple == 1 && b.root == 1)
		out << "1";
	return out;
}
