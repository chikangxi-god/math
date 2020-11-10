test_file_path = test/test.cpp
STATICLIB = libm.a
STATICLIB_DEBUG = libm_debug.a
OBJS = native_number.o whole_number.o rational_number.o sqrt_number.o
OBJS_DEBUG = native_number_debug.o whole_number_debug.o rational_number_debug.o sqrt_number_debug.o
HEADER = native_number.hpp whole_number.hpp rational_number.hpp sqrt_number.hpp number
LIBPATH = /usr/local/lib/
INCLUDEPATH = /usr/local/include/
CC_DEBUG = gcc -c -std=c++11 -pedantic -O0 -g
LINK_DEBUG = gcc -std=c++11 -pedantic -O0 -g
CC = gcc -c -std=c++11 -pedantic -O3
LINK = gcc -std=c++11 -pedantic -O3
test/test : test/test.o $(STATICLIB_DEBUG)
	$(LINK_DEBUG) -o test/test test/test.cpp \
		$(STATICLIB_DEBUG) -lstdc++
	valgrind test/test

test/test_native_number : native_number_debug.o test/test_native_number.o
	$(LINK_DEBUG) -o test/test_native_number \
		test/test_native_number.o native_number_debug.o -lstdc++

test/test.o : test/test.cpp native_number.hpp
	$(CC_DEBUG) -o test/test.o test/test.cpp

test/test_native_number.o : test/test_native_number.cpp native_number.hpp
	$(CC_DEBUG) -o test/test_native_number.o \
		test/test_native_number.cpp
$(STATICLIB_DEBUG) : native_number_debug.o whole_number_debug.o rational_number_debug.o \
	sqrt_number_debug.o
	ar r $(STATICLIB_DEBUG) $(OBJS_DEBUG)

$(STATICLIB) : $(OBJS)
	ar r $(STATICLIB) $(OBJS)


install : $(STATICLIB) $(HEADER)
	cp $(STATICLIB) $(LIBPATH)$(STATICLIB)
	cp native_number.hpp $(INCLUDEPATH)native_number.hpp
	cp whole_number.hpp $(INCLUDEPATH)whole_number.hpp
	cp rational_number.hpp $(INCLUDEPATH)rational_number.hpp
	cp sqrt_number.hpp $(INCLUDEPATH)sqrt_number.hpp
	cp number $(INCLUDEPATH)number

clean : 
	rm -f $(OBJS) $(OBJS_DEBUG) $(STATICLIB) $(STATICLIB_DEBUG) 
	rm -f test/test
	rm -f test/test.o

uninstall :
	rm $(LIBPATH)$(STATICLIB)
	rm $(INCLUDEPATH)native_number.hpp
	rm $(INCLUDEPATH)whole_number.hpp
	rm $(INCLUDEPATH)rational_number.hpp
	rm $(INCLUDEPATH)sqrt_number.hpp
	rm $(INCLUDEPATH)number

native_number_debug.o : native_number.cpp
	$(CC_DEBUG) -o native_number_debug.o native_number.cpp

native_number.o : native_number.cpp
	$(CC) -o native_number.o native_number.cpp 

whole_number_debug.o : whole_number.cpp
	$(CC_DEBUG) -o whole_number_debug.o whole_number.cpp

whole_number.o : whole_number.cpp
	$(CC) -o whole_number.o whole_number.cpp

rational_number_debug.o : rational_number.cpp
	$(CC_DEBUG) -o rational_number_debug.o rational_number.cpp

rational_number.o : rational_number.cpp
	$(CC) -o rational_number.o rational_number.cpp

sqrt_number.hpp : rational_number.hpp

sqrt_number_debug.o : sqrt_number.cpp
	$(CC_DEBUG) -o sqrt_number_debug.o sqrt_number.cpp

test/test_sqrt_number.o : test/test_sqrt_number.cpp sqrt_number.hpp
	$(CC_DEBUG) -o test/test_sqrt_number.o test/test_sqrt_number.cpp

test/test_sqrt_number :test/test_sqrt_number.o $(STATICLIB_DEBUG)
	$(LINK_DEBUG) -o test/test_sqrt_number test/test_sqrt_number.o $(STATICLIB_DEBUG) -lstdc++
	valgrind test/test_sqrt_number

test/test_rational_number.o : test/test_rational_number.cpp
	$(CC_DEBUG) -o test/test_rational_number.o test/test_rational_number.cpp

test/test_rational_number : test/test_rational_number.o $(STATICLIB_DEBUG)
	$(LINK_DEBUG) -o test/test_rational_number test/test_rational_number.o $(STATICLIB_DEBUG) -lstdc++
	valgrind test/test_rational_number


