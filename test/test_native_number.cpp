#include "../native_number.hpp"

int main()
{
	native_number n;
	assert(n==0);
	native_number m(1);
	assert(m==1);
	assert(n + m == 1);
	assert(n * m == 0);
	native_number mul = 1;
	for (uint32_t i = 0; i < 100; i++)
	{
		native_number x = rand();
		mul *= x;
		assert(mul * n == 0);
		assert(n * mul == 0);
		assert(mul * m == mul);
		assert(m * mul == mul);
	}

	return 0;
}

