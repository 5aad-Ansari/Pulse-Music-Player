#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include "Song.h"

class SearchSort {
public:
    Song* songArray;
    int capacity;
    int currentSize;

    SearchSort(int maxCapacity) {
        capacity = maxCapacity;
        currentSize = 0;
        songArray = new Song[capacity];
    }

    ~SearchSort() {
        delete[] songArray;
    }
};

#endif