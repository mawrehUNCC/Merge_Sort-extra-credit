Compilation

To compile the program, make sure you have a C++17-compatible compiler.
 You can use the included Makefile:

make

This will compile parallel_merge_sort.cpp and create an executable called
parallel_merge_sort.

Run the program with the desired array size as a command-line argument:
eg:
./parallel_merge_sort <array_size>

> ./parallel_merge_sort 1000000

This will:

Generate a random array of 1,000,000 integers
Sort it using parallel merge sort
Print the time taken to complete the sort
