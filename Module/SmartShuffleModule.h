#ifndef SMART_SHUFFLE_MODULE_H
#define SMART_SHUFFLE_MODULE_H

#include <iostream>
#include "../Modal/SmartShuffle.h"
using namespace std;

class SmartShuffleModule {
private:
    SmartShuffle heap;

    void swapNodes(int index1, int index2) {
        HeapNode temp = heap.heapArray[index1];
        heap.heapArray[index1] = heap.heapArray[index2];
        heap.heapArray[index2] = temp;
    }

    void bubbleUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap.heapArray[index].priorityScore < heap.heapArray[parentIndex].priorityScore) {
                swapNodes(index, parentIndex);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void bubbleDown(int index) {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < heap.currentSize && heap.heapArray[leftChild].priorityScore < heap.heapArray[smallest].priorityScore) {
            smallest = leftChild;
        }
        if (rightChild < heap.currentSize && heap.heapArray[rightChild].priorityScore < heap.heapArray[smallest].priorityScore) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swapNodes(index, smallest);
            bubbleDown(smallest);
        }
    }

public:
    SmartShuffleModule(int maxCapacity) : heap(maxCapacity) {}

    void insert(Song s, int score) {
        if (heap.currentSize == heap.capacity) return;
        heap.heapArray[heap.currentSize] = HeapNode(s, score);
        bubbleUp(heap.currentSize);
        heap.currentSize++;
    }

    Song playNextShuffled() {
        if (heap.currentSize == 0) return Song();

        // 1. Get the song with the lowest score (highest priority)
        Song minSong = heap.heapArray[0].song;

        // 2. Increase its score (simulating that you just played it)
        // This pushes it to the bottom of the heap.
        heap.heapArray[0].priorityScore += 10; 

        // 3. Re-heapify (bubble down the new score so the next lowest score comes to the top)
        bubbleDown(0);

        return minSong;
    }

    void displayHeap() {
        cout << "\n--- Smart Shuffle Queue (Min-Heap) ---" << endl;
        for (int i = 0; i < heap.currentSize; i++) {
            cout << "- " << heap.heapArray[i].song.title 
                 << " (Score: " << heap.heapArray[i].priorityScore << ")" << endl;
        }
    }
};

#endif
