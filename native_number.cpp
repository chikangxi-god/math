#include "native_number.hpp"
#include <iostream>
#include <iomanip>

#ifndef NDEBUG
#define assert_valid(x) (assert( \
				(x).size>=(x).digits_number && \
				((x).digits_number==0 || (x).digits[(x).digits_number-1]!=0)\
				)\
			)
#else
#define assert_valid(x)
#endif


native_number::native_number()
	:size(0),digits_number(0),digits(nullptr)
{}

native_number::native_number(const uint32_t n)
	:size(1u),digits_number(n!=0),digits(new uint32_t[1])
{
	digits[0] = n;
	assert_valid(*this);
}
native_number::native_number(const native_number& n)
	:size(n.size),digits_number(n.digits_number),digits(new uint32_t[size])
{
	for (uint32_t i = 0; i < digits_number; i++)
	{
		digits[i] = n.digits[i];
	}
	assert_valid(*this);
}
native_number::native_number(native_number&& n)
	:size(n.size),digits_number(n.digits_number),
	digits(std::move(n.digits))
{
	n.digits_number = 0;
	n.size = 0;
	assert_valid(*this);
	assert_valid(n);
}

/*
 * called function:
 * 	bool native_number::operator==(const native_number&)
 */
native_number& native_number::operator=(const native_number& n)
{
	assert_valid(n);
	assert_valid(*this);
	if (size < n.digits_number)
	{
		size = n.digits_number;
		digits = std::unique_ptr<uint32_t[]>(new uint32_t[size]);
	}
	digits_number = n.digits_number;
	for (uint32_t i = 0; i < digits_number; i++)
	{
		digits[i] = n.digits[i];
	}
	assert_valid(*this);
	assert(this->operator==(n));
	return *this;
}

native_number& native_number::operator=(native_number&& n)
{
	digits = std::move(n.digits);
	size = n.size;
	digits_number = n.digits_number;

	n.digits_number = 0;
	n.size = 0;
	assert_valid(*this);
	return *this;
}
native_number::~native_number()
{
	size = 0;
	digits_number = 0;
}

bool native_number::operator==(const native_number& n)const
{
	bool result = true;
	if (digits_number!=n.digits_number)
	{
		result = false;
	}
	else
	{
		for (uint32_t i = 0; i < digits_number; i++)
		{
			if (digits[i]!=n.digits[i])
			{
				result = false;
				break;
			}
			assert(digits[i] == n.digits[i]);
		}
	}
	return result;
}


/*
 * rely on : bool native_number::operator==(const native_number&)const;
 *
 */
bool native_number::operator!=(const native_number& n)const
{
	bool result = false;
	if (digits_number!=n.digits_number)
	{
		result = true;
	}
	else
	{
		for (uint32_t i = 0; i < digits_number; i++)
		{
			if (digits[i]!=n.digits[i])
			{
				result = true;
				break;
			}
		}
	}
	assert(result!=(*this==n));
	return result;
}

native_number native_number::operator+(const native_number& added)const
{
	assert_valid(*this);
	assert_valid(added);
	native_number result;
	if (digits_number > added.digits_number)
	{
		result.digits_number = digits_number;
	}
	else
	{
		result.digits_number = added.digits_number;
	}
	result.size = result.digits_number + 1;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[result.size]);
	uint64_t carry = 0;
	for (uint32_t i = 0; i < result.digits_number; i++)
	{
		const uint64_t a = (i<digits_number?digits[i]:0);
		const uint64_t b = (i<added.digits_number?added.digits[i]:0);
		uint64_t c = a + b + carry;
		result.digits[i] = c;
		carry = c >> 32;

	}
	if (carry)
	{
		result.digits[digits_number] = carry;
		result.digits_number++;
	}
	assert_valid(result);
	return result;
}

/*
 * called function:
 * 	native_number native_number::operator+(const native_number&)
 */
native_number& native_number::operator+=(const native_number& added)
{
	assert_valid(added);
	*this = this->operator+(added);
	assert_valid(*this);
	return *this;
}

/*
 * when debug
 * called function:
 * 	native_number native_number::operator+(const native_number&)const
 * 	bool native_number::operator==(const native_number&)const
 */
native_number native_number::operator-(const native_number& sub) const
{
	assert_valid(*this);
	assert_valid(sub);
	native_number result;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number]);
	result.size = digits_number;
	result.digits_number = 0;
	uint64_t barry = 0;
	for (uint32_t i = 0; i < digits_number; i++)
	{
		const uint64_t a = digits[i];
		const uint64_t b = (i < sub.digits_number?sub.digits[i]:0);
		const uint64_t c = a - b - barry;
		result.digits[i] = c&0xffffffff;
		barry = c>>63;
		if (result.digits[i])result.digits_number = i+1;
	}
	if (barry)
	{
		throw "sub overflow";
	}
	assert_valid(result);
	assert(result + sub == *this);
	return result;
}

/*
 * called function:
 * 	native_number native_number::operator-(const native_number&)
 */
native_number& native_number::operator-=(const native_number& b)
{
	assert_valid(*this);
	assert_valid(b);
	*this = *this - b;
	assert_valid(*this);
	return *this;
}

native_number multiply_version_0(const native_number& a, uint32_t b)
{
	native_number result = 0;
	for (; b > 0; b--)
	{
		result = result + a;
	}
	return result;
}
native_number native_number::operator*(const uint32_t mul)const
{
	assert_valid(*this);
	native_number result;
	if (mul == 0 || *this == 0)
	{
		result = native_number::zero();
	}
	else
	{
		result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number+1]);
		result.size = digits_number+1;
		result.digits_number = digits_number;
		uint64_t carry = 0;
		uint64_t m = mul;
		for (uint32_t i = 0; i < digits_number; i++)
		{
			carry = digits[i] * m + carry;
			result.digits[i] = (uint32_t)(carry&0xffffffff);
			carry >>= 32;
		}
		if (carry)
		{
			result.digits[result.digits_number] = carry;
			result.digits_number++;
		}
	}
	assert_valid(result);
	//assert(result == multiply_version_0(*this,mul));
	return result;
}

/*
 * called function:
 * 	native_number native_number::operator*(const uint32_t)
 */
native_number& native_number::operator*=(const uint32_t b)
{
	*this = this->operator*(b);
	return *this;
}

/*
 * called function:
 * 	native_number::native_number()
 * 	native_number& native_number::operator=(native_number&&)
 * 	native_number native_number::operator*(const uint32_t)
 * 	native_number native_number::operator<<(const uint32_t)
 * 	native_number& native_number::operator+=(const native_number&)
 */
native_number native_number::operator*(const native_number& mul)const
{
	assert_valid(*this);
	assert_valid(mul);
	native_number result;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number + mul.digits_number]);
	result.size = digits_number + mul.digits_number;
	result.digits_number = 0;
	native_number r;
	for (uint32_t i = 0; i < digits_number; i++)
	{
		r = mul * digits[i];
		r = (r << (i*32));
		result += r;
	}
	assert_valid(result);
	return result;
}

/*
 * called function:
 * 	native_number& native_number::operator=(native_number&&)
 * 	native_number native_number::operator*(const native_number&)
 */
native_number& native_number::operator*=(const native_number& b)
{
	*this = *this * b;
	return *this;
}
native_number native_number::operator/(const uint32_t div)const
{
	native_number result;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number]);
	result.size = digits_number;
	uint64_t r = 0;
	for (uint32_t i = digits_number-1; i != UINT32_MAX; i--)
	{
		r = (r<<32) | digits[i];
		result.digits[i] = r / div;
		r = r % div;
	}
	result.digits_number = 0;
	for (uint32_t i = digits_number-1; i!= UINT32_MAX; i--)
	{
		if (result.digits[i])
		{
			result.digits_number = i+1;
			break;
		}
	}
	assert_valid(result);
	assert_valid(*this);
	return result;
}

/*
 * called function:
 * 	native_number::native_number();
 * 	native_number::native_number(native_number&&)
 * 	native_number native_number::div(const native_number&,native_number&)
 */
native_number native_number::operator/(const native_number& b) const
{
	assert_valid(*this);
	assert_valid(b);
	native_number m;
	native_number result = this->div(b,m);
	assert_valid(m);
	assert_valid(result);
	return result;
}
uint32_t native_number::operator%(const uint32_t mod)const
{
	uint64_t r = 0;
	for (uint32_t i = digits_number-1; i != UINT32_MAX; i--)
	{
		r = (r<<32) | digits[i];
		r = r % mod;
	}
	assert_valid(*this);
	return r;
}
native_number native_number::operator%(const native_number& b) const
{
	assert_valid(*this);
	assert_valid(b);
	native_number result;
	this->div(b,result);
	assert_valid(result);
	return result;
}
native_number native_number::div(const uint32_t div, uint32_t* m) const
{
	native_number result;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number]);
	result.size = digits_number;
	uint64_t r = 0;
	for (uint32_t i = digits_number-1; i != UINT32_MAX; i--)
	{
		r = (r<<32) | digits[i];
		result.digits[i] = r / div;
		r = r % div;
	}
	*m = r;
	result.digits_number = 0;
	for (uint32_t i = digits_number-1; i != UINT32_MAX; i--)
	{
		if (result.digits[i])
		{
			result.digits_number = i+1;
			break;
		}
	}
	assert_valid(result);
	assert_valid(*this);
	return result;
}
native_number native_number::div(const native_number& n, native_number& m)const
{
	assert_valid(n);
	assert(n!=0);
	native_number result;
	result.digits_number = 0;
	result.size = digits_number-n.digits_number+1;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[result.size]);
	m = *this;
	for (uint32_t i = result.size-1; i != UINT32_MAX; i--)
	{
		native_number pre_this = m >> (i*32);
		uint32_t digit = 0;
		if (pre_this.digits_number > n.digits_number || pre_this.digits_number==n.digits_number)
		{
			uint64_t a =0;
		       	if (pre_this.digits_number == n.digits_number + 1)
			{
				a = (((uint64_t)pre_this.digits[n.digits_number])<<32)
					|(pre_this.digits[n.digits_number-1]);
			}
			else if (pre_this.digits_number == n.digits_number)
			{
				a = pre_this.digits[n.digits_number-1];
			}
			else
			{
				throw;
			}
			uint32_t b = n.digits[n.digits_number-1];
			digit = a/b;
			while (pre_this < digit*n)digit--;	
			assert(digit*n < pre_this || digit*n == pre_this);
			assert((digit+1)*n > pre_this);
		}
		result.digits[i] = digit;
		if (result.digits_number==0&&digit!=0)result.digits_number = i+1;
		m -= (digit*n)<<i*32;
	}
	assert(result*n + m == *this);
	assert_valid(result);
	return result;
}

		
native_number native_number::operator<<(const uint32_t shift) const
{
	native_number result;
	if (digits_number==0)return native_number::zero();
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number+(shift+31)/32]);
	result.size = digits_number + (shift+31)/32;
	result.digits_number = result.size;
	if (shift%32==0)
	{
		uint32_t d = shift/32;
		for (uint32_t i = digits_number - 1; i < UINT32_MAX; i-- )
		{
			result.digits[i+d] = digits[i];
			assert_valid(result);
		}
		for (uint32_t i = 0; i < d; i++)
		{
			result.digits[i] = 0;
			assert_valid(result);
		}
	}
	else{throw;}
	assert_valid(result);
	assert_valid(*this);
	return result;
}
native_number native_number::operator>>(const uint32_t shift)const
{
	native_number result;
	if (digits_number <= shift/32)return native_number::zero();
	uint32_t size = digits_number-shift/32;
	result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[size]);
	result.size = size;
	for (uint32_t i = 0; i < size; i++)
	{
		result.digits[i] = digits[i+shift/32];
	}
	result.digits_number = size;
	assert_valid(result);
	return result;
}


void native_number::append(uint32_t most)
{
	if (digits_number == size)
	{
		uint32_t size_added = 1;
		uint32_t* d = new uint32_t[size+size_added];
		for (uint32_t i = 0; i < size; i++)
		{
			d[i] = digits[i];
		}
		digits = std::unique_ptr<uint32_t[]>(d);
		size += size_added;
	}
	digits[digits_number] = most;
	digits_number++;
	assert_valid(*this);
}

std::ostream& operator<<(std::ostream& out, const native_number& n)
{
	const uint32_t str_size = n.digits_number * 11;
	char *str = new char[str_size];
	uint32_t dot = str_size-1;
	native_number num = n;
	while (!num.is_zero())
	{
		uint32_t d = 0;
		num = num.div(10,&d);
		str[dot] = d + '0';
		dot--;
	}
	dot++;
	if (dot == str_size){std::cout << '0';}
	while (dot < str_size)
	{
		std::cout << str[dot];
		dot++;
	}
	delete[] str;
	return out;
}
std::istream& operator>>(std::istream& in, native_number& n)
{
	char d = 0;
	n = native_number::zero();
	assert_valid(n);
	assert(n.is_zero());
	while (isspace(in.peek()))in.get();
	while (isdigit(d=in.peek()))
	{
		n = n * 10 + in.get() - '0';
	}
	assert_valid(n);
	return in;
}
native_number operator*(const uint32_t a,const native_number& b)
{
	return b*a;
}
native_number operator/(const uint32_t a,const native_number& b)
{
	return native_number(a)/b;
}
bool operator<(const native_number& n, const native_number& m)
{
	if (n.digits_number > m.digits_number)return false;
	else if (n.digits_number < m.digits_number)return true;
	else
	{
		for (uint32_t i = n.digits_number-1; i != UINT32_MAX; i--)
		{
			if (n.digits[i] > m.digits[i])return false;
			else if (n.digits[i] < m.digits[i]) return true;
		}
	}
	return false;
}
bool operator<=(const native_number& a, const native_number& b)
{
	return !(a>b);
}
bool operator>(const native_number& n, const native_number& m)
{
	if (n.digits_number > m.digits_number)return true;
	else if (n.digits_number < m.digits_number)return false;
	else
	{
		for (uint32_t i = n.digits_number-1; i!= UINT32_MAX; i--)
		{
			if (n.digits[i] > m.digits[i])return true;
			else if (n.digits[i] < m.digits[i])return false;
		}
	}
	return false;
}
bool operator>=(const native_number& a, const native_number& b)
{
	return !(a<b);
}

#undef assert_valid
