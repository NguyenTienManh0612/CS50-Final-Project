#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "players.h"

using namespace std;

class Game
{
private:
    vector<vector<char>> m_board;
    int m_size;
    char m_currentPlayer;
    vector<pair<int, int>> m_moves;
    vector<Players> m_players;

public:
    Game();
    void printBoard();
    bool makeMove(int x, int y);
    void saveMove(int x, int y);
    bool isWinningMove(int x, int y);
    bool checkWin();
    bool checkDraw();
    void switchPlayer();
    void replayMoves();
    void clearBoard();
    void loadPlayers();
    void savePlayers(Players&);
    void displayPlayerInfo();
    void findPlayer(const string& name);
    void findPlayerSameLevel(const string &name);
    int getSize() const;
    vector<vector<char> > getBoard() const;
    vector<pair<int, int> > getMoves() const;
    char getCurrentPlayer() const;
    void playerVsPlayer(string& playerName1, string& playerName2);
    void playerVsBot(string& playerName, int difficulty);
    void instruction();
    void setCurrentPlayer(char currentPlayer);
};

#endif // GAME_H
