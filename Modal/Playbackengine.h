#ifndef PLAYBACK_ENGINE_H
#define PLAYBACK_ENGINE_H

#include <string>
#include "Song.h"
using namespace std;

// Node for the Queue (Up Next)
class QueueNode {
public:
    Song song;
    QueueNode* next;
    QueueNode(Song s) { song = s; next = NULL; }
};

// Node for the Stack (History)
class StackNode {
public:
    Song song;
    StackNode* next;
    StackNode(Song s) { song = s; next = NULL; }
};

class PlaybackEngine {
public:
    // Queue Pointers
    QueueNode* queueFront;
    QueueNode* queueRear;

    // Stack Pointer
    StackNode* stackTop;

    // Current state
    Song currentSong;
    bool isPlaying;

    PlaybackEngine() {
        queueFront = NULL;
        queueRear = NULL;
        stackTop = NULL;
        isPlaying = false;
    }
};

#endif