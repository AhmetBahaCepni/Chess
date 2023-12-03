#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Board{
    public:
        // Constructors and Destructors and Operators
        Board();
        ~Board();
        Board(const Board& other);
        Board& operator=(const Board& other);
        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        // void printBoard(); overloading operator<< already does this
        
        // Fundamental functions
        std::string takeInput(); 
        std::vector<std::vector<Piece>> copyBoard(const std::vector<std::vector<Piece>> &other) const;
        std::vector<std::vector<bool>> copyThreats(const std::vector<std::vector<bool>> &other) const;
        void updateBoard();
        
        // Validate and Check functions

        bool isValidMove(std::string input);
        bool checkPath(int Sx, int Sy, int Ex, int Ey) const;
        bool pieceChecks(int Sx, int Sy, int Ex, int Ey);
        
        // Action functions
        void swapPieces(int Sx, int Sy, int Ex, int Ey);
        void hitPiece(int Sx, int Sy, int Ex, int Ey);
        void movePiece(std::string input);
        void undoMove(std::string input);

        // Threat functions
        void fillThreads();
        void updatePieces();
        void findAndFill(Piece &p);
        void fillThCell(int x, int y, bool color, Piece &p);
        void rookThreads(Piece &p);
        void bishopThreads(Piece &p);
        bool isSafe(int x, int y, bool color) const;

        // Checkmate functions
        bool isCheck(bool color);
        bool isCheckMate(bool color);
        Piece& findKing(bool color);
        bool kingHasMoves(const Piece &king);
        bool kingCanGo(int x, int y, bool color);
        bool kingCanBeSaved(const Piece &king);
        

        // Point functions
        void calculatePoints();

        // Suggest AI functions
        void suggestMove(bool color);
        std::vector<std::string> getPossibleMoves(bool color);
        // special functions
        char promotePawn();
        void castle(bool color, bool side);

        // file functions
        void saveGame() const;
        void loadGame();

        // Helper functions
        Piece& getPiece(int x, int y);
        int getPoint(char type) const;
        bool isOpponent(int x, int y);
        bool isOpponent(int x, int y, bool color);
        bool isFriend(int x, int y);
        bool isFriend(int x, int y, bool color);

        // Inline functions
        int min(int a, int b) const { return (a < b) ? a : b; }
        int max(int a, int b) const { return (a > b) ? a : b; }
        void nextTurn() { turn = !turn; }
        bool whoTurn() const { return turn; }
        bool isGameOver() const { return gameOver; }
        void setGameOver(bool state) { gameOver = state; }
        void setCheck(int state) { check = state; }
        int getCheck() const { return check; }
        bool isPiece(int x, int y) const { return board[y][x].getType() != '.'; }

    private:
        std::vector< std::vector<Piece> > board;
        std::vector< std::vector<bool> > wThreads;
        std::vector< std::vector<bool> > bThreads;
        std::vector< double > points;
        std::vector<bool> castlingVariables;
        int check; // -1 for no check, 0 for black, 1 for white
        bool turn;
        bool gameOver;
};

#endif