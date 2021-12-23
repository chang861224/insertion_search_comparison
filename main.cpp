#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "methods/Treap.h"
#include "methods/SkipList.h"
#include "methods/SortedArray.h"
#include "methods/Hash.h"
#include "utils.h"
using namespace std;

int main(int argc, char** argv){
    // When no arguments input
    if(argc == 1){
        cout << "----------------------" << endl;
        cout << "Options Description:" << endl;
        cout << "\t-n_index <int>" << endl;
        cout << "\t\tThe index based on 2, which means the length of the number array. Default is 10." << endl;
        cout << "\t-search_scale <int>" << endl;
        cout << "\t\tThe number of times you want to search the element in the array. Default is 100000." << endl;
        cout << "\t-method <string>" << endl;
        cout << "\t\tThe insertion and search method. Default is `SkipList`." << endl;
        cout << "\t\tHere are the method options:" << endl;
        cout << "\t\t1)SkipList 2)Treap 3)LinearSearch 4)BinarySearch" << endl;
        cout << "\t-save <string>" << endl;
        cout << "\t\tThe filename which the result saved. The type of file should be `.csv`." << endl;
        cout << "\t\tIf you do not enter the filename, the result would be print out on the screen." << endl;
        cout << "\t-max_level <int>" << endl;
        cout << "\t\tThe number of level in skip list method." << endl;
        cout << "\t-pos_percent <float>" << endl;
        cout << "\t\tThe positive percentage in skip list method." << endl;
        cout << "\t\tThe value should be between 0 and 1!" << endl;
        cout << endl;
        cout << "NOTICE: If the method is `SkipList`, the default is 3; otherwise, this argument DO NOTHING!" << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout << "./main.exe -n_index 15 -search_scale 100000 -method SkipList -pos_percent 0.5 -save result.csv" << endl;
        cout << "----------------------" << endl;
    }

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
    int level;
    double avg_copy_times;
    int max_level = 3;
    float pos_percent = 0.5;

    // Argument parse
    if((i = ArgPos((char*)"-n_index", argc, argv)) > 0) n_index = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-search_scale", argc, argv)) > 0) search_scale = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-method", argc, argv)) > 0) strcpy(method, argv[i + 1]);
    if((i = ArgPos((char*)"-save", argc, argv)) > 0) strcpy(filename, argv[i + 1]);
    if((i = ArgPos((char*)"-max_level", argc, argv)) > 0) max_level = atoi(argv[i + 1]);
    if((i = ArgPos((char*)"-pos_percent", argc, argv)) > 0) pos_percent = atof(argv[i + 1]);

    // Content of data
    long size = pow(2, n_index);
    int* array = new int[size];
    generateArray(array, size, rand());

    // Search list
    int* search_list = new int[search_scale];
    generateArray(search_list, search_scale, rand());

    if(strcmp(method, "SkipList") == 0){
        SkipList skip_list(max_level, pos_percent);

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
        
        level = skip_list.getLevel();
        avg_copy_times = (double)skip_list.getCopyTimes() / (double)size;
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
            cout << "Max number of lavel: " << max_level << endl;
            cout << "Level: " << level << endl;
            cout << "Average copt times: " << avg_copy_times << endl;
            cout << "Positive percentage: " << pos_percent << endl;
        }

        cout << "Insertion time: " << fixed << insert_duration << setprecision(4) << " sec" << endl;
        cout << "Search time: " << fixed << search_duration << setprecision(4) << " sec" << endl;
    }
    else{
        ofstream file;

        file.open(filename, ios_base::app);

        // Format: Method, Index, Size, Search scale, Level, Average copy times, Positive percentage, Insertion time, Search time
        file << method << ",";
        file << n_index << ",";
        file << size << ",";
        file << search_scale << ",";
        
        // Skip list only
        if(strcmp(method, "SkipList") == 0){
            file << level << ",";
            file << avg_copy_times << ",";
            file << pos_percent << ",";
        }
        else{
            file << ",";
            file << ",";
            file << ",";
        }

        file << insert_duration << ",";
        file << search_duration << endl;

        file.close();
    }

	return 0;
}

