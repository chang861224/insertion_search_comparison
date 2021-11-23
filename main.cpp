#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "methods/Treap.h"
#include "methods/SkipList.h"
#include "methods/SortedArray.h"
#include "utils.h"
using namespace std;

int main(int argc, char** argv){
    srand(time(NULL));

    int i;
    clock_t insert_start, insert_end, search_start, search_end;
    int n_index = 10;
    int search_scale = 100000;
    char* method = new char[20];
    strcpy(method, "SkipList");
    char* filename = new char[20];
    strcpy(filename, "");
    // slip list only
    int level = 3;
    float pos_percent = 0.5;

    // Argument parse
    if((i = ArgPos((char*)"-n_index", argc, argv)) > 0) n_index = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-search_scale", argc, argv)) > 0) search_scale = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-method", argc, argv)) > 0) strcpy(method, argv[i + 1]);
    if((i = ArgPos((char*)"-save", argc, argv)) > 0) strcpy(filename, argv[i + 1]);
    if((i = ArgPos((char*)"-level", argc, argv)) > 0) level = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-pos_percent", argc, argv)) > 0) pos_percent = atof(argv[i + 1]);

    // Content of data
    long size = pow(2, n_index);
    int* array = new int[size];
    generateArray(array, size, rand());

    // Search list
    int* search_list = new int[search_scale];
    generateArray(search_list, search_scale, rand());

    if(strcmp(method, "SkipList") == 0){
        SkipList skip_list(level, pos_percent);

        // Insert
        insert_start = clock();

        for(auto i = 0 ; i < size ; i++){
            skip_list.Insert(array[i]);
        }

        insert_end = clock();

        // Search
        search_start = clock();

        for(auto i = 0 ; i < search_scale ; i++){
            skip_list.Search(search_list[i]);
        }

        search_end = clock();
    }
    else if(strcmp(method, "Treap") == 0){
        Treap treap(NULL);

        // Insert
        insert_start = clock();

        for(auto i = 0 ; i < size ; i++){
            treap.Insert(array[i]);
        }

        insert_end = clock();

        // Search
        search_start = clock();

        for(auto i = 0 ; i < search_scale ; i++){
            treap.Search(search_list[i]);
        }

        search_end = clock();
    }
    else if(strcmp(method, "LinearSearch") == 0){
        SortedArray sorted_array(size);

        // Insert
        insert_start = clock();

        for(int i = 0 ; i < size ; i++){
            sorted_array.Insert(array[i]);
        }

        insert_end = clock();

        // Search
        search_start = clock();

        for(int i = 0 ; i < search_scale ; i++){
            int location = sorted_array.linearSearch(search_list[i]);
        }

        search_end = clock();
    }
    else if(strcmp(method, "BinarySearch") == 0){
        SortedArray sorted_array(size);

        // Insert
        insert_start = clock();

        for(int i = 0 ; i < size ; i++){
            sorted_array.Insert(array[i]);
        }

        insert_end = clock();

        // Search
        search_start = clock();

        for(int i = 0 ; i < search_scale ; i++){
            int location = sorted_array.binarySearch(search_list[i], 0, sorted_array.getSize() - 1);
        }

        search_end = clock();
    }
    else{
        cout << "Method not found!" << endl;
        exit(1);
    }

    // Duration calculation
    double insert_duration = double(insert_end - insert_start) / double(CLOCKS_PER_SEC);
    double search_duration = double(search_end - search_start) / double(CLOCKS_PER_SEC);

    // Results
    if(strcmp(filename, "") == 0){
        cout << "Search method: " << method << endl;
        cout << "Index based on 2: " << n_index << endl;
        cout << "Size of data structure: " << size << endl;
        cout << "Search scale: " << search_scale << endl;

        // Skip list only
        if(strcmp(method, "SkipList") == 0){
            cout << "Number of lavel: " << level << endl;
            cout << "Positive percentage: " << pos_percent << endl;
        }

        cout << "Insertion time: " << fixed << insert_duration << setprecision(4) << " sec" << endl;
        cout << "Search time: " << fixed << search_duration << setprecision(4) << " sec" << endl;
    }
    else{
        ofstream file;

        file.open(filename, ios_base::app);

        // Format: Method, Index, Size, Search scale, Level, Positive percentage, Insertion time, Search time
        file << method << ",";
        file << n_index << ",";
        file << size << ",";
        file << search_scale << ",";
        
        // Skip list only
        if(strcmp(method, "SkipList") == 0){
            file << level << ",";
            file << pos_percent << ",";
        }
        else{
            file << ",";
            file << ",";
        }

        file << insert_duration << ",";
        file << search_duration << endl;

        file.close();
    }

	return 0;
}

