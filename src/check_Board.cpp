#include "../libraries/Board.hpp"

bool Board::isSafe(int x, int y, bool color)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) // if out of bounds
        return false;
    if(color)
    {
        if(bThreads[y][x])
            return false;
    }
    else
    {
        if(wThreads[y][x])
            return false;
    }   
    return true;
}

bool Board::isCheck(bool color)
{
    Piece &king = findKing(color);

    if(king.getUnderAttack())
        return true;
    else
        return false;
}

bool Board::isCheckMate(bool color)
{
    Piece &king = findKing(color);

    if (kingHasMoves(king))
        return false;
    if (kingCanBeSaved(king))
        return false;

    return true;
}

bool Board::kingHasMoves(Piece &king)
{
    int x = king.getX();
    int y = king.getY();

    if (kingCanGo(x + 1, y + 1, king.getColor()))
        return true;
    if (kingCanGo(x + 1, y, king.getColor()))
        return true;
    if (kingCanGo(x, y + 1, king.getColor()))
        return true;
    if (kingCanGo(x, y - 1, king.getColor()))
        return true;
    if (kingCanGo(x - 1, y + 1, king.getColor()))
        return true;
    if (kingCanGo(x - 1, y, king.getColor()))
        return true;
    if (kingCanGo(x - 1, y - 1, king.getColor()))
        return true;
    if (kingCanGo(x + 1, y - 1, king.getColor()))
        return true;

    return false;
}

bool Board::kingCanGo(int x, int y, bool color)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) // if out of bounds
        return false;
    if (!isFriend(x, y, color) && isSafe(x, y, color))
        return true;
    
    return false;
}

bool Board::kingCanBeSaved(Piece &king)
{
    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() != 'k' && piece.getType() == 'K' && isFriend(piece.getX(), piece.getY(), king.getColor()))
            {
                for (auto &move : piece.getMoves())
                {
                    movePiece(move);
                    updateBoard();
                    if (!isCheck(king.getColor()))
                    {
                        undoMove(move);
                        updateBoard();
                        return true;
                    }
                    undoMove(move);
                    updateBoard();
                }
            }
        }
    }

    return false;
}

Piece &Board::findKing(bool color)
{
    char king = (color ? 'K' : 'k');
    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() == king && piece.getColor() == color)
                return piece;
        }
    }
    std::cout << "!!!!!!!!!! This should not happen 5!!!!!!!!!!" << std::endl;
    return board[0][0];
}
