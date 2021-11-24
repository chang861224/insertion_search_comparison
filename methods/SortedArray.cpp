#include "SortedArray.h"

SortedArray::SortedArray(int size){
    n = 0;
    length = size;
    array = new int[length];
}

void SortedArray::Insert(int key){
    n = insertKey(key);
}

int SortedArray::insertKey(int key){
    if (n >= length)
        return n;
 
    int i;

    for (i = n - 1 ; (i >= 0 && array[i] > key) ; i--)
        array[i + 1] = array[i];
 
    array[i + 1] = key;
 
    return (n + 1);
}

int SortedArray::linearSearch(int key){
    for (int i = 0 ; i < n ; i++)
        if (array[i] == key)
            return i;

    return -1;
}

int SortedArray::binarySearch(int key, int low, int high){
    if (high < low)
        return -1;

    int mid = (low + high) / 2;
    
    if (key == array[mid])
        return mid;
    
    if (key > array[mid])
        return binarySearch(key, mid + 1, high);
    
    return binarySearch(key, low, mid - 1);
}

int SortedArray::getSize(){
    return length;
}

