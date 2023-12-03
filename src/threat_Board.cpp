#include "../libraries/Board.hpp"

void Board::fillThreads()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            wThreads[i][j] = 0;
            bThreads[i][j] = 0;
        }
    }
    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() != '.')
            {
                piece.clearMoves();
                findAndFill(piece);
            }
        }
    }
}

void Board::fillThCell(int x, int y, bool color, Piece &p) // p here is attacker but x and y are the cell we are filling
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return;
    if (color)
        wThreads[y][x] = 1;
    else
        bThreads[y][x] = 1;
    
    if(p.getType() != '.')
    {
        if(p.getType() != 'p' && p.getType() != 'P' && !isFriend(x, y, p.getColor())) 
        {
            p.insertMove(x, y);
        }
        else if((p.getType() == 'p' ||  p.getType() == 'P') && isOpponent(x, y, p.getColor()))
        {
            p.insertMove(x, y);
        }
    }
    // if (!isFriend(x, y, color))
    // {
    //     if (color)
    //         wThreads[y][x] = 1;
    //     else
    //         bThreads[y][x] = 1;
    // }
}

void Board::rookThreads(Piece &p)
{
    for (int i = p.getX() + 1; i < 8; i++)
    {
        fillThCell(i, p.getY(), p.getColor(), p);
        if (isPiece(i, p.getY()))
            break;
    }
    for (int i = p.getX() - 1; i >= 0; i--)
    {
        fillThCell(i, p.getY(), p.getColor(), p);
        if (isPiece(i, p.getY()))
            break;
    }
    for (int i = p.getY() + 1; i < 8; i++)
    {
        fillThCell(p.getX(), i, p.getColor(), p);
        if (isPiece(p.getX(), i))
            break;
    }
    for (int i = p.getY() - 1; i >= 0; i--)
    {
        fillThCell(p.getX(), i, p.getColor(), p);
        if (isPiece(p.getX(), i))
            break;
    }
}

void Board::bishopThreads(Piece &p)
{
    for (int i = p.getX() + 1, j = p.getY() + 1; i < 8 && j < 8; i++, j++)
    {
        fillThCell(i, j, p.getColor(), p);
        if (isPiece(i, j))
            break;
    }
    for (int i = p.getX() - 1, j = p.getY() + 1; i >= 0 && j < 8; i--, j++)
    {
        fillThCell(i, j, p.getColor(), p);
        if (isPiece(i, j))
            break;
    }
    for (int i = p.getX() + 1, j = p.getY() - 1; i < 8 && j >= 0; i++, j--)
    {
        fillThCell(i, j, p.getColor(), p);
        if (isPiece(i, j))
            break;
    }
    for (int i = p.getX() - 1, j = p.getY() - 1; i >= 0 && j >= 0; i--, j--)
    {
        fillThCell(i, j, p.getColor(), p);
        if (isPiece(i, j))
            break;
    }
}

void Board::findAndFill(Piece &p)
{
    int type = p.getType();
    if (type != 'P')
        type = tolower(type);

    switch (type)
    {
    case 80: // P
        fillThCell(p.getX() + 1, p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() + 1, p.getColor(), p);
        if(!isPiece(p.getX(), p.getY() + 1))
        {
            p.insertMove(p.getX(), p.getY() + 1);
            if(p.getY() == 1 && !isPiece(p.getX(), p.getY() + 2))
                p.insertMove(p.getX(), p.getY() + 2);
        }
        break;
    case 112: // p
        fillThCell(p.getX() + 1, p.getY() - 1, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() - 1, p.getColor(), p);
        if(!isPiece(p.getX(), p.getY() - 1))
        {
            p.insertMove(p.getX(), p.getY() - 1);
            if(p.getY() == 6 && !isPiece(p.getX(), p.getY() - 2))
                p.insertMove(p.getX(), p.getY() - 2);
        }
        break;

        break;
    case 114: // r
        rookThreads(p);
        break;
    case 98: // b
        bishopThreads(p);
        break;
    case 113: // q
        rookThreads(p);
        bishopThreads(p);
        break;
    case 107: // k
        fillThCell(p.getX() + 1, p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX() + 1, p.getY() - 1, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() - 1, p.getColor(), p);
        fillThCell(p.getX() + 1, p.getY(), p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY(), p.getColor(), p);
        fillThCell(p.getX(), p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX(), p.getY() - 1, p.getColor(), p);
        break;
    case 110: // n
        fillThCell(p.getX() + 2, p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX() + 2, p.getY() - 1, p.getColor(), p);
        fillThCell(p.getX() - 2, p.getY() + 1, p.getColor(), p);
        fillThCell(p.getX() - 2, p.getY() - 1, p.getColor(), p);
        fillThCell(p.getX() + 1, p.getY() + 2, p.getColor(), p);
        fillThCell(p.getX() + 1, p.getY() - 2, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() + 2, p.getColor(), p);
        fillThCell(p.getX() - 1, p.getY() - 2, p.getColor(), p);
        break;
    default:
        std::cout << "!!!!!!!!!! This should not happen !!!!!!!!!!" << std::endl;
        std::cout << type << std::endl;
        break;
    }
}