test_file_path = test/test.cpp
STATICLIB = libnn.a
LIBPATH = /usr/local/lib/
INCLUDEPATH = /usr/local/include/
test/test : native_number.cpp native_number.hpp test/test.cpp
	gcc -std=c++11 -pedantic -O0 -g -o test/test native_number.cpp $(test_file_path) -lstdc++
	./test/test

install : native_number.o
	ar r $(STATICLIB) native_number.o
	cp $(STATICLIB) $(LIBPATH)$(STATICLIB)
	cp native_number.hpp $(INCLUDEPATH)native_number

native_number.o : native_number.cpp native_number.hpp
	gcc -c -std=c++11 -pedantic -o native_number.o native_number.cpp 
