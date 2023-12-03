#include "../libraries/Board.hpp"

bool gameLoop(Board& board)
{
    std::cout << board << std::endl;
    board.updateBoard();
    while (!board.isGameOver())
    {
        std::string input = board.takeInput();
        if(input == "special")
        {
            board.updateBoard();
            board.nextTurn();
            std::cout << board << std::endl;
            continue;
        }
        std::cout << input << std::endl;
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
            continue;
        }
        
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
    std::ifstream saveFile("log/save.txt");
    //if save.txt is not empty, ask if the user wants to load the game or start a new one
    if(saveFile.peek() != std::ifstream::traits_type::eof())
    {
        std::cout << "Loading game..." << std::endl;
        board.loadGame();
        std::cout << board.whoTurn() << std::endl;
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
    int choice;
    std::cout << "Welcome to Chess!" << std::endl;
    while(true)
    {
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Help" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> choice;
        if(choice == 1)
        {
            break;
        }
        else if(choice == 2)
        {
            fileOperations(board);
            break;
        }
        else if(choice == 3)
        {
            std::cout << "This is a simple Chess game." << std::endl;
            std::cout << "Why do you need help dont you know how to play chess?" << std::endl;
            std::cout << "Just kidding, example moves are a1a3, b7c5, etc." << std::endl;
            std::cout << "You can save the game by typing save." << std::endl;
            std::cout << "You can get a move hint by typing suggest." << std::endl;
            std::cout << "You can castle by typing O-O for short castle and O-O-O for long castle." << std::endl;
            std::cout << "You can exit the game by typing exit." << std::endl << std::endl;
            continue;
        }
        else if(choice == 4)
        {
            std::cout << "Goodbye!" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Invalid choice, try again" << std::endl;
        }
    }
    winner = gameLoop(board);
    winnerMessage(winner);

    return 0;
}