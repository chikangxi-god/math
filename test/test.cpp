#include "../native_number.hpp"
#include "../whole_number.hpp"
#include "../rational_number.hpp"
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>
int main()
{
	std::cout << "native_number(1) << 22 = " << (native_number(1) << 22) << std::endl;
	std::cout << (native_number(1) << 23) << std::endl;
	srand(time(NULL));
	rational_number x = 0.5f;
	std::cout << "0.5f = " << x << std::endl;
	x = 1.5f;
	std::cout << "1.5f = " << x << std::endl;
	native_number n,m;
	std::cout << " 2 % 2 = " << native_number(2) % native_number(2) << std::endl;
	for (uint32_t i = 0; i < 10; i++)
	{
		uint32_t x = rand();
		uint32_t y = rand();
		n = x;
		m = y;
		assert(n + m == x + y);
		assert(m==0 || n != x + y);
		assert(n > m || m - n == y - x);
		assert(n * m > UINT32_MAX || n * m == x * y);
		assert(y==0 ||n / m == x / y);
		assert(y == 0 || n / y == x / y);
	}
	whole_number a,b;
	for (uint32_t i = 0; i < 10; i++)
	{
		int32_t x = rand() - INT32_MAX/2;
		int32_t y = rand() - INT32_MAX/2;
		a = x;
		b = y;
		assert(a + b > INT32_MAX || a + b < INT32_MIN || a + b == x + y);
		assert(a - b > INT32_MAX || a - b < INT32_MIN || a - b == x - y);
		assert(a * b > INT32_MAX || a * b < INT32_MIN || a * b == x * y);
		assert(y == 0 || a / b > INT32_MAX || a / b < INT32_MIN || a / b == x / y);
	}
	{
		rational_number a,b;
		for (uint32_t i = 0; i < 10; i++)
		{
			float x = (float)rand()/ rand();
			float y = (float)rand()/ rand();
			a = x;
			b = y;
			std::cout << a << " + " << b << " = " << a + b << std::endl;
			std::cout << a << " - " << b << " = " << a - b << std::endl;
			std::cout << a << " * " << b << " = " << a * b << std::endl;
			std::cout << a << " / " << b << " = " << a / b << std::endl;
		}
	}
	return 0;
}	
