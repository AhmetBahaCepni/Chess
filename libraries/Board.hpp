#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <string>

class Board{
    public:
        Board();
        ~Board();
        Board(const Board& other);
        Board& operator=(const Board& other);

        void printBoard();
        std::string takeInput();
        
        Piece& getPiece(int x, int y);
        void swapPieces(int Sx, int Sy, int Ex, int Ey);
        void hitPiece(int Sx, int Sy, int Ex, int Ey);
        bool pieceChecks(int Sx, int Sy, int Ex, int Ey);

        void movePiece(std::string input);
        void nextTurn();

        void fillThreads();
        void updatePieces();
        void findAndFill(Piece &p);
        void fillThCell(int x, int y, bool color);
        void rookThreads(Piece &p);
        void bishopThreads(Piece &p);
        void printThreads(bool color);

        void calculatePoints();

        bool checkPath(int Sx, int Sy, int Ex, int Ey);
        bool whoTurn();
        bool isGameOver();
        bool isValidMove(std::string input);
        bool isPiece(int x, int y);
        bool isOpponent(int x, int y);
        bool isFriend(int x, int y);
        bool isFriend(int x, int y, bool color);
        bool isBlack(int x, int y);
        bool isWhite(int x, int y);
    private:
        std::vector< std::vector<Piece> > board;
        std::vector< std::vector<bool> > wThreads;
        std::vector< std::vector<bool> > bThreads;
        std::vector< double > points;
        std::vector<Piece> whiteP;
        std::vector<Piece> blackP;
        bool turn;
        bool gameOver;
};

#endif