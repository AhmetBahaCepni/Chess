#include "../libraries/Board.hpp"

bool gameLoop(Board& board)
{
    #include <iostream> // Add missing import

    std::cout << "Welcome to Chess!" << std::endl;
    std::cout << board << std::endl;
    while (!board.isGameOver())
    {
        std::string input = board.takeInput();
        while(board.isValidMove(input) == false)
        {
            std::cout << "Invalid move, try again" << std::endl;
            input = board.takeInput();
            std::cout << board << std::endl;
        }

        board.movePiece(input);
        if(board.isCheck(board.whoTurn()))
        {
            if(board.getCheck() == -1)
                std::cout << "You can not open your kign to check!" << std::endl;
            else
                std::cout << "You should sace your king from check" << std::endl;
            board.undoMove(input);
            
            board.printThreads(0); // Debugging purposes
            board.printThreads(1); // Debugging purposes
        
            continue;
        }

        board.printThreads(0); // Debugging purposes
        board.printThreads(1); // Debugging purposes
        
        std::cout << board << std::endl;

        if(board.isCheck(!board.whoTurn()))
        {
            if(board.isCheckMate(!board.whoTurn()))
            {
                std::cout << "Checkmate!" << std::endl;
                board.setGameOver(true);
                return board.whoTurn();
            }
            else
            {
                std::cout << (!board.whoTurn() ? "White" : "Black") << " is in check!" << std::endl;
                board.setCheck(!board.whoTurn());
            }
        }

        board.nextTurn();
        board.saveGame();
    }
    return false;
}

void fileOperations(Board& board)
{
    std::ifstream saveFile("save.txt");
    //if save.txt is not empty, ask if the user wants to load the game or start a new one
    if(saveFile.peek() != std::ifstream::traits_type::eof())
    {
        std::cout << "Do you want to load the game? (y/n)" << std::endl << ">> ";
        char answer;
        std::cin >> answer;
        if(answer == 'y')
        {
            board.loadGame();
        }
    }
}

void winnerMessage(bool winner)
{
    if(winner)
    {
        std::cout << "White wins!" << std::endl;
    }
    else
    {
        std::cout << "Black wins!" << std::endl;
    }
}

int main(void)
{
    Board board;
    bool winner;

    fileOperations(board);
    winner = gameLoop(board);
    winnerMessage(winner);

    return 0;
}