#include "../libraries/Piece.hpp"

Piece::Piece() {
    this->type = ' ';
    this->x = -1;
    this->y = -1;
    this->point = 0;
    this->color = 0;
    this->isUnderAttack = false;
    std::vector<std::string> moves;
}

Piece::Piece(char _type, bool color, int x, int y, double point) {
    this->type = _type;
    this->color = color;
    this->x = x;
    this->y = y;
    this->point = point;
    this->isUnderAttack = false;
    std::vector<std::string> moves;
}

Piece::~Piece() {
    // Nothing to do here
}

Piece::Piece(const Piece& other) {
    *this = other;
}

Piece& Piece::operator=(const Piece& other) {
    if (this != &other) {
        this->type = other.type;
        this->color = other.color;
        this->x = other.x;
        this->y = other.y;
        this->point = other.point;
        this->isUnderAttack = other.isUnderAttack;
        std::vector<std::string> _moves;
        for(auto move : other.moves)
            _moves.push_back(move);
        this->moves = _moves;
    }
    return *this;
}

void Piece::insertMove(int x, int y)
{
    std::string move = "";
    move += (char)(x + 'a');
    move += (char)(y + '1');
    moves.push_back(move);
}

void Piece::clearMoves()
{
    moves.clear();
}

std::vector<std::string> Piece::getMoves()
{
    return moves;
}

char Piece::getType() {
    return this->type;
}

bool Piece::getColor() {
    return this->color;
}

int Piece::getX() {
    return this->x;
}

int Piece::getY() {
    return this->y;
}

double Piece::getPoint() {
    return this->point;
}

bool Piece::getUnderAttack() {
    return this->isUnderAttack;
}

void Piece::setType(char type) {
    this->type = type;
}

void Piece::setUnderAttack(bool state) {
    this->isUnderAttack = state;
}

void Piece::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}

void Piece::setCoords(std::string coords) {
    this->x = coords[0] - 'A';
    this->y = coords[1] - '1';
}
