debug : native_number.cpp native_number.hpp test_native_number.cpp
	gcc -std=c++11 -pedantic -O0 -g native_number.cpp test_native_number.cpp -lstdc++

release : native_number.cpp native_number.hpp test_native_number.cpp
	gcc -std=c++11 -pedantic -DNDEBUG -O3  native_number.cpp test_native_number.cpp -lstdc++
