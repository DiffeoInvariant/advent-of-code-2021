

CXX = clang++
CXXFLAGS = -std=c++17 -O3 -g


%: %.cc
	$(LINK.cc) $^ -o $@
