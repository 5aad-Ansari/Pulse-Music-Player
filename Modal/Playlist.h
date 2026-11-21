#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "Song.h"
using namespace std;

class PlaylistNode {
public:
    Song song;
    PlaylistNode* next;
    PlaylistNode* prev;

    PlaylistNode(Song s) {
        song = s;
        next = NULL;
        prev = NULL;
    }
};

class Playlist {
public:
    string name;
    PlaylistNode* head;
    PlaylistNode* tail;
    int totalSongs;

    Playlist(string _name) {
        name = _name;
        head = NULL;
        tail = NULL;
        totalSongs = 0;
    }
};

#endif