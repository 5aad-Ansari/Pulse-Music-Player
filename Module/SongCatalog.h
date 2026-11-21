#ifndef SONG_CATALOG_H
#define SONG_CATALOG_H

#include <iostream>
#include "../Modal/Song.h"
using namespace std;


// Custom BST for Aphabetical Sort
class BSTNode {
public:
    Song data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Song s) {
        data = s;
        left = NULL;
        right = NULL;
    }
};

class SongBST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, Song s) {
        if (node == NULL) return new BSTNode(s);
        
        if (s.title < node->data.title)
            node->left = insertHelper(node->left, s);
        else
            node->right = insertHelper(node->right, s);
            
        return node;
    }

    void inorderHelper(BSTNode* node) {
        if (node == NULL) return;
        inorderHelper(node->left);
        cout << "ID: " << node->data.id << " | " << node->data.title << " by " << node->data.artist << endl;
        inorderHelper(node->right);
    }

public:
    SongBST() { root = NULL; }
    void insert(Song s) { root = insertHelper(root, s); }
    void displayAlphabetical() { inorderHelper(root); }
};

// 2. hash table for fast id find
class HashNode {
public:
    int key;
    Song value;
    HashNode* next;
    
    HashNode(int k, Song v) {
        key = k;
        value = v;
        next = NULL;
    }
};

class SongHashMap {
private:
    static const int TABLE_SIZE = 100; 
    HashNode* table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE; 
    }

public:
    SongHashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    void insert(int key, Song value) {
        int index = hashFunction(key);
        HashNode* newNode = new HashNode(key, value);
        
        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    Song* find(int key) {
        int index = hashFunction(key);
        HashNode* temp = table[index];
        
        while (temp != NULL) {
            if (temp->key == key) {
                return &(temp->value);
            }
            temp = temp->next;
        }
        return NULL; // Safely returns NULL if not found
    }
};

// 3. module logic
class SongCatalog {
private:
    SongBST songTree;       
    SongHashMap songHash;   
    int totalSongs;

public:
    SongCatalog() {
        totalSongs = 0;
    }

    void addSong(int id, string title, string artist, int duration) {
        Song newSong(id, title, artist, duration);
        songTree.insert(newSong);
        songHash.insert(id, newSong);
        totalSongs++;
        cout << "Successfully added: " << title << endl;
    }

    void searchByID(int id) {
        Song* found = songHash.find(id);
        if (found != NULL) {
            cout << "\n--- Song Found ---" << endl;
            cout << "ID: " << found->id << endl;
            cout << "Title: " << found->title << endl;
            cout << "Artist: " << found->artist << endl;
            cout << "Duration: " << found->duration << "s" << endl;
        } else {
            cout << "Song with ID " << id << " not found." << endl;
        }
    }

    void displayCatalogAlphabetical() {
        cout << "\n--- Full Catalog (A-Z) ---" << endl;
        if (totalSongs == 0) {
            cout << "Catalog is empty." << endl;
        } else {
            songTree.displayAlphabetical();
        }
    }
};

#endif
