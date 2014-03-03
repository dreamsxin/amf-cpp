CXXFLAGS += -std=c++0x -Wall -Wextra -pedantic
CPPFLAGS += -Isrc

ifneq ($(shell $(CXX) --version | grep clang),)
	ifeq ($(shell uname -s),Darwin)
		CXXFLAGS += -stdlib=libc++
	endif
endif

SRC = src/serializer.cpp src/deserializationcontext.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean debug dist-clean release test
all: release

release: libamf.a
debug: CXXFLAGS += -g
debug: libamf.a
32bit: CXXFLAGS += -m32
32bit: release
libamf.a: libamf.a($(OBJ))

clean:
	rm -f *.a src/*.o .dep

dist-clean: clean
	$(MAKE) -C tests clean

test: $(OBJ)
	$(MAKE) -C tests
	tests/main

.dep:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM $(SRC)src/serializer.cpp | \
		sed '/^[^[:space:]]/s,^,src/,;s,:, $@:,' > $@

ifneq ($(MAKECMDGOALS),clean)
-include .dep
endif
