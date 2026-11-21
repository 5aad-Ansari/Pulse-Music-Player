#ifndef SMART_SHUFFLE_H
#define SMART_SHUFFLE_H

#include <string>
#include "Song.h"
using namespace std;

// 1. HEAP NODE
class HeapNode {
public:
    Song song;
    int priorityScore; // keeps score if a song has low score it has higher chance tto play next

    HeapNode() {
        priorityScore = 0;
    }

    HeapNode(Song s, int score) {
        song = s;
        priorityScore = score;
    }
};

// 2. THE SMART SHUFFLE MODEL
class SmartShuffle {
public:
    // We use an array to represent the Binary Heap
    HeapNode* heapArray;
    int capacity;   
    int currentSize; 

    SmartShuffle(int maxCapacity) {
        capacity = maxCapacity;
        currentSize = 0;
        heapArray = new HeapNode[capacity];
    }

    ~SmartShuffle() {
        delete[] heapArray;
    }
};

#endif