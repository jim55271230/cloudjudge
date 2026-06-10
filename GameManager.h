// 告訴 Visual Studio 使用 UTF-8 處理此檔案，徹底解決 C4819 警告與字串斷開報錯
#pragma execution_character_set("utf-8")

#include "GameManager.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// —— 前端主控台顏色美化設定 ——
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define COLOR_WHITE  7
#define COLOR_GREEN  10
#define COLOR_RED    12
#define COLOR_YELLOW 14
#define COLOR_CYAN   11
#define COLOR_PURPLE 13

static void setColor(int color) {
    // 已修正拼字：使用 Windows API 標準函數
    SetConsoleTextAttribute(hConsole, color);
}

static void resetColor() {
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
}

static void delay(int ms) {
    Sleep(ms);
}

// 狀態字串轉換
static const char* moveName(int move) {
    if (move == ROCK)     return "石頭 (ROCK)     ?";
    if (move == PAPER)    return "布  (PAPER)    ?";
    if (move == SCISSORS) return "剪刀 (SCISSORS)  ??";
    return "未知";
}

// 前端：繪製標題
void GameManager::drawHeader() {
    system("cls");
    setColor(COLOR_CYAN);
    cout << "=============================================\n";
    cout << "      ? 現代感終極剪刀石頭布競技場 ?      \n";
    cout << "=============================================\n";
    resetColor();
}

// 前端：繪製精美訊息框
void GameManager::drawBox(const char* message, int color) {
    setColor(color);
    cout << "\n┌──────────────────────────────────────────┐\n";
    cout << "  " << message << "\n";
    cout << "└──────────────────────────────────────────┘\n";
    resetColor();
}

// 前端：動態顯示計分板
void GameManager::displayScore() {
    setColor(COLOR_PURPLE);
    cout << "\n?? 【目前戰況】";
    setColor(COLOR_WHITE);
    cout << " 回合: " << currentRound << " / " << maxRounds << " | ";
    setColor(COLOR_GREEN);
    cout << player.getName() << ": " << humanScore;
    setColor(COLOR_WHITE);
    cout << " vs ";
    setColor(COLOR_RED);
    cout << "電腦: " << computerScore << "\n";
    cout << "─────────────────────────────────────────────\n";
    resetColor();
}

// 前端：最終大結局公告
void GameManager::displayFinalResult() {
    drawHeader();
    cout << "\n?? 遊戲結束！最終統計結果：\n";
    cout << " ?? " << player.getName() << " 總得分：" << humanScore << "\n";
    cout << " ?? 電腦總得分：" << computerScore << "\n";

    if (humanScore > computerScore) {
        drawBox(" ?? 恭喜！你以壓倒性勝利擊敗了 AI 戰神！", COLOR_GREEN);
    }
    else if (humanScore < computerScore) {
        drawBox(" ? 遺憾！人類最後的希望敗給了電腦...", COLOR_RED);
    }
    else {
        drawBox(" ?? 終局平手！這是一場傳奇般的勢均力敵！", COLOR_YELLOW);
    }
}

// 後端：電腦思考特效與隨機出拳
int GameManager::getComputerMove() {
    setColor(COLOR_YELLOW);
    cout << "\n?? 電腦正在思考中";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        delay(250);
    }
    cout << "\n";
    resetColor();
    return (rand() % 3) + 1;
}

// 後端：單回合處理邏輯
void GameManager::playRound() {
    int playerChoice;

    while (true) {
        drawHeader();
        displayScore();

        cout << " ?? 請選擇出拳編號:\n";
        setColor(COLOR_GREEN);  cout << "  [1] 石頭 ?\n";
        setColor(COLOR_PURPLE); cout << "  [2] 布 ?\n";
        setColor(COLOR_YELLOW); cout << "  [3] 剪刀 ??\n";
        resetColor();
        cout << "\n ? 你的選擇是：";

        if (!(cin >> playerChoice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (playerChoice >= 1 && playerChoice <= 3) {
            break;
        }

        setColor(COLOR_RED);
        cout << " ?? 輸入錯誤！請輸入 1, 2 或 3。\n";
        resetColor();
        delay(1000);
    }

    int computerChoice = getComputerMove();

    cout << "\n─────────────────────────────────────────────\n";
    cout << " ?? 你的選擇： " << moveName(playerChoice) << "\n";
    cout << " ?? 電腦選擇： " << moveName(computerChoice) << "\n";
    cout << "─────────────────────────────────────────────\n";

    if (playerChoice == computerChoice) {
        drawBox(" ?? 本回合平手！", COLOR_YELLOW);
    }
    else if ((playerChoice == ROCK && computerChoice == SCISSORS) ||
        (playerChoice == PAPER && computerChoice == ROCK) ||
        (playerChoice == SCISSORS && computerChoice == PAPER)) {
        drawBox(" ?? 你贏了這個回合！", COLOR_GREEN);
        humanScore++;
    }
    else {
        drawBox(" ? 你輸了這個回合！", COLOR_RED);
        computerScore++;
    }

    currentRound++;
    if (currentRound > maxRounds) {
        isGameOver = true;
    }

    cout << "\n 按任意鍵繼續下一回合...";
    system("pause > nul");
}

// 主控制流程
void GameManager::start() {
    srand(static_cast<unsigned int>(time(0)));

    drawHeader();
    string pName;
    cout << "\n ?? 歡迎來到競技場！請輸入你的名字: ";
    if (cin >> pName) {
        player.setName(pName);
    }

    cout << " ?? 設定戰局：請問要遊玩幾回合？(預設輸入 3 代表三戰兩勝): ";
    if (!(cin >> maxRounds) || maxRounds <= 0) {
        maxRounds = 3;
    }
    cin.ignore(1000, '\n');

    // 進行回合循環
    while (!isGameOver) {
        playRound();
    }

    // 展示最終結果
    displayFinalResult();
    cout << "\n 感謝遊玩！按任意鍵正式退出程式...\n";
    system("pause > nul");
}
