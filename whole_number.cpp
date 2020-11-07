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
