# Pulse-Music-Player
Pulse Music Player
# 🎵 PULSE — iPod-Style Music Player (DSA Showcase)

PULSE is a retro iPod-inspired music player that demonstrates core **Data Structures & Algorithms** in two parallel implementations:

1. **A fully interactive web/desktop player** (vanilla JavaScript + Electron)
2. **A matching C++ console application** using the same structures

![PULSE Player](preview.png)

---

## 🚀 Live Demo

👉 **Play it here:** [https://<your-username>.github.io/pulse/](https://<your-username>.github.io/pulse/)

Use the click wheel (drag with mouse/finger), arrow keys, and the center button just like a real iPod.

---

## 🧩 Data Structures Used

| Feature | Data Structure | File |
|---|---|---|
| Alphabetical catalog + ID lookup | **Binary Search Tree** + **Hash Map (chaining)** | `SongCatalog.h` |
| Playlists | **Doubly Linked List** | `Playlist.h` / `PlaylistManager.h` |
| Playback engine (queue + undo history) | **Queue (linked list)** + **Stack** | `Playbackengine.h` / `PlaybackEngineModule.h` |
| Smart shuffle | **Min-Heap** (priority = play count) | `SmartShuffle.h` / `SmartShuffleModule.h` |
| Search & sort | **QuickSort** + **Binary Search** | `SearchSort.h` / `SearchSortModule.h` |

---

## ✨ Features

- 🎛️ **Skeuomorphic iPod UI** — click wheel, LCD screen, MENU/prev/next/play buttons
- 🎨 **Body color themes** — Silver, Black, Red, Blue
- 🔊 **Optional click-wheel sound** (Web Audio API)
- 📱 **Responsive + keyboard & touch support**
- 📂 **Playlists** with "send to queue" + multi-level queue restore
- 🔀 **Smart Shuffle** using a priority min-heap
- ⏯️ **Now Playing** screen with progress bar & auto-advance
- 🔍 **Search by ID** (hash map) and **by title** (binary search on sorted array)

---

## 🛠️ Tech Stack

- **Frontend:** HTML, CSS, Vanilla JavaScript (no frameworks)
- **Desktop:** Electron
- **Backend/CLI:** C++ (STL-free custom implementations)
- **Deployment:** GitHub Pages

---

## 📦 Run Locally

### Web Version
Just open `index.html` in any modern browser. No build step needed.

### Desktop (Electron)
```bash
npm install
npm start
