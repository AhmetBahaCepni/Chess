#include "../libraries/Board.hpp"

void Board::calculatePoints()
{
    double wPoints = 0;
    double bPoints = 0;

    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() != '.')
            {
                if (piece.getColor())
                    wPoints += piece.getUnderAttack() ? piece.getPoint() / 2 : piece.getPoint();
                else
                    bPoints += piece.getUnderAttack() ? piece.getPoint() / 2 : piece.getPoint();
            }
        }
    }
    points[0] = bPoints;
    points[1] = wPoints;
}

int Board::getPoint(char type)
{
    switch (type)
    {
    case 'P':
    case 'p':
        return 1;
        break;
    case 'R':
    case 'r':
        return 5;
        break;
    case 'B':
    case 'b':
        return 3;
        break;
    case 'Q':
    case 'q':
        return 9;
        break;
    case 'K':
    case 'k':
        return 0;
        break;
    case 'N':
    case 'n':
        return 3;
        break;
    default:
        return 0;
        break;
    }
}

bool Board::isOpponent(int x, int y)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() != whoTurn());
}

bool Board::isOpponent(int x, int y, bool color)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() != color);
}

bool Board::isFriend(int x, int y)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() == whoTurn());
}

bool Board::isFriend(int x, int y, bool color)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() == color);
}

Piece &Board::getPiece(int x, int y)
{
    return this->board[y][x];
}