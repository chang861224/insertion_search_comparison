#ifndef _SORTED_ARRAY_H_
#define _SORTED_ARRAY_H_

class SortedArray{
    public:
        SortedArray(int size);
        void Insert(int key);
        int linearSearch(int key);
        int binarySearch(int key, int low, int high);
        int getSize();

    private:
        int n;
        int length;
        int* array;

        int insertKey(int key);
};

# endif
