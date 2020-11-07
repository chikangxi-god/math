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
	whole_number(const whole_number&);
	whole_number(whole_number&&);

	whole_number& operator=(const whole_number&);
	whole_number& operator=(whole_number&&);

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

};
