# CARO Console Game: A Comprehensive Overview

### Video Demo:  
For a visual walkthrough of the game, please visit [this YouTube link](https://youtu.be/hX1enp7Ic1s?si=FplvK3njwDcLQUat).

---

### **Introduction**
This project is a console-based **Caro Game**, developed as the final project for CS50. Caro, a traditional game with roots in the Tic-Tac-Toe genre, is enhanced in this version with competitive and strategic modes. Players can either challenge their friends or go head-to-head with an AI bot that offers varying levels of difficulty.

Built using **C++** and employing Object-Oriented Programming (OOP), the game is structured to ensure modularity and scalability. Its functionalities, such as detailed player tracking, dynamic board updates, and replay features, make it a robust platform for practicing strategic thinking.

---

### **Setup Instructions**
The game requires **MinGW** for building C++ files. Once installed, follow these steps to compile and play the game:

1. Open the terminal (Windows).
2. Navigate to the game directory.
3. Compile the game using:
   ```bash
   g++ game.cpp main.cpp players.cpp -o caro-game
   ```
4. Run the game:
   ```bash
   caro-game.exe
   ```

Once launched, you'll see a menu offering multiple modes and features. Select the corresponding numbers to explore the game modes or access instructions.

---

### **Game Features**
#### **1. Game Modes**
- **Player vs. Player:** A classic mode where two human players take turns.
- **Player vs. Bot:** Play against a bot with adjustable difficulty levels:
  - **Easy:** A more relaxed gameplay experience.
  - **Hard:** A strategically challenging mode where the bot predicts your moves.

#### **2. Replay System**
Players can replay a match to review their moves, analyze strategies, or relive the excitement.

#### **3. Dynamic Board**
The board size can be adjusted, offering a customized experience for each game.

#### **4. Player Statistics**
- The game maintains win/loss/draw records for each player.
- Stats are persistent and saved across sessions.

#### **5. Smart AI**
The bot employs an algorithm to analyze the board and determine the best move. This feature ensures that the bot becomes a competitive opponent, especially at higher difficulty levels.

#### **6. Detailed Instructions**
Players can access a comprehensive guide on gameplay, controls, and strategies.

---

### **Design Overview**
The game leverages **OOP principles** for better organization and maintainability. The project is divided into three key components:  
1. **`players.h`:** Handles player data and bot logic.  
2. **`game.h`:** Manages the game board, moves, and rules.  
3. **`main.cpp`:** Integrates the above components and facilitates user interaction.

#### **1. Players Class (`players.h`)**
- **Attributes:**
  - `m_name`: Stores the player's name.
  - `m_win`, `m_lose`, `m_draw`: Tracks the player's performance.
  - `m_is_bot`: Indicates if the player is an AI bot.
  - `m_check_points_bot`: Helps the bot analyze potential moves.
  
- **Key Methods:**
  - **`findBestMove`:** Implements the bot's strategy using algorithms based on board state and difficulty.
  - **`setWinSameName` / `setLoseSameName` / `setDrawSameName`:** Updates player stats across multiple sessions.

#### **2. Game Class (`game.h`)**
- **Attributes:**
  - `m_board`: A 2D vector representing the game board.
  - `m_size`: Defines the board dimensions.
  - `m_currentPlayer`: Tracks the current turn.
  - `m_players`: Stores player data.
  
- **Key Methods:**
  - **`printBoard`:** Displays the current game state.
  - **`makeMove`:** Validates and processes player moves.
  - **`checkWin`:** Checks for winning patterns on the board.
  - **`playerVsBot`:** Implements the logic for player-bot matches.
  - **`replayMoves`:** Replays the sequence of moves from the game.

#### **3. Main Integration (`main.cpp`)**
This file ties together the `Players` and `Game` classes. It handles:
- Loading and saving player data.
- Displaying menus and processing user inputs.
- Transitioning between modes.

---

### **Game Logic**
#### **Player vs. Player**
1. Two players alternate turns, marking their moves on the board.
2. After every move, the game checks for a winner or a draw.
3. Statistics are updated and saved upon game completion.

#### **Player vs. Bot**
1. The player starts and makes their move.
2. The bot calculates its best move using the `findBestMove` method.
3. The process continues until a winner is declared or the game ends in a draw.

#### **Winning Conditions**
A player wins if they align 5 consecutive markers (horizontally, vertically, or diagonally).

---

### **Technical Highlights**
#### **Bot Algorithm**
The bot evaluates the board based on:
- **Immediate Threats:** Blocks the player from winning.
- **Opportunities:** Prioritizes moves that lead to a win.
- **Difficulty Levels:** Adjusts its depth of analysis based on the selected difficulty.

#### **Replay Feature**
- Stores all moves in a vector.
- Allows step-by-step playback to analyze gameplay.

#### **Persistence**
- Player data, including win/loss/draw records, is saved in a file for continuity.

---

### **Future Enhancements**
- **Online Multiplayer:** Allow remote matches using network connectivity.
- **Improved AI:** Implement machine learning techniques for a more adaptive bot.
- **Graphical Interface:** Transition from console to GUI for enhanced user experience.

---

### **Conclusion**
This Caro Console Game is more than a simple implementation of Tic-Tac-Toe. With features like smart AI, replay capabilities, and detailed player statistics, it delivers a comprehensive and engaging gameplay experience. Built using C++, it serves as an excellent example of applying OOP principles to game development. Whether you're playing with friends or challenging the bot, the game ensures hours of strategic fun!