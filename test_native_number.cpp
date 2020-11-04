#include<iostream>

#include "native_number.hpp"

int main()
{
	native_number sum = 1;
	uint32_t d = 1;
	std::cin >> d;
	for (uint32_t i = 1; i <= d; i++)
	{
		sum = sum * native_number(i);
		//std::cout << i << "! = " << sum << std::endl;
	}
	std::cout << sum << std::endl;
	return 0;
}
