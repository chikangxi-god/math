#include "../native_number.hpp"
#include "../whole_number.hpp"
#include "../rational_number.hpp"
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
int main()
{
	native_number n,m;
	n = 10;
	m = 100;
	std::cout << n + m << std::endl;
	assert(n + m == 110);
	assert(m - n == 90);
	n = 5;
	m = 6;
	assert(n*m == 30);
	n = 31;
	m = 7;
	assert(n/m == 4);
	srand(time(NULL));
	for (uint32_t i = 0; i < 100; i++)
	{
		uint32_t x = rand() % 1000;
		uint32_t y = rand() % 1000;
		n = x;
		m = y;
		assert(n + m == x + y);
		assert(m==0 || n != x + y);
		assert(n > m || m - n == y - x);
		assert(n * m == x * y);
		assert(n / m == x / y);
		assert(n / y == x / y);
	}
	return 0;
}	
