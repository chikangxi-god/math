#include "native_number.hpp"
#include <iostream>
#include <iomanip>
std::ostream& operator<<(std::ostream& out, const native_number& n)
{
	//std::cout << "std::ostream& operator<<(std::ostream&,const native_number&) is being called."
	//	<< std::endl;
	const uint32_t str_size = n.digits_number * 11;
	char *str = new char[str_size];
	uint32_t dot = str_size-1;
	native_number num = n;
	while (!num.is_zero())
	{
		uint32_t d = 0;
		num = num.div(10,&d);
		//std::cout << "digits_number = " << num.digits_number << " ... " << d << std::endl;
		str[dot] = d + '0';
		dot--;
		//if (dot == UINT32_MAX)std::cout << "error!" << std::endl;
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
