CXX = g++
CXXFLAGS = -O3 -std=c++17 -pthread

all: parallel_merge_sort

parallel_merge_sort: parallel_merge_sort.cpp
	$(CXX) $(CXXFLAGS) -o parallel_merge_sort parallel_merge_sort.cpp

clean:
	rm -f parallel_merge_sort
