#include "rational_number.hpp"

rational_number::rational_number(float x)
{
	uint32_t a = *(uint32_t*)&x;
	uint32_t s = a>>31;	
	uint32_t e = (a>>23) &0xff;
	int32_t E = (int32_t)e - 127;
	uint32_t f = (a & 0x7fffff);
	if (e==255)throw;
	else if (e==0)
	{
		if (f==0)
		{
			numerator = 0;
			denominator = 1;
		}
		else
		{
			denominator = native_number(1)<<(126+23);
			numerator.n = f;
			numerator.is_negative = s;
		}
	}
	else if (E>=23)
	{
		denominator = 1;
		numerator.n = native_number(f|0x800000)<<(E-23);
		numerator.is_negative = s;
	}
	else
	{
		denominator = (native_number(1)<<(23-E));
		numerator.n = f|0x800000;
		numerator.is_negative = s;
	}
	simplify();
}


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

static native_number prime_numbers[] = {2,3,5};
void rational_number::simplify()
{
	if (numerator.n % denominator == 0)
	{
		numerator.n /= denominator;
		denominator = 1;
	}
	else if (denominator % numerator.n == 0)
	{
		denominator /= numerator.n;
		numerator.n = 1;
	}
	for (uint32_t i = 0; i < sizeof(prime_numbers)/sizeof(prime_numbers[0])
			&& prime_numbers[i] <= numerator.n
			&& prime_numbers[i] <= denominator;
	    )
	{
		if (numerator.n % prime_numbers[i] == 0
				&& denominator % prime_numbers[i] == 0)
		{

			numerator.n /= prime_numbers[i];
			denominator /= prime_numbers[i];
		}
		else{i++;}
	}
}
rational_number operator+(const rational_number& a, const rational_number& b)
{
	rational_number result;
	if (a.denominator == b.denominator)
	{
		result.denominator = a.denominator;
		result.numerator = a.numerator + b. numerator;
	}
	else
	{
		result.denominator = a.denominator * b.denominator;
		result.numerator = a.numerator*b.denominator + a.denominator * b.numerator;
	}
	result.simplify();
	return result;
}


rational_number operator-(const rational_number& a, const rational_number& b)
{
	rational_number result;
	if (a.denominator == b.denominator)
	{
		result.denominator = a.denominator;
		result.numerator = a.numerator - b.numerator;
	}
	else
	{
		result.denominator = a.denominator * b.denominator;
		result.numerator = a.numerator*b.denominator - a.denominator * b.numerator;
	}
	result.simplify();
	return result;
}

rational_number operator*(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.numerator.is_negative = a.numerator.is_negative^b.numerator.is_negative;
	if (a.denominator == b.numerator.n && a.numerator.n == b.denominator)
	{
		result.numerator.n = 1;
		result.denominator = 1;
	}
	else if (a.denominator == b.numerator.n)
	{
		result.numerator.n = a.numerator.n;
		result.denominator = b.denominator;
	}
	else if (a.numerator == b.denominator)
	{
		result.numerator.n = b.numerator.n;
		result.denominator = a.denominator;
	}
	else
	{
		result.denominator = a.denominator * b.denominator;
		result.numerator.n = a.numerator.n * b.numerator.n;
	}
	result.simplify();
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
	result.simplify();
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

std::ostream& operator<<(std::ostream& out, const rational_number& b)
{
	out << (b.numerator.is_negative?"-":"");
	out << b.numerator.n / b.denominator;
	out << ".";
	native_number f = b.numerator.n % b.denominator;
	for (uint32_t i = 0; i < 9; i++)
	{
		f *= 10;
		out << f/b.denominator;
		f = f % b.denominator;
	}

	return out;
}
