#include <iostream>
#include <iomanip>
#include "game.h"
/*
**Author: Nguyen Tien Manh
**ID    : ManhNT50
*/
using namespace std;
bool exitMenu {false};
bool isValidChoice(const string& str)
{
    if(str.length() != 1)
        return false;
    char ch = str[0];
    return ch >= '0' && ch <= '9';
}
int main()
{
    Game game;
    game.loadPlayers();
    string mode {};
    string playerName1, playerName2;
    string playerName;
    while (!exitMenu) {
        system("cls");
        cout <<  "\x1b[38;2;34;35;36m";
        cout<<"        ██████╗ █████╗ ██████╗  ██████╗ "<<endl;
        cout<<"       ██╔════╝██╔══██╗██╔══██╗██╔═══██╗"<<endl;
        cout<<"       ██║     ███████║██████╔╝██║   ██║"<<endl;
        cout<<"       ██║     ██╔══██║██╔══██╗██║   ██║"<<endl;
        cout<<"       ╚██████╗██║  ██║██║  ██║╚██████╔╝"<<endl;
        cout<<"        ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ "<<endl;
        cout << "\033[0m" << endl;
        cout << "1. " << "\x1b[38;5;160mPlayer\033[0m" << " vs " <<  "\x1b[38;5;160m" << "Player" << endl;
        cout << "\033[0m" << "2. " << "\x1b[38;5;160mPlayer\033[0m" << " vs " << "\x1b[38;5;160mBot" << endl;
        cout << "\033[0m" << "3. \x1b[38;5;93mReplay\033[0m the previous match" << endl;
        cout << "4. Player's \x1b[38;5;34mInformation\033[0m" << endl;
        cout << "5. \x1b[38;5;130mGuide\033[0m" << endl;
        cout << "0. \x1b[38;5;160mExit\033[0m\n" << endl;
        cout << "Press \x1b[38;5;27m<Number>\033[0m to choice: ";
        getline(cin, mode);
        if(!isValidChoice(mode))
        {
            cout << "Invalid mode selected!" << endl;
            cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
            getchar();
        }
        else
        switch (stoi(mode)) {
        case 1:
            system("cls");
            cout << "*-------------------\x1b[38;5;27mPLAYER VS PLAYER\033[0m-------------------*\n" << endl;
            cout << "Player 1st: " << endl;
            cout << "Enter your \x1b[38;5;196mname\033[0m: ";
            getline(cin, playerName1);
            cout << "Player 2nd: " << endl;
            cout << "Enter your \x1b[38;5;196mname\033[0m: ";
            getline(cin, playerName2);
            while(playerName1 == playerName2)
            {
                cout << "Player 2's name must be \x1b[38;5;160mdifferent\033[0m with player 1's one!" << endl;
                cout << "Please type again!" << endl;
                getchar();
                system("cls");
                cout << "*-------------------\x1b[38;5;27mPLAYER VS PLAYER\033[0m-------------------*" << endl;
                cout << "Player 1st: " << endl;
                cout << "Enter your \x1b[38;5;196mname\033[0m: " << playerName1 << endl;
                cout << "Player 2nd: " << endl;
                cout << "Enter your \x1b[38;5;196mname\033[0m: ";
                getline(cin, playerName2);
            }
            game.playerVsPlayer(playerName1, playerName2);
            break;
        case 2:
            while(!exitMenu)
            {
                system("cls");
                cout << "*-------------------\x1b[38;5;27mPLAYER VS BOT\033[0m-------------------*\n" << endl;
                cout << "1. \x1b[38;5;196mEasy\033[0m mode" << endl;
                cout << "2. \x1b[38;5;196mNormal\033[0m mode" << endl;
                cout << "3. \x1b[38;5;196mHard\033[0m mode" << endl;
                cout << "4. Back to main menu\n" << endl;
                cout << "Press \x1b[38;5;27m<Number>\033[0m to choice: ";
                string choice;
                getline(cin,choice);
                if(!isValidChoice(choice))
                {
                    cout << "Invalid mode selected!" << endl;
                    cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
                    getchar();
                }
                else
                switch(stoi(choice))
                {
                case 1:
                    system("cls");
                    cout << "*-------------------\x1b[38;5;27mEASY MODE\033[0m-------------------*\n" << endl;
                    cout << "Enter your \x1b[38;5;196mname\033[0m: ";
                    getline(cin, playerName);
                    game.playerVsBot(playerName, 1);
                    break;
                case 2:
                    system("cls");
                    cout << "*-------------------\x1b[38;5;27mNORMAL MODE\033[0m-------------------*\n" << endl;
                    cout << "Enter your \x1b[38;5;196mname\033[0m: ";
                    getline(cin, playerName);
                    game.playerVsBot(playerName, 2);
                    break;
                case 3:
                    system("cls");
                    cout << "*-------------------\x1b[38;5;27mHARD MODE\033[0m-------------------*\n" << endl;
                    cout << "Enter your \x1b[38;5;196mname\033[0m: ";
                    getline(cin, playerName);
                    game.playerVsBot(playerName, 3);
                    break;
                case 4:
                    exitMenu = true;
                    break;
                default:
                    cout << "Invalid mode selected!" << endl;
                    cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
                    getchar();
                }
            }
            exitMenu = false;
            break;
        case 3:
            system("cls");
            game.replayMoves();
            break;
        case 4:
            while(!exitMenu)
            {
                system("cls");
                cout << "*-------------------\x1b[38;5;27mPLAYER'S INFORMATION\033[0m-------------------*\n" << endl;
                cout << "1. Find \x1b[38;5;196mplayer's information by Name\033[0m" << endl;
                cout << "2. Find \x1b[38;5;196mplayer's information with the same level\033[0m" << endl;
                cout << "3. Display \x1b[38;5;196mLeaderboard\033[0m" << endl;
                cout << "4. Back to main menu\n" << endl;
                cout << "Press \x1b[38;5;27m<Number>\033[0m to choice: ";
                string choice;
                getline(cin,choice);
                if(!isValidChoice(choice))
                {
                    cout << "Invalid mode selected!" << endl;
                    cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
                    getchar();
                }
                else
                switch(stoi(choice))
                {
                case 1:
                {
                    system("cls");
                    string playerName;
                    cout << "Enter \x1b[38;5;196mplayer's name\033[0m you want to find: ";
                    getline(cin, playerName);
                    cout << "\nFound:\n" << endl;
                    game.findPlayer(playerName);
                    cout << "\nPress \x1b[38;5;136m<Enter>\033[0m to close this window..." << endl;
                    getchar();
                }
                    break;
                case 2:
                {
                    system("cls");
                    string playerName;
                    cout << "Enter \x1b[38;5;196mplayer's name\033[0m: ";
                    getline(cin, playerName);
                    cout << "\nFound:\n" << endl;
                    game.findPlayerSameLevel(playerName);
                    cout << "\nPress \x1b[38;5;136m<Enter>\033[0m to close this window..." << endl;
                    getchar();
                }
                    break;
                case 3:
                    system("cls");
                    cout << "*-------------------\x1b[38;5;27mLEADERBOARD\033[0m-------------------*\n" << endl;
                    game.displayPlayerInfo();
                    cout << "\nPress \x1b[38;5;136m<Enter>\033[0m to close this window..." << endl;
                    getchar();
                    break;
                case 4:
                    exitMenu = true;
                    break;
                default:
                    cout << "Invalid mode selected!" << endl;
                    cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
                    getchar();
                }
            }
            exitMenu = false;
            break;
        case 5:
            system("cls");
            game.instruction();
            cout << "\nPress \x1b[38;5;136m<Enter>\033[0m to close this window..." << endl;
            getchar();
            break;
        case 0:
            cout << "Exiting......." << endl;
            return 1;
        default:
            cin.ignore();
            cout << "Invalid mode selected!" << endl;
            cout << "Press \x1b[38;5;136m<Enter>\033[0m to type again!" << endl;
            getchar();
        }
    }
    return 0;
}
