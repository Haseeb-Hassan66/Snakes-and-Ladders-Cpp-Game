#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio> // truncate mode
using namespace std;

struct Player {
    string name;
    int position;
    Color color;
    bool isActive;
    int lastRoll;
    bool hasExtraTurn;

    Player(string playerName, Color playerColor) {
        name = playerName;
        position = 0;
        color = playerColor;
        isActive = false;
        lastRoll = 0;
        hasExtraTurn = false;
    }
};

// Function prototypes
void DrawBoard();
int RollDice();
void CheckSpecialPositions(Player& player, string& message);
void DrawPlayer(Player& player);
Vector2 GetPositionCoordinates(int position);
void DrawRollDiceButton();
void DrawPlayerInfo(const Player& player, int x, int y);
void DrawLastRollInfo(const Player& player, int x, int y);
void DrawBottomMessage(const string& message);
void DrawSnake(Vector2 startPos, Vector2 endPos);

// Save/load functions
void SaveGame(const Player& player1, const Player& player2, bool player1Turn, const string& message);
bool LoadGame(Player& player1, Player& player2, bool& player1Turn, string& message);
void StartNewGame(Player& player1, Player& player2, bool& player1Turn, string& gameMessage, bool& enterNamePhase);


const int screenWidth = 1500;
const int screenHeight = 900;
const int cellSize = 80;
const int boardSize = 10;

int snakes[] = { 16, 48, 79, 93, 83 };
int snakeTargets[] = { 6, 30, 60, 37 , 10};
int ladders[] = { 3, 20, 57, 72 };
int ladderTargets[] = { 22, 41, 76, 94 };

int main() {
    InitWindow(screenWidth, screenHeight, "Saanp Seerhi");

    srand(static_cast<unsigned>(time(0)));

    string player1Name = "Player 1";
    string player2Name = "Player 2";
    bool enterNamePhase = true;
    Player player1(player1Name, BLUE);
    Player player2(player2Name, RED);
    bool player1Turn = true;
    string gameMessage = "Game started!";
    bool gameOver = false;

    // Check if a saved game exists and load it if available
    if (LoadGame(player1, player2, player1Turn, gameMessage)) {
        enterNamePhase = false;
        gameMessage = "Game loaded!";
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (enterNamePhase) {
            if (player1Turn) {
                DrawText("Enter Player 1's name:", 25, 35, 25, BLACK);
                DrawText(player1Name.c_str(), 25, 75, 25, BLUE);
                DrawText("Press Enter when done.", 25, 115, 25, BLACK);

                int key = GetCharPressed();
                while (key > 0) {
                    if (key >= 32 && key <= 125 && player1Name.length() < 30) {
                        player1Name += (char)key;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && player1Name.length() > 0) {
                    player1Name.pop_back();
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    player1.name = player1Name;
                    player1Turn = false;
                }
            }
            else {
                DrawText("Enter Player 2's name:", 25, 35, 25, BLACK);
                DrawText(player2Name.c_str(), 25, 75, 25, RED);
                DrawText("Press Enter when done.", 25, 115, 25, BLACK);

                int key = GetCharPressed();
                while (key > 0) {
                    if (key >= 32 && key <= 125 && player2Name.length() < 30) {
                        player2Name += (char)key;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && player2Name.length() > 0) {
                    player2Name.pop_back();
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    player2.name = player2Name;
                    enterNamePhase = false;
                }
            }
        }
        else {
            DrawBoard();
            DrawPlayer(player1);
            DrawPlayer(player2);
            DrawRollDiceButton();
            DrawPlayerInfo(player1, screenWidth - 200, 100);
            DrawPlayerInfo(player2, screenWidth - 200, 160);
            DrawLastRollInfo(player1, screenWidth - 200, 220);
            DrawLastRollInfo(player2, screenWidth - 200, 260);
            DrawBottomMessage(gameMessage);

            if (!gameOver && IsKeyPressed(KEY_ENTER)) {
                Player& currentPlayer = player1Turn ? player1 : player2;
                int diceRoll = RollDice();
                currentPlayer.lastRoll = diceRoll;
                gameMessage = currentPlayer.name + " rolled a " + to_string(diceRoll) + ".";

                if (!currentPlayer.isActive && diceRoll == 6) {
                    currentPlayer.isActive = true;
                    currentPlayer.position = 1;
                    currentPlayer.hasExtraTurn = true;
                }
                else if (currentPlayer.isActive) {
                    currentPlayer.position += diceRoll;
                    if (diceRoll == 6) {
                        currentPlayer.hasExtraTurn = true;
                    }
                    if (currentPlayer.position > 100) currentPlayer.position = 100;
                    CheckSpecialPositions(currentPlayer, gameMessage);
                }

                if (player1.isActive && player2.isActive && player1.position == player2.position) {
                    if (player1Turn) {
                        player2.position = 0;
                        player2.isActive = false;
                        gameMessage += " and sent " + player2.name + " back to start!";
                        currentPlayer.hasExtraTurn = true;
                    }
                    else {
                        player1.position = 0;
                        player1.isActive = false;
                        gameMessage += " and sent " + player1.name + " back to start!";
                        currentPlayer.hasExtraTurn = true;
                    }
                }

                if (currentPlayer.position == 100) {
                    gameOver = true;
                    gameMessage = currentPlayer.name + " wins!";
                }

                if (currentPlayer.hasExtraTurn) {
                    currentPlayer.hasExtraTurn = false;
                    gameMessage += " " + currentPlayer.name + " gets an extra turn!";
                }
                else {
                    player1Turn = !player1Turn;
                }
            }

            if (IsKeyPressed(KEY_S)) {
                SaveGame(player1, player2, player1Turn, gameMessage);
                gameMessage = "Game saved!";
            }

            if (IsKeyPressed(KEY_N)) {
                StartNewGame(player1, player2, player1Turn, gameMessage, enterNamePhase);
            }


            if (gameOver && IsKeyPressed(KEY_R)) {
                player1 = Player(player1.name, BLUE);
                player2 = Player(player2.name, RED);
                player1Turn = true;
                gameMessage = "Game restarted!";
                gameOver = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int cellNumber = (boardSize - i - 1) * boardSize + (i % 2 == 0 ? j + 1 : boardSize - j);
            int x = j * cellSize;
            int y = i * cellSize;

            DrawRectangleLines(x, y, cellSize, cellSize, LIGHTGRAY);
            DrawText(to_string(cellNumber).c_str(), x + 10, y + 10, 20, DARKGRAY);
        }
    }

    for (int i = 0; i < sizeof(snakes) / sizeof(snakes[0]); i++) {
        Vector2 start = GetPositionCoordinates(snakes[i]);
        Vector2 end = GetPositionCoordinates(snakeTargets[i]);
        DrawSnake(start, end);
    }

    for (int i = 0; i < sizeof(ladders) / sizeof(ladders[0]); i++) {
        Vector2 start = GetPositionCoordinates(ladders[i]);
        Vector2 end = GetPositionCoordinates(ladderTargets[i]);
        DrawLineEx(start, end, 5, GREEN);
    }
}

void DrawSnake(Vector2 startPos, Vector2 endPos) {
    DrawLineBezier(startPos, endPos, 3.0f, RED);
}

int RollDice() {
    return rand() % 6 + 1;
}

void CheckSpecialPositions(Player& player, string& message) {
    for (int i = 0; i < sizeof(snakes) / sizeof(snakes[0]); i++) {
        if (player.position == snakes[i]) {
            player.position = snakeTargets[i];
            message += " Oops! Landed on a snake! Moved to position " + to_string(player.position) + ".";
            return;
        }
    }

    for (int i = 0; i < sizeof(ladders) / sizeof(ladders[0]); i++) {
        if (player.position == ladders[i]) {
            player.position = ladderTargets[i];
            message += " Yay! Landed on a ladder! Moved to position " + to_string(player.position) + ".";
            return;
        }
    }
}

void DrawPlayer(Player& player) {
    if (player.position > 0) {
        Vector2 playerPos = GetPositionCoordinates(player.position);
        DrawCircleV(playerPos, 15, player.color);
    }
}

Vector2 GetPositionCoordinates(int position) {
    int row = (position - 1) / boardSize;
    int col = (position - 1) % boardSize;
    if (row % 2 == 0) {
        col = boardSize - 1 - col;
    }
    return { (float)(col * cellSize + cellSize / 2), (float)((boardSize - row - 1) * cellSize + cellSize / 2) };
}

void DrawRollDiceButton() {
    DrawRectangle(screenWidth / 2 - 50, screenHeight - 100, 100, 40, LIGHTGRAY);
    DrawText("Roll Dice", screenWidth / 2 - 40, screenHeight - 90, 20, BLACK);
}

void DrawPlayerInfo(const Player& player, int x, int y) {
    DrawText(player.name.c_str(), x, y, 20, player.color);
    string position = "Position: " + to_string(player.position);
    DrawText(position.c_str(), x, y + 30, 20, BLACK);
}

void DrawLastRollInfo(const Player& player, int x, int y) {
    string lastRoll = "Last Roll: " + to_string(player.lastRoll);
    DrawText(lastRoll.c_str(), x, y, 20, BLACK);
}

void DrawBottomMessage(const string& message) {
    DrawText(message.c_str(), 20, screenHeight - 40, 20, DARKGRAY);
}

void SaveGame(const Player& player1, const Player& player2, bool player1Turn, const string& message) {
    ofstream saveFile("E:\\Projects\\C++  Projects\\Snakes-and-Ladders-Cpp-Game\\save\\game_save.txt");
    if (saveFile.is_open()) {
        saveFile << player1.name << endl
            << player1.position << endl
            << player1.isActive << endl
            << player1.lastRoll << endl;

        saveFile << player2.name << endl
            << player2.position << endl
            << player2.isActive << endl
            << player2.lastRoll << endl;

        saveFile << player1Turn << endl;
        saveFile << message << endl;

        saveFile.close();
    }
}

void StartNewGame(Player& player1, Player& player2, bool& player1Turn, string& gameMessage, bool& enterNamePhase) {
    player1 = Player("Player 1", BLUE);
    player2 = Player("Player 2", RED);
    player1Turn = true;
    gameMessage = "Enter names for new players.";
    enterNamePhase = true;

    ofstream saveFile("E:\\Projects\\C++  Projects\\Snakes-and-Ladders-Cpp-Game\\save\\game_save.txt", ios::trunc);

    if (saveFile.is_open()) {
        saveFile.close();
    }
}


bool LoadGame(Player& player1, Player& player2, bool& player1Turn, string& message) {
    ifstream loadFile("E:\\Projects\\C++  Projects\\Snakes-and-Ladders-Cpp-Game\\save\\game_save.txt");

    // Check if the file is open and not empty
    if (loadFile.is_open() && loadFile.peek() != ifstream::traits_type::eof()) {
        getline(loadFile, player1.name);
        loadFile >> player1.position >> player1.isActive >> player1.lastRoll;
        loadFile.ignore(); 

        getline(loadFile, player2.name);
        loadFile >> player2.position >> player2.isActive >> player2.lastRoll;
        loadFile.ignore(); 

        loadFile >> player1Turn;
        loadFile.ignore(); 
        getline(loadFile, message);

        loadFile.close();
        return true; // Game loaded successfully
    }

    
    return false;
}