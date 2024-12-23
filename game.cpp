#include "game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

void Game::setCurrentPlayer(char currentPlayer)
{
    m_currentPlayer = currentPlayer;
}

Game::Game() : m_size(10), m_currentPlayer('X') {
    m_board.resize(10, vector<char>(10, ' '));
}
// get data members
int Game::getSize() const
{
    return m_size;
}
vector<vector<char> > Game::getBoard() const
{
    return m_board;
}
vector<pair<int, int> > Game::getMoves() const
{
    return m_moves;
}
char Game::getCurrentPlayer() const
{
    return m_currentPlayer;
}

//handle logic game
bool isValidMove(const string& str)
{
    if(str.length() != 3)
        return false;
    return (str[0] >= '0' && str[0] <= '9') && (str[2] >= '0' && str[2] <= '9') && (str[1] == ' ');
}
bool isFileEmpty(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    return file.tellg() == 0;
}
void emptyFile(const string& filename) {
  ofstream outfile(filename, ios::trunc | ios::out);
  if (!outfile.is_open())
    cerr << "Error opening file: " << filename << endl;
  outfile.close();
}
// record new match in replay file
void clearFile()
{
    string fileName = "SavedMove";
    emptyFile(fileName);
}
void Game::printBoard()
{
    //       0   1
    //     |---|---|
    //   0 |   |   |
    //     |---|---|
    // print index of columns
    cout << "\x1b[38;5;93m";
    cout << "  ";
    for (int i = 0; i < m_size; ++i) {
        cout << setw(4) << i;
    }
    cout << endl;
    cout << "\x1b[38;5;136m";
    // print the first |---
    cout << "   ";
    for (int i = 0; i < m_size; ++i) {
        cout << "|---";
    }
    cout << "|" << endl;

    // print the next row that included row index
    for (int row = 0; row < m_size; ++row)
    {
        cout << " " << "\x1b[38;5;93m" << row << "\x1b[38;5;136m" << " |";
        // print the value in box
        for (int col = 0; col < m_size; ++col)
        {
            if(m_board[row][col] == 'X')
                cout << " " << "\x1b[38;5;21m" << m_board[row][col] << "\x1b[38;5;136m" << " |";
            else if(m_board[row][col] == 'O')
                cout << " " << "\x1b[38;5;196m" << m_board[row][col] << "\x1b[38;5;136m" << " |";
            else
                cout << "\x1b[38;5;136m" << "   |";
        }
        cout << endl;
        cout << "\x1b[38;5;136m";
        // print next |---
        cout << "   ";
        for (int col = 0; col < m_size; ++col) {
            cout << "|---";
        }
        cout << "|" << endl;
        cout << "\033[0m";
    }
}
void Game::clearBoard()
{
    m_board.assign(m_size, vector<char>(m_size, ' ')); //assign coordinate (x,y) to whitespace => clear board
}
bool Game::isWinningMove(int x, int y)
{
    char player = m_board[x][y];
    const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}}; // vector right, down, down-right, down-left

    for (const auto& dir : directions) {
        int count = 1;
        //check right
        for (int i = 1; i < 5; ++i) {
            int nx = x + dir[0] * i;
            int ny = y + dir[1] * i;
            if (nx >= 0 && nx < m_size && ny >= 0 && ny < m_size && m_board[nx][ny] == player) {
                count++;
            } else {
                break;
            }
        }
        //check left
        for (int i = 1; i < 5; ++i) {
            int nx = x - dir[0] * i;
            int ny = y - dir[1] * i;
            if (nx >= 0 && nx < m_size && ny >= 0 && ny < m_size && m_board[nx][ny] == player) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) return true;
    }

    return false;
}
bool Game::checkWin()
{
    if (m_moves.empty()) return false;
    pair<int, int> lastMove = m_moves.back();
    int x = lastMove.first;
    int y = lastMove.second;
    return isWinningMove(x, y);
}
bool Game::checkDraw()
{
    int count = 0;
    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < m_size; ++j)
        {
            if(m_board[i][j] != ' ')
                count++;
        }
    }
    if(count == 100) return true;
    return false;
}
void Game::switchPlayer()
{
    m_currentPlayer = (m_currentPlayer == 'X') ? 'O' : 'X';
}
bool Game::makeMove(int x, int y)
{
    if (x >= 0 && x < m_size && y >= 0 && y < m_size && m_board[x][y] == ' ')
    {
        m_board[x][y] = m_currentPlayer; //stores value X or O
        saveMove(x, y);
        return true;
    }
    return false; // invalid moving
}
void Game::saveMove(int x, int y)
{
    string fileName = "SavedMove";
    m_moves.push_back({x, y});
    ofstream file(fileName, ios::app);
    if (file.is_open())
    {
        file << m_currentPlayer << " " << x << " " << y << endl;
        file.close();
    } else {
        cerr << "Unable to open moves file for writing." << endl;
    }
}
void Game::replayMoves()
{
    clearBoard();
    //
    string fileName = "SavedMove";
    ifstream input(fileName);
    if(isFileEmpty(fileName))
    {
        cout << "Replay file is empty!" << endl;
        cout << "Press <Enter> to back to the Main Menu!" << endl;
        //cin.ignore();
        getchar();
        return;
    }
    if (!input.is_open())
    {
        cout << "Error: Unable to open replay file." << endl;
        cout << "Press <Enter> to back to the Main Menu!" << endl;
        //cin.ignore();
        getchar();
        return;
    }
    char player;
    int x, y;
    string line;
    printBoard();
    cout << "Press <Enter> to continue!" << endl;
    //cin.ignore();
    getchar();
    while (getline(input,line))
    {
        stringstream ss(line);
        ss >> player >> x >> y;
        m_board[x][y] = player;
        system("cls");
        printBoard();
        cout << "Press <Enter> to continue!" << endl;
        getchar();
    }
    input.close();
}

void Game::savePlayers(Players& player)
{
    ofstream save("players");
    m_players.push_back(player);
    int size = m_players.size();
    for(int i = 0; i < size; ++i)
    {
        for(int j = i + 1; j < size; ++j)
        {
            // delete player who has the same name
            if(m_players.at(i).getName() == m_players.at(j).getName())
            {
                m_players.at(i).setWinSameName(m_players.at(j));
                m_players.at(i).setLoseSameName(m_players.at(j));
                m_players.at(i).setDrawSameName(m_players.at(j));
                m_players.pop_back();
                break;
            }
        }
        if(m_players.size() < size)
            break;
    }
    for (int i = 0; i < m_players.size(); ++i)
    {
        save << m_players.at(i).getName() << ',' << m_players.at(i).getWin() << ' '
             << m_players.at(i).getLose() << ' ' << m_players.at(i).getDraw() << endl;
    }
}
void Game::loadPlayers()
{
    ifstream file;
    string fileName = "players";
    file.open(fileName);
    string name, line;
    int wins, losses, draws;
    while (!file.eof())
    {
        getline(file,line);
        if(line.empty()) break;
        stringstream ss(line);
        getline(ss,name,',');
        ss >> wins >> losses >> draws;
        m_players.push_back(Players(name, wins, losses, draws));
    }
}
void sort(vector<Players>& players)
{
    for(size_t i = 0; i < players.size() - 1; i++)
    {
        int max_idx = i;
        for(size_t j = i + 1; j < players.size(); j++)
        {
            if(players.at(j).getPoint() > players.at(max_idx).getPoint())
            {
                max_idx = j;
            }
        }
        swap(players.at(i), players.at(max_idx));
    }
}
void Game::displayPlayerInfo()
{
    if(m_players.empty())
    {
        cout << "No record about players!\nLet's play a game to be a \x1b[38;5;196mking\033[0m of this game!" << endl;
        return;
    }
    sort(m_players);
    for (const auto& player : m_players) {
        cout << "\x1b[38;5;165m" << "Name: " << player.getName() << " - " << "\x1b[38;5;21m" << "Wins: "
             << player.getWin() << " - " << "\x1b[38;5;196m" << "Losses: " << player.getLose()
             << " - " << "\x1b[38;5;34m" << "Draws: " << player.getDraw() << endl;
        cout << "\033[0m";
    }
}
string toLower(const string& str)
{
    string result = str;
    int len = str.length();
    for(int i = 0; i < len; i++)
    {
        if(str[i] > 'A' && str[i] < 'Z')
            result[i] = tolower(str[i]);
    }
    return  result;
}
void Game::findPlayer(const string &name)
{
    bool flag = true;
    for (auto& player : m_players) {
        if (toLower(player.getName()) == toLower(name)) {
            cout << "\x1b[38;5;165m" << "Name: " << player.getName() << " - " << "\x1b[38;5;21m" << "Wins: "
                 << player.getWin() << " - " << "\x1b[38;5;196m" << "Losses: " << player.getLose()
                 << " - " << "\x1b[38;5;34m" << "Draws: " << player.getDraw() << endl;
            cout << "\033[0m";
            flag = false;
        }
    }
    if(flag)
        cout << "Unable to find player with name:\x1b[38;5;165m " << name << "\033[0m" << endl;
}

void Game::findPlayerSameLevel(const string &name)
{
    bool flag = true;
    for(size_t i = 0; i < m_players.size(); i++)
    {
        if (m_players[i].getName() == name)
        {
            for(size_t j = 0; j < m_players.size(); j++)
            {
                if((m_players[j].getPoint() == m_players[i].getPoint()
                        || m_players[j].getPoint() == (m_players[i].getPoint() - 1)
                        || m_players[j].getPoint() == (m_players[i].getPoint() + 1)
                        || m_players[j].getPoint() == (m_players[i].getPoint() - 2)
                        || m_players[j].getPoint() == (m_players[i].getPoint() + 2))
                        && m_players[j].getName() != m_players[i].getName())
                {
                    cout << "\x1b[38;5;165m" << "Name: " << m_players[j].getName() << endl;
                    cout << "\033[0m";
                    flag = false;
                }
            }
        }
    }
    if(flag)
        cout << "Unable to find players with the same level!" << endl;
}

void Game::playerVsPlayer(string& playerName1, string& playerName2)
{
    clearFile();
    clearBoard();
    Players player1(playerName1,0,0,0);
    Players player2(playerName2,0,0,0);
    pair<char, string> p1 = make_pair('X', playerName1);
    pair<char, string> p2 = make_pair('O', playerName2);
    setCurrentPlayer('X');
    int x, y; //coordinate of each move
    string coordinate {};
    while (true)
    {
        system("cls");
        cout << "Player " << "\x1b[38;5;21m" << "X" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName1
             << "\x1b[38;5;136m" << "     vs     " << "\033[0m" << "Player " << "\x1b[38;5;196m" << "O" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName2 << endl;
        printBoard();
        if(getCurrentPlayer() == 'X')
            cout << "Player " << "\x1b[38;5;21m" << p1.first << "\033[0m" << " (" << "\x1b[38;5;34m" << p1.second << "\033[0m" << ")" << ", enter your move (row and column): ";
        else
            cout << "Player " << "\x1b[38;5;196m" << p2.first << "\033[0m" << " (" << "\x1b[38;5;34m" << p2.second << "\033[0m" << ")" << ", enter your move (row and column): ";
        if(checkDraw())
        {
            system("cls");
            cout << "Player " << "\x1b[38;5;21m" << "X" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName1
                 << "\x1b[38;5;136m" << "     vs     " << "\033[0m" << "Player " << "\x1b[38;5;196m" << "O" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName2 << endl;
            printBoard();
            cout << "\n=====================\x1b[38;5;196m Draw! Draw! Draw! Draw! Draw! \033[0m=====================\n" << endl;
            player1.setDraw();
            player2.setDraw();
            cout << "Please \x1b[38;5;136m<Enter>\033[0m to back to Main Menu!" << endl;
            //cin.ignore();
            getchar();
            break;
        }
        getline(cin,coordinate);
        if(!isValidMove(coordinate))
        {
            cout << "Invalid move. Try again." << endl;
            sleep(1);
        } else {
            stringstream getCoordinate(coordinate);
            getCoordinate >> x >> y;
            if (makeMove(x, y))
            {
                if (checkWin())
                {
                    system("cls");
                    cout << "Player X: " << playerName1 << "     vs     " << "Player O: " << playerName2 << endl;
                    printBoard(); //print the last moving
                    if(getCurrentPlayer() == 'X')
                    {
                        cout << "\n===================== Player \x1b[38;5;196m" << p1.second << "\033[0m wins!=====================\n" << endl;
                        player1.setWin();
                        player2.setLose();
                    }
                    else
                    {
                        cout << "\n===================== Player \x1b[38;5;196m" << p2.second << "\033[0m wins!=====================\n" << endl;
                        player2.setWin();
                        player1.setLose();
                    }
                    savePlayers(player1);
                    savePlayers(player2);
                    cout << "Please \x1b[38;5;136m<Enter>\033[0m to back to Main Menu!" << endl;
                    //cin.ignore();
                    getchar();
                    break;
                }
                switchPlayer();
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
                sleep(1); //millisecond
            }
        }
    }
}

void Game::playerVsBot(string & playerName, int difficulty)
{
    clearFile();
    clearBoard();
    Players player(playerName,0,0,0);
    Players bot("Bot",0,0,0,true);
    pair<char, string> p1 = make_pair('X', playerName);
    pair<char, string> p2 = make_pair('O', "Bot");
    int x, y;
    string coordinate;
    setCurrentPlayer('X');
    while (true)
    {
        system("cls");
        cout << "Player " << "\x1b[38;5;21m" << "X" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName
             << "\x1b[38;5;136m" << "     vs     " << "\033[0m" << "Player " << "\x1b[38;5;196m" << "O" << "\033[0m" << ": " << "\x1b[38;5;34mBot" << endl;
        printBoard();
        if (getCurrentPlayer() == 'X')
        {
            cout << "Player \x1b[38;5;21m" << p1.first << " \033[0m(\x1b[38;5;34m" << p1.second << "\033[0m)" << ", enter your move (row and column): ";
            getline(cin,coordinate);
            if(!isValidMove(coordinate))
            {
                cout << "Invalid move. Try again." << endl;
                sleep(1);
            } else {
                stringstream getCoordinate(coordinate);
                getCoordinate >> x >> y;
                //cin >> x >> y;
                if (makeMove(x, y))
                {
                    if (checkWin())
                    {
                        system("cls");
                        cout << "Player " << "\x1b[38;5;21m" << "X" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName
                             << "\x1b[38;5;136m" << "     vs     " << "\033[0m" << "Player " << "\x1b[38;5;196m" << "O" << "\033[0m" << ": " << "\x1b[38;5;34mBot" << endl;
                        printBoard(); //print the last moving
                        cout << "\n===================== Player \x1b[38;5;196m" << p1.second << "\033[0m wins!=====================\n" << endl;
                        player.setWin();
                        savePlayers(player);
                        cout << "Please \x1b[38;5;136m<Enter>\033[0m to back to Main Menu!" << endl;
                        //cin.ignore();
                        getchar();
                        break;
                    }
                    switchPlayer();
                } else {
                    cout << "Invalid move. Try again." << endl;
                    sleep(1);
                }
            }
        } else {
            cout << "Bot is making a move..." << endl;
            auto board = getBoard();
            auto move = bot.findBestMove(board, difficulty);
            makeMove(move.first, move.second);
            if (checkWin()) {
                system("cls");
                printBoard();
                cout << "\n============================ \x1b[38;5;196m" << p2.second << "\033[0m wins!============================\n" << endl;
                player.setLose();
                savePlayers(player);
                cout << "Please \x1b[38;5;136m<Enter>\033[0m to back to Main Menu!" << endl;
                //cin.ignore();
                getchar();
                break;
            }
            switchPlayer();
        }
        if(checkDraw())
        {
            system("cls");
            cout << "Player " << "\x1b[38;5;21m" << "X" << "\033[0m" << ": " << "\x1b[38;5;34m" << playerName
                 << "\x1b[38;5;136m" << "     vs     " << "\033[0m" << "Player " << "\x1b[38;5;196m" << "O" << "\033[0m" << ": " << "\x1b[38;5;34mBot" << endl;
            printBoard();
            cout << "\n=====================\x1b[38;5;196m Draw! Draw! Draw! Draw! Draw! \033[0m=====================\n" << endl;
            player.setDraw();
            cout << "Please \x1b[38;5;136m<Enter>\033[0m to back to Main Menu!" << endl;
            //cin.ignore();
            getchar();
            break;
        }
    }
}
void Game::instruction()
{
    cout << "===============================\x1b[38;5;21mINSTRUCTION\033[0m===============================" << endl;
    cout << endl;
    cout << "Caro is a board game based on the popular Japanese strategy board game called Gomoku.\n"
         << "The game is played on a 10 x 10 grid.\n"
         << "The player 1 representing the “X” symbol gets to take the first turn followed by the player representing the “O” symbol.\n"
         << "Players take turns placing their symbol on an open intersection on the board.\n"
         << "To take their moves, players need to enter the coordinate of moves.\n"
         << "Players have to race to create an unbroken row of five symbols while blocking their opponent to prevent them from creating five in a row.\n"
         << "The player that manages to create five in a row first wins the round.\nThe row can be horizontal, vertical, or diagonal as long as it is unbroken."
         << '\n'
         << "To reach the top of the ranking, players need to gain as many wins as possible.\n\n"
         << "\x1b[38;5;196mEach win will get 3 points, draw 1 point and loss no points.\033[0m"
         << endl;
}
