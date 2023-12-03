#include "../libraries/Board.hpp"

char Board::promotePawn()
{
    char choice;
    std::cout << "Choose a piece to promote your pawn to: ";
    std::cin >> choice;
    while (choice != 'Q' && choice != 'R' && choice != 'B' && choice != 'N')
    {
        std::cout << "Invalid choice, try again: ";
        std::cin >> choice;
    }
    return choice;
}

void Board::castle(bool color, bool side)
{
    if(color)
    {
        if(castlingVariables[0] || castlingVariables[1] || isCheck(color))
        {
            std::cout << "You can't castle" << std::endl;
            return;
        }
        if(side && checkPath(4, 0, 7, 0))
        {
            hitPiece(4, 0, 6, 0);
            hitPiece(7, 0, 5, 0);
        }
        else if(!side && checkPath(4, 0, 0, 0))
        {
            hitPiece(4, 0, 2, 0);
            hitPiece(0, 0, 3, 0);
        }
        else
        {
            std::cout << "You can't castle" << std::endl;
            return;
        }
    }
    else
    {
        if(castlingVariables[2] || castlingVariables[3] || isCheck(color))
        {
            std::cout << "You can't castle" << std::endl;
            return;
        }
        if(side && checkPath(4, 7, 7, 7))
        {

            hitPiece(4, 7, 6, 7);
            hitPiece(7, 7, 5, 7);
        }
        else if(!side && checkPath(4, 7, 0, 7))
        {
            hitPiece(4, 7, 2, 7);
            hitPiece(0, 7, 3, 7);
        }
        else
        {
            std::cout << "You can't castle" << std::endl;
            return;
        }
    }
}