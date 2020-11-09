test_file_path = test/test.cpp
STATICLIB = libm.a
LIBPATH = /usr/local/lib/
INCLUDEPATH = /usr/local/include/
CC_DEBUG = gcc -c -std=c++11 -pedantic -O0 -g
LINK_DEBUG = gcc -std=c++11 -pedantic -O0 -g
CC = gcc -c -std=c++11 -pedantic -O3
LINK = gcc -std=c++11 -pedantic -O3
test/test : native_number_debug.o test/test.o whole_number_debug.o rational_number_debug.o
	$(LINK_DEBUG) -o test/test test/test.cpp \
		native_number_debug.o whole_number_debug.o rational_number_debug.o \
	       	-lstdc++
	valgrind test/test

test/test_native_number : native_number_debug.o test/test_native_number.o
	$(LINK_DEBUG) -o test/test_native_number \
		test/test_native_number.o native_number_debug.o -lstdc++

test/test.o : test/test.cpp native_number.hpp
	$(CC_DEBUG) -o test/test.o test/test.cpp

test/test_native_number.o : test/test_native_number.cpp native_number.hpp
	$(CC_DEBUG) -o test/test_native_number.o \
		test/test_native_number.cpp

install : native_number.o whole_number.o rational_number.o
	ar r $(STATICLIB) native_number.o whole_number.o rational_number.o
	cp $(STATICLIB) $(LIBPATH)$(STATICLIB)
	cp native_number.hpp $(INCLUDEPATH)native_number
	cp whole_number.hpp $(INCLUDEPATH)whole_number
	cp rational_number.hpp $(INCLUDEPATH)rational_number

clean : 
	if ls native_number.o; then rm native_number.o;fi
	if ls whole_number.o; then rm whole_number.o;fi
	if ls rational_number.o; then rm rational_number.o;fi
	if ls native_number_debug.o;then rm native_number_debug.o;fi
	if ls whole_number_debug.o;then rm whole_number_debug.o;fi
	if ls rational_number_debug.o;then rm rational_number_debug.o;fi
	if ls test/test;then rm test/test;fi

uninstall :
	rm $(LIBPATH)$(STATICLIB)
	rm $(INCLUDEPATH)native_number
	rm $(INCLUDEPATH)whole_number
	rm $(INCLUDEPATH)rational_number

native_number_debug.o : native_number.cpp native_number.hpp
	$(CC_DEBUG) -o native_number_debug.o native_number.cpp

native_number.o : native_number.cpp native_number.hpp
	$(CC) -o native_number.o native_number.cpp 

whole_number_debug.o : whole_number.cpp whole_number.hpp
	$(CC_DEBUG) -o whole_number_debug.o whole_number.cpp

whole_number.o : whole_number.cpp whole_number.hpp
	$(CC) -o whole_number.o whole_number.cpp

rational_number_debug.o : rational_number.cpp rational_number.hpp
	$(CC_DEBUG) -o rational_number_debug.o rational_number.cpp 

rational_number.o : rational_number.cpp rational_number.hpp
	$(CC) -o rational_number.o rational_number.cpp
