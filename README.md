# 🎲 Snakes and Ladders Game (C++ with Raylib)

A two-player **Snakes and Ladders** game built in **C++** with a custom GUI using the **Raylib** graphics library. Includes dice rolling, snake/ladder logic, turn system, name input, and save/load functionality.

---

## 📌 Features

- 🎮 Two-player gameplay with name input  
- 🎲 Dice rolling with 6 = extra turn  
- 🐍 Snakes and ladders mapped on board  
- 🔁 Send opponent back to start on same tile and gives a extra turn 
- 💾 Save and Load game (manual with `S` key)  
- 🔄 Start new game with `N`, restart with `R`  
- 🖼️ GUI built using **Raylib**

---

## 📁 Project Structure

```
Snakes-And-Ladders-CPP/
│
├── src/
│   └── main.cpp              # Main game file
└── README.md
```

---

## ⚙️ Requirements

- C++ compiler (g++, clang++)
- Raylib library installed

---

## ▶️ How to Run


1. **Install Raylib**
2. **Compile**
3. **Run**

---

## 💾 Save File

- Game data is saved in:
- save/game_save.txt

## ⚠️ Important:

- The current code uses a hardcoded file path like:
E:\\Projects\\C++  Projects\\Snakes-and-Ladders-Cpp-Game\\save\\game_save.txt

- To make the game work on your own system, you must update this path in main.cpp to match your directory. For example:
ofstream saveFile("save/game_save.txt");
ifstream loadFile("save/game_save.txt");

- This ensures the game will save/load properly from your local folder and works for any user on any system.

---

## 💾 Controls

| Key     | Action               |
|---------|----------------------|
| Enter   | Roll dice            |
| S       | Save game state      |
| N       | Start a new game     |
| R       | Restart game (after win) |

---

## 💡 Save File

Game data is saved in:

```
save/game_save.txt
```

You can edit `main.cpp` to change the path if needed.

---


## 🙌 Credits

- Developed by Haseeb Hassan  
- Powered by [Raylib](https://www.raylib.com/)

---

## 📄 License

MIT License – free to use, modify, and share.
