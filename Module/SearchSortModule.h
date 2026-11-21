#ifndef SEARCH_SORT_MODULE_H
#define SEARCH_SORT_MODULE_H

#include <iostream>
#include "../Modal/SearchSort.h"
using namespace std;

class SearchSortModule {
private:
    SearchSort data;

    int partition(Song arr[], int low, int high) {
        string pivot = arr[high].title;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j].title < pivot) {
                i++;
                Song temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Song temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return (i + 1);
    }

    void quickSort(Song arr[], int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

public:
    SearchSortModule(int maxCapacity) : data(maxCapacity) {}

    void addSongForSorting(Song s) {
        if (data.currentSize < data.capacity) {
            data.songArray[data.currentSize] = s;
            data.currentSize++;
        }
    }

    void sortByTitle() {
        if (data.currentSize == 0) {
            cout << "No songs to sort." << endl;
            return;
        }
        quickSort(data.songArray, 0, data.currentSize - 1);
        cout << "Songs sorted alphabetically by title." << endl;
    }

    void displaySongs() {
        cout << "\n--- Sorted Song List ---" << endl;
        if (data.currentSize == 0) {
            cout << "List is empty." << endl;
            return;
        }
        for (int i = 0; i < data.currentSize; i++) {
            cout << "- " << data.songArray[i].title 
                 << " by " << data.songArray[i].artist << endl;
        }
    }

    int binarySearchByTitle(string target) {
        int left = 0;
        int right = data.currentSize - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (data.songArray[mid].title == target) {
                return mid;
            }
            else if (data.songArray[mid].title < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }

    void searchForSong(string title) {
        // Automatically sort before searching to guarantee Binary Search works
        if (data.currentSize > 0) {
            quickSort(data.songArray, 0, data.currentSize - 1);
        }
        
        int result = binarySearchByTitle(title);
        if (result != -1) {
            cout << "\nFound at index " << result << ": " << data.songArray[result].title 
                 << " by " << data.songArray[result].artist << endl;
        } else {
            cout << "\nSong '" << title << "' not found." << endl;
        }
    }
};

#endif
