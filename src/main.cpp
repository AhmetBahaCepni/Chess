#include "../libraries/Board.hpp"


void gameLoop(Board& board)
{
    board.printBoard();
    while (!board.isGameOver())
    {
        board.printThreads(0); // Debugging purposes
        board.printThreads(1); // Debugging purposes

        std::string input = board.takeInput();
        while(board.isValidMove(input) == false)
        {
            std::cout << "Invalid move, try again" << std::endl;
            input = board.takeInput();
            board.printBoard();
        }
        board.movePiece(input);
        
        board.fillThreads();
        board.updatePieces();
        board.calculatePoints();
        board.printBoard();
        board.nextTurn();
    }
}

int main(void)
{
    Board board;

    gameLoop(board);
   
    return 0;
}