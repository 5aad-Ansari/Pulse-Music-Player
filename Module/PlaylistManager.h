#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include <iostream>
#include <string>
#include "../Modal/Playlist.h"
using namespace std;

class PlaylistManager {
private:
    Playlist* playlists[10]; // Array of pointers to hold up to 10 playlists
    int totalPlaylists;

public:
    PlaylistManager() {
        totalPlaylists = 0;
    }

    void createPlaylist(string name) {
        if (totalPlaylists >= 10) {
            cout << "Maximum number of playlists reached!" << endl;
            return;
        }
        playlists[totalPlaylists] = new Playlist(name);
        totalPlaylists++;
        cout << "Playlist '" << name << "' created successfully." << endl;
    }

    int findPlaylistIndex(string name) {
        for (int i = 0; i < totalPlaylists; i++) {
            if (playlists[i]->name == name) {
                return i;
            }
        }
        return -1; // Not found
    }

    void addSongToPlaylist(string playlistName, Song s) {
        int index = findPlaylistIndex(playlistName);
        if (index == -1) {
            cout << "Error: Playlist '" << playlistName << "' not found!" << endl;
            return;
        }

        PlaylistNode* newNode = new PlaylistNode(s);
        Playlist* targetList = playlists[index];

        if (targetList->head == NULL) {
            targetList->head = newNode;
            targetList->tail = newNode;
        } else {
            targetList->tail->next = newNode;
            newNode->prev = targetList->tail;
            targetList->tail = newNode;
        }
        targetList->totalSongs++;
    }

    void displayPlaylist(string playlistName) {
        int index = findPlaylistIndex(playlistName);
        if (index == -1) {
            cout << "Error: Playlist '" << playlistName << "' not found!" << endl;
            return;
        }

        Playlist* targetList = playlists[index];
        cout << "\n--- Playlist: " << targetList->name << " ---" << endl;
        if (targetList->head == NULL) {
            cout << "Playlist is empty." << endl;
            return;
        }

        PlaylistNode* current = targetList->head;
        while (current != NULL) {
            cout << "- " << current->song.title << " by " << current->song.artist << endl;
            current = current->next;
        }
    }

    void displayAllPlaylists() {
        cout << "\n--- All Playlists ---" << endl;
        for (int i = 0; i < totalPlaylists; i++) {
            cout << i + 1 << ". " << playlists[i]->name 
                 << " (" << playlists[i]->totalSongs << " songs)" << endl;
        }
    }
    Song* getSongsFromPlaylist(string playlistName, int& count) {
        int index = findPlaylistIndex(playlistName);
        if (index == -1) { 
            count = 0; 
            return NULL; 
        }

        Playlist* targetList = playlists[index];
        count = targetList->totalSongs;
        if (count == 0) return NULL;

        Song* songArray = new Song[count];
        PlaylistNode* current = targetList->head;
        int i = 0;
        
        while (current != NULL) {
            songArray[i] = current->song;
            current = current->next;
            i++;
        }
        
        return songArray;
    }
};

#endif
