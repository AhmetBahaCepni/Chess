#include "../libraries/Board.hpp"

void gameLoop(Board& board)
{
    #include <iostream> // Add missing import

    std::cout << "Welcome to Chess!" << std::endl;
    std::cout << board << std::endl;
    while (!board.isGameOver())
    {
        board.printThreads(0); // Debugging purposes
        board.printThreads(1); // Debugging purposes

        std::string input = board.takeInput();
        while(board.isValidMove(input) == false)
        {
            std::cout << "Invalid move, try again" << std::endl;
            input = board.takeInput();
            std::cout << board << std::endl;
        }
        board.movePiece(input);
        
        board.fillThreads();
        board.updatePieces();
        board.calculatePoints();

        board.isCheck();

        std::cout << board << std::endl;
        board.nextTurn();
    }
}

int main(void)
{
    Board board;

    gameLoop(board);
   
    return 0;
}