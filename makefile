# https://gist.github.com/mihaitodor/bfb8e7ad908489fdf3ceb496573f306a
# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.
#
# SYNOPSIS:
#   make [all]       - builds everything (the test runner)
#   make test_bsearch - builds just the test runner
#   make clean       - removes all generated files

# Points to the root of Google Test, relative to this file.
GTEST_DIR    := third_party/googletest/googletest

# Where to find user code and headers
USER_DIR     := .
INCDIR       := include

# Flags passed to both C and C++ compilers.
CPPFLAGS    += -I$(INCDIR) \
               -isystem $(GTEST_DIR)/include

# Flags passed to the C compiler.
CC           := gcc
CFLAGS      += -Wall -Wextra -std=c99

# Flags passed to the C++ compiler
CXX          := g++
CXXFLAGS    += -Wall -Wextra -std=c++17 -pthread

# All tests produced by this Makefile
TESTS        := test_bsearch

# Google Test headers (for dependency tracking)
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h \
                 $(GTEST_DIR)/include/gtest/internal/*.h

# Google Test source files (amalgamation)
GTEST_SRCS   := $(GTEST_DIR)/src/gtest-all.cc \
                $(GTEST_DIR)/src/gtest_main.cc

.PHONY: all clean

all: $(TESTS)

clean:
	rm -f $(TESTS) *.o gtest.a gtest_main.a

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $< -o $@

gtest_main.o: $(GTEST_DIR)/src/gtest_main.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $< -o $@

# Archive gtest.a
gtest.a: gtest-all.o
	ar rcs $@ $<

# Archive gtest_main.a
gtest_main.a: gtest-all.o gtest_main.o
	ar rcs $@ $^

bsearch.o: src/bsearch.c $(INCDIR)/search.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

test_bsearch.o: tests/test_bsearch.cpp $(INCDIR)/search.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Link the test runner
test_bsearch: bsearch.o test_bsearch.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@


