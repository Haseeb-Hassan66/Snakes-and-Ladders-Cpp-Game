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
3. **Run:**

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
