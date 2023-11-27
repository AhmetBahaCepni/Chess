#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <string>

class Piece {
    public:
        Piece();
        Piece(char _type, bool color, int x, int y, double point); // x is letters and y is numbers (A1, B2, etc.)
        ~Piece();
        Piece(const Piece& other);
        Piece& operator=(const Piece& other);
        char getType();
        int getX();
        int getY();
        double getPoint();
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
};

#endif // PIECE_HPP