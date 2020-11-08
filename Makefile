test_file_path = test/test.cpp
STATICLIB = libnn.a
LIBPATH = /usr/local/lib/
INCLUDEPATH = /usr/local/include/
test/test : native_number_debug.o test/test.cpp whole_number_debug.o rational_number_debug.o
	gcc -std=c++11 -pedantic -O0 -g -o test/test test/test.cpp \
		native_number_debug.o whole_number_debug.o rational_number_debug.o \
	       	-lstdc++
	./test/test

test/test.o : test/test.cpp native_number.hpp
	gcc -std=c++11 -pedantic -O0 -g -o test/test.o test/test.cpp

install : native_number.o whole_number.o
	ar r $(STATICLIB) native_number.o whole_number.o
	cp $(STATICLIB) $(LIBPATH)$(STATICLIB)
	cp native_number.hpp $(INCLUDEPATH)native_number
	cp whole_number.hpp $(INCLUDEPATH)whole_number

native_number_debug.o : native_number.cpp native_number.hpp
	gcc -c -std=c++11 -pedantic -O0 -g -o native_number_debug.o native_number.cpp

native_number.o : native_number.cpp native_number.hpp
	gcc -c -std=c++11 -pedantic -o native_number.o native_number.cpp 

whole_number_debug.o : whole_number.cpp whole_number.hpp
	gcc -c -std=c++11 -pedantic -O0 -g -o whole_number_debug.o whole_number.cpp

whole_number.o : whole_number.cpp whole_number.hpp
	gcc -c -std=c++11 -pedantic -o whole_number.o whole_number.cpp

rational_number_debug.o : rational_number.cpp rational_number.hpp
	gcc -c -std=c++11 -pedantic -O0 -g -o rational_number_debug.o rational_number.cpp 

rational_number.o : rational_number.cpp rational_number.hpp
	gcc -c -std=c++11 -pedantic -o rational_number.o rational_number.cpp
