#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"

// 定義出拳狀態列舉
enum Move {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

class GameManager {
public:
    void start(); // 遊戲啟動主入口

private:
    void drawHeader();         // 前端：霓虹標題
    void drawBox(const char* message, int color); // 前端：結果對話框
    void displayScore();       // 前端：計分板
    void displayFinalResult(); // 前端：大結局結算
    int getComputerMove();     // 後端：電腦思考與出拳
    void playRound();          // 後端：單回合勝負核心

    // 遊戲核心數據
    Player player;
    int humanScore = 0;
    int computerScore = 0;
    int currentRound = 1;
    int maxRounds = 3;
    bool isGameOver = false;
};

#endif // GAMEMANAGER_H#pragma once
