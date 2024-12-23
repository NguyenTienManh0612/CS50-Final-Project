#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>
#include <vector>

using namespace std;

class Players
{
private:
    string m_name;
    int m_win;
    int m_lose;
    int m_draw;
    bool m_is_bot;
    vector<pair<int,int>> m_check_points_bot;
public:
    Players(string, int, int, int, bool);
    Players(string, int, int, int);
    string getName() const;
    void setName(const string &name);
    int getWin() const;
    int getLose() const;
    int getDraw() const;
    void setWin();
    void setLose();
    void setDraw();
    void setWinSameName(const Players& player);
    void setLoseSameName(const Players& player);
    void setDrawSameName(const Players& player);
    int getPoint();
    pair<int, int> findBestMove(std::vector<std::vector<char>>& board, int difficulty);
};

#endif // PLAYERS_H
