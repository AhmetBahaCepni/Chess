#include "../libraries/Board.hpp"


void gameLoop(Board& board)
{
    while (!board.isGameOver())
    {
        board.printBoard();
        std::string input = board.takeInput();
        while(board.isValidMove(input) == false)
        {
            std::cout << "Invalid move, try again" << std::endl;
            input = board.takeInput();
            board.printBoard();
        }
        board.movePiece(input);
        
        board.nextTurn();
    }
}

int main(void)
{
    Board board;

    gameLoop(board);
   
    return 0;
}