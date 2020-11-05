#ifndef NATIVE_NUMBER_HPP
#define NATIVE_NUMBER_HPP

#include<cstdint>
#include<cassert>
#include<iostream>
#include<memory>


class native_number
{
public:
	native_number();
	native_number(uint32_t n);
	native_number(const native_number& n);
	native_number(native_number&& n);

	native_number& operator=(const native_number& n);
	native_number& operator=(native_number&& n);
	~native_number();


	native_number operator+(const native_number& added)const;
	native_number& operator+=(const native_number& added);

	native_number operator-(const native_number& sub) const;

	native_number operator*(const uint32_t mul)const;
	native_number operator*(const native_number& mul)const;
	native_number operator/(const uint32_t div)const;
	uint32_t operator%(const uint32_t mod)const;
	native_number div(const uint32_t div, uint32_t* m) const;
	bool operator==(const native_number& n)const;
	bool operator!=(const native_number& n)const;
	native_number operator<<(uint32_t shift) const;

	bool is_zero()const { return digits_number==0;}
	static native_number zero(){ return native_number();}

private:
	uint32_t most_significant_digit() const {return digits_number>0?digits[digits_number-1]:0;}
	void append(uint32_t most);

	uint32_t size;
	uint32_t digits_number;
	std::unique_ptr<uint32_t[]> digits;

	friend std::ostream& operator<<(std::ostream& out,const native_number& n);
	friend std::istream& operator>>(std::istream& in, native_number& n);
};

#endif
