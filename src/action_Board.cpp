#include "../libraries/Board.hpp"


std::string Board::takeInput()
{
    std::string input;

    while (1)
    {
        std::cout << "Turn is " << (whoTurn() ? "White" : "Black") << ". Enter your move: " << std::endl
                  << ">> ";
        std::cin >> input;
        if (input == "exit")
        {
            saveGame();
            std::cout << "Game saved" << std::endl;
            std::cout << "Exiting..." << std::endl;
            exit(0);
        }
        if(input == "save")
        {
            saveGame();
            std::cout << "Game saved" << std::endl;
            continue;
        }
        if(input == "suggest")
        {
            std::cout << "Suggested move is:  ";
            suggestMove(whoTurn());
            continue;
        }
        if(input == "O-O") // this is O not zero
        {
            castle(whoTurn(), 1);
            return "special";
        }
        if(input == "O-O-O") // this is O not zero
        {
            castle(whoTurn(), 0);
            return "special";
        }
        if (input.length() == 4 && (input[0] >= 'a' && input[0] <= 'h' && input[1] >= '1' && input[1] <= '8' && input[2] >= 'a' && input[2] <= 'h' && input[3] >= '1' && input[3] <= '8'))
        {
            break;
        }
        else
        {
            std::cout << std::endl
                      << "- Invalid input. valid move examples are a1a3, b7c5, etc." << std::endl;
        }
    }
    return input;
}

bool Board::isValidMove(std::string input)
{
    int startX = input[0] - 'a';
    int startY = input[1] - '1';
    int endX = input[2] - 'a';
    int endY = input[3] - '1';

    if (!isPiece(startX, startY) ||
        (getPiece(startX, startY).getColor() != whoTurn()) ||
        isFriend(endX, endY))
    {
        return false;
    }
    if (!pieceChecks(startX, startY, endX, endY))
    {
        return false;
    }
    return true;
}

bool Board::pieceChecks(int Sx, int Sy, int Ex, int Ey)
{
    Piece &start = getPiece(Sx, Sy);
    Piece &end = getPiece(Ex, Ey);

    int type = start.getType();
    if (type != 'P')
        type = tolower(type);

    switch (type)
    {
    case 80: // P
        if (start.getX() == end.getX())
        {
            if (start.getY() == 1)
            {
                if (end.getY() - start.getY() > 2 || end.getY() - start.getY() < 1)
                    return false;
                if (!checkPath(Sx, Sy, Ex, Ey))
                    return false;
            }
            else
            {
                if (end.getY() - start.getY() != 1)
                    return false;
            }
            if (isPiece(Ex, Ey))
                return false;
        }
        else if (end.getY() - start.getY() == 1 && abs(start.getX() - end.getX()) == 1)
        {
            if (!isOpponent(Ex, Ey))
                return false;
        }
        else
            return false;
        if (end.getY() == 7)
            start.setType(promotePawn());
        break;
    case 112: // p
        if (start.getX() == end.getX())
        {
            if (start.getY() == 6)
            {
                if (start.getY() - end.getY() > 2 || start.getY() - end.getY() < 1)
                    return false;
                if (!checkPath(Sx, Sy, Ex, Ey))
                    return false;
            }
            else
            {
                if (start.getY() - end.getY() != 1)
                    return false;
            }
            if (isPiece(Ex, Ey))
                return false;
        }
        else if (start.getY() - end.getY() == 1 && abs(start.getX() - end.getX()) == 1)
        {
            if (!isOpponent(Ex, Ey))
                return false;
        }
        else
            return false;
        if (end.getY() == 0)
            start.setType(promotePawn());
        break;
    case 114: // r
        if (start.getX() != end.getX() && start.getY() != end.getY())
            return false;
        if (!checkPath(Sx, Sy, Ex, Ey))
            return false;
        start.getColor() ? castlingVariables[1] = true : castlingVariables[3] = true;
        break;
    case 98: // b
        if (abs(start.getX() - end.getX()) != abs(start.getY() - end.getY()))
            return false;
        if (!checkPath(Sx, Sy, Ex, Ey))
            return false;
        break;
    case 113: // q
        if (start.getX() != end.getX() && start.getY() != end.getY())
        {
            if (abs(start.getX() - end.getX()) != abs(start.getY() - end.getY()))
                return false;
        }
        if (!checkPath(Sx, Sy, Ex, Ey))
            return false;
        break;
    case 107: // k
        if (abs(start.getX() - end.getX()) > 1 || abs(start.getY() - end.getY()) > 1)
            return false;
        start.getColor() ? castlingVariables[0] = true : castlingVariables[2] = true;
        break;
    case 110: // n
        if (abs(start.getX() - end.getX()) == 2 && abs(start.getY() - end.getY()) == 1)
            return true;
        if (abs(start.getX() - end.getX()) == 1 && abs(start.getY() - end.getY()) == 2)
            return true;
        return false;
        break;
    default:
        std::cout << type << std::endl;
        break;
    }
    return true;
}

bool Board::checkPath(int Sx, int Sy, int Ex, int Ey)
{
    int minX, maxX, minY, maxY;

    if (Sx == Ex)
    {
        minY = min(Sy, Ey);
        maxY = max(Sy, Ey);
        for (int i = minY + 1; i < maxY; i++)
        {
            if (isPiece(Sx, i))
                return false;
        }
    }
    else if (Sy == Ey)
    {
        minX = min(Sx, Ex);
        maxX = max(Sx, Ex);
        for (int i = minX + 1; i < maxX; i++)
        {
            if (isPiece(i, Sy))
                return false;
        }
    }
    else if (abs(Sx - Ex) == abs(Sy - Ey))
    {
        if ((Sx - Ex > 0 && Sy - Ey > 0) || (Sx - Ex < 0 && Sy - Ey < 0))
        {
            std::cout << "diagonal 1" << std::endl;
            minX = min(Sx, Ex);
            minY = min(Sy, Ey);
            maxX = max(Sx, Ex);
            maxY = max(Sy, Ey);

            minX++;
            minY++;
            while (minX < maxX && minY < maxY)
            {
                std::cout << minX << " " << minY << std::endl;
                if (isPiece(minX, minY))
                    return false;
                minY++;
                minX++;
            }
        }
        else
        {
            std::cout << "diagonal 2" << std::endl;
            minX = min(Sx, Ex);
            minY = max(Sy, Ey);
            maxX = max(Sx, Ex);
            maxY = min(Sy, Ey);

            minX++;
            minY--;
            while (minX < maxX && minY > maxY)
            {
                std::cout << minX << " " << minY << std::endl;
                if (isPiece(minX, minY))
                    return false;
                minX++;
                minY--;
            }
        }
    }
    return true;
}
// we can see all ports and ssh port with shell command

void Board::movePiece(std::string input)
{
    int startX = input[0] - 'a';
    int startY = input[1] - '1';
    int endX = input[2] - 'a';
    int endY = input[3] - '1';

    if (isOpponent(endX, endY))
    {
        hitPiece(startX, startY, endX, endY);
    }
    else
    {
        swapPieces(startX, startY, endX, endY);
    }
    updateBoard();
}

void Board::undoMove(std::string input)
{
    int startX = input[0] - 'a';
    int startY = input[1] - '1';
    int endX = input[2] - 'a';
    int endY = input[3] - '1';

    swapPieces(startX, startY, endX, endY);
    updateBoard();
}

void Board::hitPiece(int Sx, int Sy, int Ex, int Ey)
{
    Piece &start = getPiece(Sx, Sy);

    start.setCoords(Ex, Ey);
    board[Ey][Ex] = start;
    board[Sy][Sx] = Piece('.', 0, Sx, Sy, 0);
}

void Board::swapPieces(int Sx, int Sy, int Ex, int Ey)
{
    Piece start = getPiece(Sx, Sy);
    Piece end = getPiece(Ex, Ey);

    start.setCoords(Ex, Ey);
    end.setCoords(Sx, Sy);
    board[Ey][Ex] = start;
    board[Sy][Sx] = end;
}


void Board::updatePieces()
{
    std::ofstream moveFile;
    moveFile.open("move.txt");
    moveFile.clear(); // to 

    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() != '.')
            {
                bool color = piece.getColor();

                if (!color && wThreads[piece.getY()][piece.getX()])
                {
                    piece.setUnderAttack(true);
                }
                else if (color && bThreads[piece.getY()][piece.getX()])
                {
                    piece.setUnderAttack(true);
                }
                else
                {
                    piece.setUnderAttack(false);
                }

                // how to open a file in append mode 

                for(std::string move : piece.getMoves())
                {
                    moveFile << piece.getType() << " " << piece.getX() << piece.getY() << "--> " << move << std::endl;
                }
            }
        }
    }
    moveFile.close();
}

void Board::updateBoard()
{
    fillThreads();
    updatePieces();
    calculatePoints();
}