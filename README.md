# Comparison with Insertion and Search Methods
Compare the time-cost of insertion and search methods, include:

1. Skip list
2. Treap
3. Sorted array

In the search section, there are "linear search" and "binary search" in "sorted array" method.


## Usage

### Compilation
Use `make` to complie the program.
```
make
```

### Execution
Use `./main.exe` to run the program. Here are the arguments shown below:
```
Options Description:
	-n_index <int>
		The index based on 2, which means the length of the number array. Default is 10.
	-search_scale <int>
		The number of times you want to search the element in the array. Default is 100000.
	-method <string>
		The insertion and search method. Default is `SkipList`.
		Here are the method options:
		1)SkipList 2)Treap 3)LinearSearch 4)BinarySearch
	-save <string>
		The filename which the result saved. The type of file should be `.csv`.
		If you do not enter the filename, the result would be print out on the screen.
	-max_level <int>
		The number of level in skip list method.
	-pos_percent <float>
		The positive percentage in skip list method.
		The value should be between 0 and 1!

NOTICE: If the method is `SkipList`, the default is 3; otherwise, this argument DO NOTHING!

Usage:
./main.exe -n_index 15 -search_scale 100000 -method SkipList -pos_percent 0.5 -save result.csv
```
