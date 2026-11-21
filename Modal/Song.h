#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

class Song {
public:
    int id;
    string title;
    string artist;
    int duration;

    Song() {
        id = -1;
        title = "";
        artist = "";
        duration = 0;
    }

    Song(int _id, string _title, string _artist, int _duration) {
        id = _id;
        title = _title;
        artist = _artist;
        duration = _duration;
    }
};

#endif