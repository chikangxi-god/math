#include "whole_number.hpp"
#include "native_number.hpp"
whole_number::whole_number(const whole_number& b)
	:is_negative(b.is_negative),n(b.n)
{
}

whole_number::whole_number(whole_number&& b)
	:is_negative(b.is_negative),n(std::move(b.n))
{
}
whole_number::whole_number(const native_number& n)
	:is_negative(0),n(n)
{}
whole_number::whole_number(native_number&& n)
	:is_negative(0),n(std::move(n))
{}
whole_number::whole_number(bool is_negative, const native_number& n)
	:is_negative(is_negative),n(n)
{}
whole_number::whole_number(bool is_negative, native_number&& n)
	:is_negative(is_negative),n(std::move(n))
{}

whole_number& whole_number::operator=(const whole_number& b)
{
	is_negative = b.is_negative;
	n = b.n;
	return *this;
}

whole_number& whole_number::operator=(whole_number&& b)
{
	is_negative = b.is_negative;
	n = std::move(b.n);
	return *this;
}
whole_number& whole_number::operator+=(const whole_number& b)
{
	*this = *this + b;
	return *this;
}
whole_number& whole_number::operator-=(const whole_number& b)
{
	*this = *this - b;
	return *this;
}
whole_number& whole_number::operator*=(const whole_number& b)
{
	*this = *this * b;
	return *this;
}
whole_number& whole_number::operator/=(const whole_number& b)
{
	*this = *this / b;
	return *this;
}
whole_number whole_number::operator-()
{
	whole_number result;
	result.n = n;
	result.is_negative = !is_negative;
	return result;
}

whole_number operator+(const whole_number& a, const whole_number& b)
{
	whole_number result;
	if (a.is_negative==b.is_negative)
	{
		result.is_negative = a.is_negative;
		result.n = a.n + b.n;
	}
	else
	{
		if (a.n > b.n)
		{
			result.is_negative = a.is_negative;
			result.n = a.n - b.n;
		}
		else
		{
			result.is_negative = !a.is_negative;
			result.n = b.n - a.n;
		}
	}
	if (result.n==0)result.is_negative=false;
	return result;
}

whole_number operator-(const whole_number& a, const whole_number& b)
{
	whole_number result;
	if (a.is_negative!=b.is_negative)
	{
		result.is_negative = a.is_negative;
		result.n = a.n + b.n;
	}
	else
	{
		if (a.n > b.n)
		{
			result.is_negative = a.is_negative;
			result.n = a.n - b.n;
		}
		else
		{
			result.is_negative = !a.is_negative;
			result.n = b.n - a.n;
		}
	}
	if (result.n==0)result.is_negative=false;
	return result;
}

whole_number operator*(const whole_number& a, const whole_number& b)
{
	whole_number result;
	result.is_negative = a.is_negative^b.is_negative;
	result.n = a.n * b.n;
	if (result.n==0)result.is_negative=false;
	return result;
}

whole_number operator/(const whole_number& a, const whole_number& b)
{
	whole_number result;
	result.is_negative = a.is_negative^b.is_negative;
	result.n = a.n / b.n;
	if (result.n==0)result.is_negative=false;
	return result;
}

whole_number operator%(const whole_number& a, const whole_number& b)
{
	whole_number result;
	result.is_negative = a.is_negative;
	result.n = a.n % b.n;
	if (result.n==0)result.is_negative=false;
	return result;
}

bool operator==(const whole_number& a, const whole_number& b)
{
	bool result;
	result = (a.n==b.n)&&(a.is_negative==b.is_negative);
	return result;
}
bool operator!=(const whole_number& a, const whole_number& b)
{
	bool result;
	result = (a.n!=b.n)||(a.is_negative!=b.is_negative);
	return result;
}

bool operator>(const whole_number& a, const whole_number& b)
{
	bool result;
	result = a.is_negative==0&&b.is_negative==1
		|| a.is_negative==0&&a.n>b.n
		|| a.is_negative==1&&b.is_negative==1&&a.n<b.n;
	return result;
}

bool operator>=(const whole_number& a, const whole_number& b)
{
	bool result;
	result = a.is_negative==0&&b.is_negative==1
		|| a.is_negative==0&&a.n>=b.n
		|| a.is_negative==1&&b.is_negative==1&&a.n<=b.n;
	return result;
}

bool operator<(const whole_number& a, const whole_number& b)
{
	bool result;
	result = a.is_negative==1&&b.is_negative==0
		|| b.is_negative==0&&a.n<b.n
		|| b.is_negative==1&&a.is_negative==1&&a.n>b.n;
	return result;
}

bool operator<=(const whole_number& a, const whole_number& b)
{
	bool result;
	result = a.is_negative==1&&b.is_negative==0
		|| b.is_negative==0&&a.n<=b.n
		||b.is_negative==1&&a.is_negative==1&&a.n>=b.n;
	return result;
}

native_number abs(const whole_number& a)
{
	return a.n;
}


std::ostream& operator<<(std::ostream& out, const whole_number& a)
{
	if (a.is_negative)
	{
		out << '-';
	}
	out << a.n;
	return out;
}

std::istream& operator>>(std::istream& in, whole_number& b)
{
	while (isspace(in.peek())){in.get();}
	if (in.peek()=='-')
	{
		b.is_negative = 1;
		in.get();
	}
	while (isdigit(in.peek()))
	{
		uint32_t decimal_digit = in.get() - '0';
		assert(decimal_digit >=0 && decimal_digit <= 9);
		b.n = b.n * 10 + decimal_digit;
	}
	return in;
}
