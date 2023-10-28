TARGETS := ida-test libpython-test/libpython-test-a.dylib libpython-test/libpython-test-b.dylib libpython-test/libpython-test-stub.dylib

C_CXX_FLAGS := -Wall -Wextra -g -O0
CFLAGS := $(C_CXX_FLAGS) -std=gnu17
CXXFLAGS := $(C_CXX_FLAGS) -std=gnu++20

all: $(TARGETS)

.PHONY: clean all test

test:

clean:
	rm -rf *.dSYM/ libpython-test/*.dSYM
	rm -f $(TARGETS)

libpython-test/libpython-test-a.dylib: libpython-test/libpython-test-a.c
	$(CC) -o $@ $^ $(CFLAGS) -shared -Wl,-install_name,@rpath/libpython-test.dylib


libpython-test/libpython-test-b.dylib: libpython-test/libpython-test-b.c
	$(CC) -o $@ $^ $(CFLAGS) -shared -Wl,-install_name,@rpath/libpython-test.dylib

libpython-test/libpython-test-stub.dylib: libpython-test/libpython-test-stub.cpp libpython-test/libpython-test-a.dylib libpython-test/libpython-test-b.dylib
	$(CXX) -o $@ libpython-test/libpython-test-stub.cpp $(CXXFLAGS) -shared -Wl,-install_name,@rpath/$(shell basename $@) -Wl,-rpath,@loader_path -Wl,-reexport_library,libpython-test/libpython-test.dylib -v -Wl,-v

ida-test: ida-test.c libpython-test/libpython-test-a.dylib libpython-test/libpython-test-b.dylib libpython-test/libpython-test-stub.dylib
	$(CC) -o $@ ida-test.c $(CFLAGS) -I libpython-test/ -L libpython-test -Wl,-rpath,$(shell readlink -f libpython-test/) -lpython-test-stub
