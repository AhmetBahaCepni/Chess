#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <string>

class Piece {
    public:
        // Constructors and Destructors and Operators
        Piece();
        Piece(char _type, bool color, int x, int y, double point); // x is letters and y is numbers (A1, B2, etc.)
        ~Piece();
        Piece(const Piece& other);
        Piece& operator=(const Piece& other);

        // Getters and Setters
        char getType();
        int getX();
        int getY();

        // Other functions
        void insertMove(int x, int y);
        void clearMoves();
        
        // Fundamental functions
        double getPoint();
        std::vector<std::string> getMoves();
        bool getColor();
        bool getUnderAttack();
        void setType(char type);
        void setUnderAttack(bool isUnderAttack);
        void setCoords(int x, int y);
        void setCoords(std::string coords);
    private:
        char type;
        int x;
        int y;
        double point;
        bool color; // 0 for black, 1 for white
        bool isUnderAttack;
        std::vector<std::string> moves;
};

#endif // PIECE_HPP