#include<iostream>
#include<ctime>
#include "native_number.hpp"

int main()
{
	clock_t last_clock;
	native_number sum = 1;
	uint32_t d = 1;
	std::cin >> d;
	last_clock = clock();
	for (uint32_t i = 1; i <= d; i++)
	{
		sum = sum * native_number(i);
		std::cout << i << "! has calculated." << std::endl;
	}
	//sum = native_number(2u) * native_number(3u);
	std::cout << sum << std::endl;
	clock_t diff_clock = clock() - last_clock;
	std::cout << "clock = " << diff_clock << std::endl;
	return 0;
}
