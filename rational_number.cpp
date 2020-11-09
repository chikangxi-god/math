#include "rational_number.hpp"

rational_number::rational_number(float x)
{
	uint32_t a = *(uint32_t*)&x;
	uint32_t s = a>>31;	
	uint32_t e = (a>>23) &0xff;
	int32_t E = (int32_t)e - 127;
	uint32_t f = (a & 0x7fffff);
	is_negative = s;
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
			numerator = f;
		}
	}
	else if (E>=23)
	{
		denominator = 1;
		numerator = native_number(f|0x800000)<<(E-23);
	}
	else
	{
		denominator = (native_number(1)<<(23-E));
		numerator = f|0x800000;
	}
	simplify();
}


rational_number& rational_number::operator=(const rational_number& b)
{
	is_negative = b.is_negative;
	numerator = b.numerator;
	denominator = b.denominator;
	assert(*this == b);
	return *this;
}
rational_number& rational_number::operator=(rational_number&& b)
{
	is_negative = b.is_negative;
	numerator = std::move(b.numerator);
	denominator = std::move(b.denominator);
	assert(denominator!=0);
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

static native_number prime_numbers[] = {2,3,5,7,11,13,17,23,29};
void rational_number::simplify()
{
	if (numerator % denominator == 0)
	{
		numerator /= denominator;
		denominator = 1;
	}
	else if (denominator % (numerator) == 0)
	{
		denominator /= numerator;
		numerator = 1;
	}
	for (uint32_t i = 0; i < sizeof(prime_numbers)/sizeof(prime_numbers[0])
			&& prime_numbers[i] <= numerator
			&& prime_numbers[i] <= denominator;
	    )
	{
		if (numerator % prime_numbers[i] == 0
				&& denominator % prime_numbers[i] == 0)
		{

			numerator /= prime_numbers[i];
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
		if (a.is_negative!=b.is_negative)
		{
			if (a.numerator >= b.numerator)
			{
				result.is_negative = a.is_negative;
				result.numerator = a.numerator - b.numerator;
			}
			else
			{
				result.is_negative = b.is_negative;
				result.numerator = b.numerator - a.numerator;
			}
		}
		else
		{
			result.is_negative = a.is_negative;
			result.numerator = a.numerator + b.numerator;
		}
	}
	else
	{
		result.denominator = a.denominator * b.denominator;
		whole_number signed_numerator = a.get_signed_numerator()*b.denominator
		       	+ a.denominator * b.get_signed_numerator();
		result.is_negative = signed_numerator.is_neg();
		result.numerator = abs(signed_numerator);
	}
	result.simplify();
	return result;
}


rational_number operator-(const rational_number& a, const rational_number& b)
{
	rational_number result;
	whole_number signed_numerator;
	if (a.denominator == b.denominator)
	{
		result.denominator = a.denominator;
		signed_numerator = a.get_signed_numerator() - b.get_signed_numerator();
	}
	else
	{
		result.denominator = a.denominator * b.denominator;
		signed_numerator = a.get_signed_numerator()*b.denominator
			- a.denominator * b.get_signed_numerator();
	}
	result.is_negative = signed_numerator.is_neg();
	result.numerator = abs(signed_numerator);
	result.simplify();
	return result;
}

rational_number operator*(const rational_number& a, const rational_number& b)
{
	rational_number result;
	bool is_negative = a.is_negative^b.is_negative;
	if (a.denominator == b.numerator && a.numerator == b.denominator)
	{
		result.numerator = 1;
		result.denominator = 1;
	}
	else if (a.denominator == b.numerator)
	{
		result.numerator = a.numerator;
		result.denominator = b.denominator;
	}
	else if (a.numerator == b.denominator)
	{
		result.numerator = b.numerator;
		result.denominator = a.denominator;
	}
	else
	{
		result.numerator = a.numerator*b.numerator;
		result.denominator = a.denominator * b.denominator;
	}
	result.simplify();
	return result;
}

rational_number operator/(const rational_number& a, const rational_number& b)
{
	rational_number result;
	result.denominator = a.denominator * b.numerator;
	result.numerator = a.numerator * b.denominator;
	result.is_negative = a.is_negative ^ b.is_negative;
	result.simplify();
	return result;
}

bool operator==(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.is_negative==b.is_negative 
		&& a.numerator*b.denominator == a.denominator* b.numerator;
	return result;
}
bool operator!=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.is_negative!=b.is_negative
		|| a.numerator*b.denominator != a.denominator* b.numerator;
	return result;
}
bool operator>(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.get_signed_numerator()*b.denominator > a.denominator * b.get_signed_numerator();
	return result;
}
bool operator>=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.get_signed_numerator()*b.denominator >= a.denominator * b.get_signed_numerator();
	return result;
}
bool operator<(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.get_signed_numerator()* b.denominator < a.denominator * b.get_signed_numerator();
	return result;
}
bool operator<=(const rational_number& a, const rational_number& b)
{
	bool result;
	result = a.get_signed_numerator() * b.denominator <= a.denominator * b.get_signed_numerator();
	return result;
}

std::ostream& operator<<(std::ostream& out, const rational_number& b)
{
	out << (b.is_negative?"-":"");
	out << b.numerator / b.denominator;
	out << ".";
	native_number f = b.numerator % b.denominator;
	for (uint32_t i = 0; i < 99&&f!=0; i++)
	{
		f *= 10;
		out << f/b.denominator;
		f = f % b.denominator;
	}

	return out;
}
std::istream& operator>>(std::istream& in, rational_number& b)
{
	whole_number signed_numerator;
	in >> signed_numerator;
	b.is_negative = signed_numerator.is_neg();
	b.numerator = abs(signed_numerator);
	if (in.peek()=='.')
	{
		in.get();
		while (isdigit(in.peek()))
		{
			uint32_t decimal_digit = in.get() - '0';
			assert(decimal_digit >=0 && decimal_digit <=9);
			b.numerator = b.numerator*10 + decimal_digit;
			b.denominator *= 10;
		}
	}
	return in;
}
