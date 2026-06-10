#include "GameManager.h"
#include <windows.h>

int main() {
    // 強制 Visual Studio 輸出的控制台視窗採用 UTF-8 編碼，完美顯示 Emoji 與中文外框
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    GameManager game;
    game.start();
    return 0;
}
