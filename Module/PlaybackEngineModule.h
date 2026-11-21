#ifndef PLAYBACK_ENGINE_MODULE_H
#define PLAYBACK_ENGINE_MODULE_H

#include <iostream>
#include "../Modal/Playbackengine.h"
using namespace std;

class PlaybackEngineModule {
private:
    PlaybackEngine player;
    
    // Stack of arrays for multi-level Undo
    Song* backupQueues[10]; 
    int backupCounts[10];   
    int backupTop;          

public:
    PlaybackEngineModule() : player(), backupTop(-1) {}

    ~PlaybackEngineModule() {
        // Clean up any remaining backups in the stack
        while (backupTop >= 0) {
            delete[] backupQueues[backupTop];
            backupTop--;
        }
    }

    void addToQueue(Song s) {
        QueueNode* newNode = new QueueNode(s);
        if (player.queueFront == NULL) {
            player.queueFront = newNode;
            player.queueRear = newNode;
        } else {
            player.queueRear->next = newNode;
            player.queueRear = newNode;
        }
    }

    void addMultipleToQueue(Song* songs, int count) {
        for (int i = 0; i < count; i++) {
            addToQueue(songs[i]);
        }
        cout << count << " songs from the playlist have been added to the Queue!" << endl;
    }

    void clearQueueAndBackup() {
        if (player.queueFront == NULL) return;

        // 1. Count how many songs are currently in the queue
        int count = 0;
        QueueNode* temp = player.queueFront;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        // 2. Push the current queue to the Stack
        if (backupTop < 9) { // Max 10 backups
            backupTop++;
            backupCounts[backupTop] = count;
            backupQueues[backupTop] = new Song[count];
            
            temp = player.queueFront;
            for (int i = 0; i < count; i++) {
                backupQueues[backupTop][i] = temp->song;
                temp = temp->next;
            }
        } else {
            cout << "Backup history is full!" << endl;
        }

        // 3. Clear the actual Queue
        while (player.queueFront != NULL) {
            QueueNode* tempNode = player.queueFront;
            player.queueFront = player.queueFront->next;
            delete tempNode;
        }
        player.queueRear = NULL;
    }

    void restorePreviousQueue() {
        if (backupTop == -1) {
            cout << "No previous queue to restore!" << endl;
            return;
        }

        // 1. Clear the current queue
        while (player.queueFront != NULL) {
            QueueNode* tempNode = player.queueFront;
            player.queueFront = player.queueFront->next;
            delete tempNode;
        }
        player.queueRear = NULL;

        // 2. Pop the last backup from the Stack and restore it
        int count = backupCounts[backupTop];
        for (int i = 0; i < count; i++) {
            addToQueue(backupQueues[backupTop][i]);
        }
        
        cout << "Restored previous queue (" << count << " songs)!" << endl;
        
        // 3. Clean up memory and move the Stack pointer down
        delete[] backupQueues[backupTop];
        backupTop--;
    }

    void playNext() {
        if (player.queueFront == NULL) {
            cout << "The queue is empty! No song to play next." << endl;
            return;
        }

        if (player.isPlaying) {
            StackNode* historyNode = new StackNode(player.currentSong);
            historyNode->next = player.stackTop;
            player.stackTop = historyNode;
        }

        QueueNode* temp = player.queueFront;
        player.currentSong = temp->song;
        player.queueFront = player.queueFront->next;

        if (player.queueFront == NULL) {
            player.queueRear = NULL;
        }
        delete temp;

        player.isPlaying = true;

        cout << "\n[PLAYING NOW]: " << player.currentSong.title 
             << " by " << player.currentSong.artist << endl;
    }

    void playPrevious() {
        if (player.stackTop == NULL) {
            cout << "No history available! Cannot go back." << endl;
            return;
        }

        if (player.isPlaying) {
            QueueNode* queueNode = new QueueNode(player.currentSong);
            queueNode->next = player.queueFront;
            player.queueFront = queueNode;
            if (player.queueRear == NULL) player.queueRear = queueNode;
        }

        StackNode* temp = player.stackTop;
        player.currentSong = temp->song;
        player.stackTop = player.stackTop->next;
        delete temp;

        cout << "\n[REPLAYING]: " << player.currentSong.title 
             << " by " << player.currentSong.artist << endl;
    }

    void showHistory() {
        cout << "\n--- Play History (Stack) ---" << endl;
        if (player.stackTop == NULL) {
            cout << "No history yet." << endl;
            return;
        }
        StackNode* current = player.stackTop;
        while (current != NULL) {
            cout << "- " << current->song.title << endl;
            current = current->next;
        }
    }
};

#endif
