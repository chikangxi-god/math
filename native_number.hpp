#ifndef NATIVE_NUMBER_HPP
#define NATIVE_NUMBER_HPP

#include<cstdint>
#include<cassert>
#include<iostream>
#include<memory>

#ifndef NDEBUG
#define assert_valid(x) (assert( \
				(x).size>=(x).digits_number && \
				((x).digits_number==0 || (x).digits[(x).digits_number-1]!=0)\
				)\
			)
#else
#define assert_valid(x)
#endif

class native_number
{
	friend std::ostream& operator<<(std::ostream& out,const native_number& n);
public:
	native_number()
	:size(0),digits_number(0),digits(nullptr)
	{
		//std::cout << "native_number's default constructor is been called." << std::endl;
		assert_valid(*this);
	}
	native_number(uint32_t n)
	:size(1u),digits_number(n!=0),digits(new uint32_t[1])
	{
		digits[0] = n;
		assert_valid(*this);
		//std::cout << "native_number(uint32_t) is been called. digits[0] = "
		//	<< digits[0] << std::endl;
	}
	native_number(const native_number& n)
	:size(n.size),digits_number(n.digits_number),digits(new uint32_t[size])
	{
		//std::cout << "native_number(const native_number&) is being called." << std::endl;
		for (uint32_t i = 0; i < digits_number; i++)
		{
			digits[i] = n.digits[i];
		}
		if (digits_number!=0&&digits[digits_number-1]==0)
			std::cout << "digits_number = " <<digits_number <<std::endl;
		assert_valid(*this);
	}
	native_number(native_number&& n)
	:size(n.size),digits_number(n.digits_number),
	digits(std::move(n.digits))
	{
		//std::cout << "native_number(native_number&&) is being called." << std::endl;
		n.digits_number = 0;
		n.size = 0;
		n.digits = nullptr;
		assert_valid(*this);
		assert_valid(n);
	}

	native_number& operator=(const native_number& n)
	{
		//std::cout << "native_number::operator=(const native_number&) is being called." << std::endl;
		if (size < n.digits_number)
		{
			//if (digits)delete[] digits;
			//digits = nullptr;
			
			size = n.digits_number;
			digits_number = n.digits_number;
			digits = std::unique_ptr<uint32_t[]>(new uint32_t[size]);
		}
		for (uint32_t i = 0; i < digits_number; i++)
		{
			digits[i] = n.digits[i];
		}
		//std::cout << "native_number::operator= will complete." << std::endl;
		assert_valid(*this);
		return *this;
	}
	native_number& operator=(native_number&& n)
	{
		//std::cout << "native_number::operator=(native_number&&) is being called." << std::endl;
		//if (digits)
		//{
			//std::cout << "digits in " << digits << " will delete." << std::endl;
		//	delete[] digits;
		//	digits = nullptr;
		//}
		//std::cout << "digits will be in " << n.digits << std::endl;
		size = n.size;
		digits_number = n.digits_number;
		digits = std::move(n.digits);

		n.digits_number = 0;
		n.size = 0;
		n.digits = nullptr;
		//std::cout << "native_number::operator=(const native_number&&) will complete." << std::endl;
		assert_valid(*this);
		assert_valid(n);
		return *this;
	}

	native_number operator+(const native_number& added)const
	{
		//std::cout << "native_number::operator+(const native_number& added) is being called." << std::endl;
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
		uint32_t carry = 0;
		for (uint32_t i = 0; i < result.digits_number; i++)
		{
			const uint32_t &a = (i<digits_number?digits[i]:0);
			const uint32_t &b = (i<added.digits_number?added.digits[i]:0);
			uint32_t &c = result.digits[i];
			c = a + b + carry;
			//std::cout << " a = " << a << ", b = " << b << ", carry = " << carry << std::endl;
			carry = (UINT32_MAX - a) < b + carry || b==UINT32_MAX&&carry>0;
			//std::cout << " c = " << c << std::endl;
		}
		if (carry)
		{
			result.digits[digits_number] = carry;
			result.digits_number++;
		}
		assert_valid(result);
		assert_valid(*this);
		assert_valid(added);
		return result;
	}
	native_number& operator+=(const native_number& added)
	{
		//std::cout << "native_number& native_number::opertator+=(const native_number& added) is being called."
		//	<< std::endl;
		*this = *this + added;
		assert_valid(*this);
		assert_valid(added);
		return *this;
	}

	native_number operator-(const native_number& sub) const
	{
		//std::cout << "native_number native_number::operator-(const native_number&) is being called."
		//	<< std::endl;
		native_number result;
		result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number]);
		result.size = digits_number;
		result.digits_number = digits_number;
		uint32_t barry = 0;
		for (uint32_t i = 0; i < digits_number; i++)
		{
			const uint32_t &a = digits[i];
			const uint32_t &b = (i < sub.digits_number?sub.digits[i]:0);
			result.digits[i] = a - b - barry;
			//std::cout << "a = " << a << ", b = " << b << std::endl;
			if (result.digits[i])result.digits_number = i+1;
			barry = (a<b+barry || b==UINT32_MAX&&barry>0);
		}
		if (barry)
		{
			std::cerr << " subtract overflow." << std::endl;
			throw;
		}
		//std::cout << "operator- will complete." << std::endl;
		assert_valid(result);
		assert_valid(*this);
		assert_valid(sub);
		return result;
	}

	native_number operator*(const uint32_t mul)const
	{
		native_number result;
		result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number+1]);
		result.size = digits_number+1;
		result.digits_number = mul!=0?digits_number:0;
		uint64_t r = 0;
		uint64_t m = mul;
		for (uint32_t i = 0; i < digits_number; i++)
		{
			r = digits[i] * m + (r>>32);
			//std::cout <<"d = " << digits[i] << ", m = " << m << ",r = " << r << std::endl;
			result.digits[i] = (uint32_t)(r&0xffffffff);
		}
		if (r>>32)
		{
			result.digits[result.digits_number] = (r>>32);
			result.digits_number++;
		}
		assert_valid(result);
		assert_valid(*this);
		return result;
	}
	native_number operator*(const native_number& mul)const
	{
		//std::cout << " *(native_number) is being called." << std::endl;
		native_number result;
		result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number + mul.digits_number]);
		result.size = digits_number + mul.digits_number;
		result.digits_number = 0;
		for (uint32_t i = 0; i < digits_number; i++)
		{
			//std::cout << "digits[i] = " << digits[i];
			native_number r = mul * digits[i];
			//std::cout << "r = " << r << ", i = " << i << std::endl;
			//std::cout << "r.digits_number = " << r.digits_number << std::endl;
			r = (r << (i*32));
			//std::cout << "r.digits_number = " << r.digits_number << std::endl;
			//std::cout << "r << (i*32) = " << r << std::endl;
			//std::cout << "result = " << result << std::endl;
			result += r;
			//std::cout << "result += r,then result = " << result << std::endl;
		}
		//std::cout << "*() complete." << std::endl;
		assert_valid(result);
		assert_valid(*this);
		assert_valid(mul);
		return result;
	}

	native_number operator/(const uint32_t div)const
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
	uint32_t operator%(const uint32_t mod)const
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
	native_number div(const uint32_t div, uint32_t* m) const
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
	native_number operator<<(uint32_t shift) const
	{
		//std::cout << "native_number::operator<<(uint32_t) will be called." << std::endl;
		//std::cout << "this->digits_number = " << digits_number << std::endl;
		//std::cout << "this->size = " << size << std::endl;
		//std::cout << "this = " << this << std::endl;
		//std::cout << "*this = " << *this << std::endl;
		//std::cout << "\n\n\n\n\n";
		native_number result;
		if (digits_number==0)return native_number::zero();
		result.digits = std::unique_ptr<uint32_t[]>(new uint32_t[digits_number+(shift+31)/32]);
		result.size = digits_number + (shift+31)/32;
		result.digits_number = result.size;
		//std::cout << "shift = " << shift << std::endl;
		//std::cout << "result.digits_number = " << result.digits_number << std::endl;
		if (shift%32==0)
		{
			uint32_t d = shift/32;
			//std::cout << "digits_number = " << digits_number << std::endl;
			for (uint32_t i = digits_number - 1; i < UINT32_MAX; i-- )
			{
				//std::cout << "r[i+d] = " << digits[i] << std::endl;
				result.digits[i+d] = digits[i];
				assert_valid(result);
			}
			//std::cout << "leave" << std::endl;
			for (uint32_t i = 0; i < d; i++)
			{
				//std::cout << "r[" << i << "] = 0." << std::endl;
				result.digits[i] = 0;
				assert_valid(result);
			}
		}
		else{throw;}
		//std::cout << "result.digits_number = " << result.digits_number << std::endl;
		//std::cout << "<<() complete." << std::endl;
		assert_valid(result);
		assert_valid(*this);
		return result;
	}

	~native_number()
	{
		//std::cout << "~native_number is being called." << std::endl;
		//std::cout << "this native_number is in " << this << std::endl;
		size = 0;
		digits_number = 0;
		//if (digits)
		//{
			//std::cout << "digits in " << digits << " will delete" << std::endl;
		//	delete[] digits;
		//	digits = nullptr;
		//}
		//std::cout << "~native_number will complete." << std::endl;
		assert_valid(*this);
	}
	uint32_t most_significant_digit() const {return digits_number>0?digits[digits_number-1]:0;}
	bool is_zero()const { return digits_number==0;}
	static native_number zero(){ return native_number();}
private:
	void append(uint32_t most)
	{
		if (digits_number == size)
		{
			uint32_t size_added = 1;
			uint32_t* d = new uint32_t[size+size_added];
			for (uint32_t i = 0; i < size; i++)
			{
				d[i] = digits[i];
			}
			//delete[] digits;
			digits = std::unique_ptr<uint32_t[]>(d);
			size += size_added;
		}
		digits[digits_number] = most;
		digits_number++;
		assert_valid(*this);
	}
	uint32_t size;
	uint32_t digits_number;
	std::unique_ptr<uint32_t[]> digits;
};

#endif