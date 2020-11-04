a.out : native_number.cpp native_number.hpp test_native_number.cpp
	gcc -std=c++11 native_number.cpp test_native_number.cpp -lstdc++
