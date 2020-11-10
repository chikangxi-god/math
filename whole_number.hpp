#ifndef WHOLE_NUMBER_HPP
#define WHOLE_NUMBER_HPP

#include<iostream>
#include"native_number.hpp"
class whole_number
{
private:
	bool is_negative;
	native_number n;
public:
	whole_number():is_negative(0),n(){}
	whole_number(int32_t a):is_negative(a<0),n((uint32_t)(a>=0?a:-a)){}
	whole_number(int64_t a):is_negative(a<0),n((uint64_t)(a>=0?a:-a)){}
	whole_number(uint32_t b):is_negative(0),n(b){}
	whole_number(const native_number&);
	whole_number(native_number&&);
	whole_number(bool is_negative, const native_number&);
	whole_number(bool is_negative, native_number&&);
	whole_number(const whole_number&);
	whole_number(whole_number&&);

	whole_number& operator=(const whole_number&);
	whole_number& operator=(whole_number&&);
	whole_number& operator+=(const whole_number&);
	whole_number& operator-=(const whole_number&);
	whole_number& operator*=(const whole_number&);
	whole_number& operator/=(const whole_number&);
	whole_number operator-();
	bool is_neg() const{ return is_negative;}


	friend whole_number operator+(const whole_number&,const whole_number&);
	friend whole_number operator-(const whole_number&,const whole_number&);
	friend whole_number operator*(const whole_number&,const whole_number&);
	friend whole_number operator/(const whole_number&,const whole_number&);
	friend whole_number operator%(const whole_number&,const whole_number&);
	
	friend bool operator==(const whole_number&, const whole_number&);
	friend bool operator!=(const whole_number&, const whole_number&);
	friend bool operator>(const whole_number&, const whole_number&);
	friend bool operator>=(const whole_number&, const whole_number&);
	friend bool operator<(const whole_number&, const whole_number&);
	friend bool operator<=(const whole_number&, const whole_number&);
	friend native_number abs(const whole_number&);
	

	friend std::ostream& operator<<(std::ostream&, const whole_number&);
	friend std::istream& operator>>(std::istream&, whole_number&);
};

#endif
