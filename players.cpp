#include "players.h"
#include <limits>
#include "game.h"
#define Row 10
#define Column 10
using namespace std;
std::string Players::getName() const
{
    return m_name;
}

void Players::setName(const std::string &name)
{
    m_name = name;
}

int Players::getWin() const
{
    return m_win;
}

int Players::getLose() const
{
    return m_lose;
}

int Players::getDraw() const
{
    return m_draw;
}

void Players::setWin()
{
    m_win++;
}

void Players::setLose()
{
    m_lose++;
}

void Players::setDraw()
{
    m_draw++;
}

void Players::setWinSameName(const Players &player)
{
    m_win += player.m_win;
}

void Players::setLoseSameName(const Players &player)
{
    m_lose += player.m_lose;
}

void Players::setDrawSameName(const Players &player)
{
    m_draw += player.m_draw;
}

int Players::getPoint()
{
    int totalPoints = m_win * 3 + m_draw;
    return totalPoints;
}
#define MaxN 10
// quyet dinh do thong minh cua bot
// So phan tu cua mang la so luong quan cua bot lien tiep nhau
// AttackArr[2] = 24; tuc co 2 quan O lien tiep va dc 24 diem
const int AttackArr[10] = {0, 3, 24, 192, 1536, 12288, 98304, 531441, 4782969, 50000000};
// So phan tu cua mang la so luong quan cua player lien tiep nhau
// defendArr[3] = 140; tuc co 3 quan X lien tiep va bot dc 140 diem de phong thu nuoc di nay
const int DefendArr[10] = {0, 2, 18, 140, 800, 8000, 70569, 350000, 3000000, 30000000};

bool isOverBorder(int x, int y) {
    return (x < 0 || x >= MaxN || y < 0 || y >= MaxN);
}

int AttackPoint(const vector<vector<char>>& board, int x, int y) {
    static const int tX[8] = {1, 0, 1, 1, -1, 0, -1, -1};
    static const int tY[8] = {0, 1, 1, -1, 0, -1, -1, 1};
    // luu so luong quan co theo huong ngang [0], doc [1], cheo xuong[2], cheo len[3]
    int Ally[4]{}, Enemy[4]{}, Block[4]{};

    for (int k = 0; k < 8; ++k) {
        for (int i = 1; i < 5; ++i) {
            if (isOverBorder(x + i * tX[k], y + i * tY[k])) {
                Block[k % 4]++;
                break;
            }
            if (board[x + i * tX[k]][y + i * tY[k]] == ' ') break;
            if (board[x + i * tX[k]][y + i * tY[k]] == 'O') {
                Ally[k % 4]++;
            }
            if (board[x + i * tX[k]][y + i * tY[k]] == 'X') {
                Enemy[k % 4]++;
                break;
            }
        }
    }

    int SumPoint = 0;
    for (int i = 0; i < 4; ++i) {
        int Point = AttackArr[Ally[i]];
        if (Ally[i] == 4) Point = AttackArr[9];
        if (Enemy[i] == 1 || Block[i] == 1) Point /= 2; // gap X hoac bien
        if (Enemy[i] == 1 && Ally[i] < 4 && Block[i] == 1) Point = 0; // o giua X hoac bien
        if (Enemy[i] == 2) Point = 0; // co 2 con x lien tiep
        SumPoint += Point;
    }

    return SumPoint;
}

int DefendPoint(const vector<vector<char>>& board, int x, int y) {
    static const int tX[8] = {1, 0, 1, 1, -1, 0, -1, -1};
    static const int tY[8] = {0, 1, 1, -1, 0, -1, -1, 1};
    int Ally[4]{}, Enemy[4]{}, Block[4]{};

    for (int k = 0; k < 8; ++k) {
        for (int i = 1; i < 5; ++i) {
            if (isOverBorder(x + i * tX[k], y + i * tY[k])) {
                Block[k % 4]++;
                break;
            }
            if (board[x + i * tX[k]][y + i * tY[k]] == ' ') break;
            if (board[x + i * tX[k]][y + i * tY[k]] == 'X') {
                Enemy[k % 4]++;
            }
            if (board[x + i * tX[k]][y + i * tY[k]] == 'O') {
                Ally[k % 4]++;
                break;
            }
        }
    }

    int SumPoint = 0;
    for (int i = 0; i < 4; ++i) {
        int Point = DefendArr[Enemy[i]];
        if (Enemy[i] == 4) Point = DefendArr[9];
        if (Ally[i] == 1 || Block[i] == 1) Point /= 2;
        if (Ally[i] == 1 && Enemy[i] < 4 && Block[i] == 1) Point = 0;
        if (Ally[i] == 2) Point = 0;
        SumPoint += Point;
    }

    return SumPoint;
}

pair<int, int> Players::findBestMove(vector<vector<char>>& board, int difficulty) {
    pair<int, int> bestMove = {-1, -1};
    int maxPoint = -DefendArr[9];
    for (int i = 0; i < MaxN; ++i)
        for (int j = 0; j < MaxN; ++j)
            if (board[i][j] == ' ')
            {
                int point = AttackPoint(board, i, j) + DefendPoint(board, i, j);
                // easy mode: bot choose random move with max point
                if(difficulty == 1)
                {
                    if (point > maxPoint || (point == maxPoint && rand() % 2 == 0 )) {
                        maxPoint = point;
                        bestMove = {i, j};
                    }
                }
                // normal mode: bot choose random move with max point
                else if(difficulty == 2)
                {
                    if (point > maxPoint || (point == maxPoint && rand() % 3 == 0)) {
                        maxPoint = point;
                        bestMove = {i, j};
                    }
                }
                // hard mode: bot choose move with max point
                else {
                    if (point > maxPoint) {
                        maxPoint = point;
                        bestMove = {i, j};
                    }
                }
            }
    return bestMove;
}

Players::Players(std::string n, int w = 0, int l = 0, int d = 0, bool bot = false)
    : m_name{n}, m_win{w}, m_lose{l}, m_draw{d}, m_is_bot{bot}
{

}

Players::Players(std::string n, int w = 0, int l = 0, int d = 0)
    : m_name{n}, m_win{w}, m_lose{l}, m_draw{d}, m_is_bot{false}
{

}
