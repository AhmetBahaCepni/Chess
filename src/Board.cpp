#include "../libraries/Board.hpp"

int min(int n1, int n2)
{
    return (n1 > n2 ? n2 : n1);
}

int max(int n1, int n2)
{
    return (n1 > n2 ? n1 : n2);
}

Board::Board()
{
    std::vector<std::vector<Piece>> _board(8, std::vector<Piece>(8));
    std::vector<std::vector<bool>> _wThreads(8, std::vector<bool>(8));
    std::vector<std::vector<bool>> _bThreads(8, std::vector<bool>(8));
    std::vector<double> _points(2);

    _board[0][0] = Piece('R', 1, 0, 0, 5);
    _board[0][1] = Piece('N', 1, 1, 0, 3);
    _board[0][2] = Piece('B', 1, 2, 0, 3);
    _board[0][3] = Piece('Q', 1, 3, 0, 9);
    _board[0][4] = Piece('K', 1, 4, 0, 0);
    _board[0][5] = Piece('B', 1, 5, 0, 3);
    _board[0][6] = Piece('N', 1, 6, 0, 3);
    _board[0][7] = Piece('R', 1, 7, 0, 5);
    for (int i = 0; i < 8; i++)
    {
        _board[1][i] = Piece('P', 1, i, 1, 1);
    }

    _board[7][0] = Piece('r', 0, 0, 7, 5);
    _board[7][1] = Piece('n', 0, 1, 7, 3);
    _board[7][2] = Piece('b', 0, 2, 7, 3);
    _board[7][3] = Piece('q', 0, 3, 7, 9);
    _board[7][4] = Piece('k', 0, 4, 7, 0);
    _board[7][5] = Piece('b', 0, 5, 7, 3);
    _board[7][6] = Piece('n', 0, 6, 7, 3);
    _board[7][7] = Piece('r', 0, 7, 7, 5);
    for (int i = 0; i < 8; i++)
    {
        _board[6][i] = Piece('p', 0, i, 6, 1);
    }

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            _board[i][j] = Piece('.', 0, j, i, 0);
        }
    }


    this->turn = 1;
    this->gameOver = 0;
    this->check = -1;
    this->board = _board;
    this->wThreads = _wThreads;
    this->bThreads = _bThreads;
    this->points = _points;
}

Board::~Board()
{
    // std::cout << "Board destructor called" << std::endl;
}

Board::Board(Board &other)
{
    if (this != &other)
    {
        *this = other;
    }
}

Board &Board::operator=(Board &other) // this should be a deep copy
{
    if (this != &other)
    {
        std::vector <double> _points;
        points.push_back(other.points[0]);
        points.push_back(other.points[1]);
        this->board = copyBoard(other.board);
        this->wThreads = copyThreats(other.wThreads);
        this->bThreads = copyThreats(other.bThreads);

        this->points = _points;
        this->check = other.check;
        this->turn = other.turn;
        this->gameOver = other.gameOver;
    }

    return *this;
}

std::vector<std::vector<Piece>> Board::copyBoard(std::vector<std::vector<Piece>> &other)
{
    std::vector<std::vector<Piece>> _board(8, std::vector<Piece>(8));

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; i++)
        {
            _board[i][j] = other[i][j];
        }
    }
    return _board;
}

std::vector<std::vector<bool>> Board::copyThreats(std::vector<std::vector<bool>> &other)
{
    std::vector<std::vector<bool>> _threads(8, std::vector<bool>(8));

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; i++)
        {
            _threads[i][j] = other[i][j];
        }
    }
    return _threads;
}

std::ostream &operator<<(std::ostream &os, Board &board)
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "current points (W-B):  " << board.points[0] << " - " << board.points[1] << std::endl;

    std::cout << std::endl;
    for (int i = 7; i >= 0; i--)
    {
        std::cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++)
        {
            std::cout << board.board[i][j].getType() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "    - - - - - - - -" << std::endl;
    std::cout << "    ";
    for (int i = 0; i < 8; i++)
    {
        std::cout << (char)('a' + i) << " ";
    }
    std::cout << std::endl;

    return os;
}

// void Board::printBoard() {
//     std::cout << "---------------------------" << std::endl;
//     std::cout << "current points (W-B):  " << points[0] << " - " << points[1] << std::endl;

//     std::cout << std::endl;
//     for (int i = 7; i >= 0; i--) {
//         std::cout << i + 1 << " | ";
//         for (int j = 0; j < 8; j++) {
//             std::cout << this->board[i][j].getType() << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "    - - - - - - - -" << std::endl;
//     std::cout << "    ";
//     for (int i = 0; i < 8; i++) {
//         std::cout << (char)('a' + i) << " ";
//     }
//     std::cout << std::endl;
// }

std::string Board::takeInput()
{
    std::string input;

    while (1)
    {
        std::cout << "Turn is " << (whoTurn() ? "White" : "Black") << ". Enter your move: " << std::endl
                  << ">> ";
        std::cin >> input;
        if(input == "save")
        {
            saveGame();
            continue;
        }
        if(input == "suggest")
        {
            suggestMove(whoTurn());
            continue;
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
        break;
    case 114: // r
        if (start.getX() != end.getX() && start.getY() != end.getY())
            return false;
        if (!checkPath(Sx, Sy, Ex, Ey))
            return false;
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
    Piece &end = getPiece(Ex, Ey);

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

bool Board::isCheck(bool color)
{
    Piece &king = findKing(color);
    int x = king.getX();
    int y = king.getY();

    if(king.getUnderAttack())
        return true;
    else
        return false;
}

bool Board::isCheckMate(bool color)
{
    Piece &king = findKing(color);
    int x = king.getX();
    int y = king.getY();

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
                    std::string input = "";
                    input += (char)(piece.getX() + 'a');
                    input += (char)(piece.getY() + '1');
                    input += move;
                    movePiece(input);
                    updateBoard();
                    if (!isCheck(king.getColor()))
                    {
                        undoMove(input);
                        updateBoard();
                        return true;
                    }
                    undoMove(input);
                    updateBoard();
                }
            }
        }
    }

    return false;
}

// bool Board::checkAttackerPath(Piece &attacker, Piece &king) // piece is usually king
// {
//     int minX, maxX, minY, maxY;
//     bool color = king.getColor();
//     std::vector<std::vector<bool>> friendThreats = (color ? wThreads : bThreads);

//     if (king.getX() == attacker.getX())
//     {
//         std::cout << "same x checkCOntrol" << std::endl;
//         minY = min(king.getY(), attacker.getY());
//         maxY = max(king.getY(), attacker.getY());
//         for (int i = minY + 1; i < maxY; i++)
//         {
//             if (friendThreats[i][king.getX()])
//                 return true;
//         }
//     }
//     else if (king.getY() == attacker.getY())
//     {
//         std::cout << "same y checkCOntrol" << std::endl;
//         minX = min(king.getX(), attacker.getX());
//         maxX = max(king.getX(), attacker.getX());
//         for (int i = minX + 1; i < maxX; i++)
//         {
//             if (friendThreats[king.getY()][i])
//                 return true;
//         }
//     }
//     else if (abs(king.getX() - attacker.getX()) == abs(king.getY() - attacker.getY()))
//     {
//         std::cout << "diagonal checkCOntrol" << std::endl;
//         if ((king.getX() - attacker.getX() > 0 && king.getY() - attacker.getY() > 0) || (king.getX() - attacker.getX() < 0 && king.getY() - attacker.getY() < 0))
//         {
//             minX = min(king.getX(), attacker.getX());
//             minY = min(king.getY(), attacker.getY());
//             maxX = max(king.getX(), attacker.getX());
//             maxY = max(king.getY(), attacker.getY());

//             minX++;
//             minY++;
//             while (minX < maxX && minY < maxY)
//             {
//                 if (friendThreats[minY][minX])
//                     return true;
//                 minY++;
//                 minX++;
//             }
//         }
//         else
//         {
//             minX = min(king.getX(), attacker.getX());
//             minY = max(king.getY(), attacker.getY());
//             maxX = max(king.getX(), attacker.getX());
//             maxY = min(king.getY(), attacker.getY());

//             minX++;
//             minY--;
//             while (minX < maxX && minY > maxY)
//             {
//                 if (friendThreats[minY][minX])
//                     return true;
//                 minX++;
//                 minY--;
//             }
//         }
//     }
//     return false;
// }

// std::vector<Piece> Board::findAttackers(Piece &piece)
// {
//     std::vector<Piece> attackers;
//     std::vector<Piece> straightAttackers;
//     std::vector<Piece> diagonalAttackers;
//     int x = piece.getX();
//     int y = piece.getY();

//     straightAttackers = findStraightAttackers(piece);
//     diagonalAttackers = findDiagonalAttackers(piece);

//     for (auto &attacker : straightAttackers)
//     {
//         attackers.push_back(attacker);
//     }
//     for (auto &attacker : diagonalAttackers)
//     {
//         attackers.push_back(attacker);
//     }

//     if(attackers.size() == 0)
//         std::cout << "no attackers" << std::endl;
//     else
//         std::cout << "attackers found" << std::endl;

//     return attackers;
// }

// std::vector<Piece> Board::findStraightAttackers(Piece &piece)
// {
//     std::vector<Piece> attackers;
//     std::vector<std::vector<bool>> threats;
//     bool pColor = piece.getColor();
//     int x = piece.getX();
//     int y = piece.getY();


//     threats = (pColor ? bThreads : wThreads);

//     for (int i = x + 1; i < 8; i++)
//     {
//         if(threats[y][i])
//         {
//             if(isOpponent(i, y, pColor))
//                 attackers.push_back(getPiece(i, y));
//         }
//         else
//         {
//             if(isOpponent(i, y, pColor))
//                 attackers.push_back(getPiece(i, y));
//             break;
//         }
//     }
//     for (int i = x - 1; i >= 0; i--)
//     {
//         if(threats[y][i])
//         {
//             if(isOpponent(i, y, pColor))
//                 attackers.push_back(getPiece(i, y));
//         }
//         else
//         {
//             if(isOpponent(i, y, pColor))
//                 attackers.push_back(getPiece(i, y));
//             break;
//         }
//     }
//     for (int i = y + 1; i < 8; i++)
//     {
//         if(threats[i][x])
//         {
//             if(isOpponent(x, i, pColor))
//                 attackers.push_back(getPiece(x, i));
//         }
//         else
//         {
//             if(isOpponent(x, i, pColor))
//                 attackers.push_back(getPiece(x, i));
//             break;
//         }
//     }
//     for (int i = y - 1; i >= 0; i--)
//     {
//         if(threats[i][x])
//         {
//             if(isOpponent(x, i, pColor))
//                 attackers.push_back(getPiece(x, i));
//         }
//         else
//         {
//             if(isOpponent(x, i, pColor))
//                 attackers.push_back(getPiece(x, i));
//             break;
//         }
//     }

//     return attackers;
// }

// std::vector<Piece> Board::findDiagonalAttackers(Piece &piece)
// {
//     std::vector<Piece> attackers;
//     std::vector<std::vector<bool>> threats;
//     bool pColor = piece.getColor();
//     int x = piece.getX();
//     int y = piece.getY();

//     threats = (pColor ? bThreads : wThreads);

//     for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
//     {
//         if(threats[j][i])
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//         }
//         else
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//             break;
//         }
//     }
//     for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
//     {
//         if(threats[j][i])
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//         }
//         else
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//             break;
//         }
//     }
//     for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
//     {
//         if(threats[j][i])
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//         }
//         else
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//             break;
//         }
//     }
//     for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
//     {
//         if(threats[j][i])
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//         }
//         else
//         {
//             if(isOpponent(i, j, pColor))
//                 attackers.push_back(getPiece(i, j));
//             break;
//         }
//     }

//     return attackers;
// }

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
    points[0] = wPoints;
    points[1] = bPoints;
}

// File IO functions -------------------------------------------------------------------------------------------------------------

void Board::saveGame()
{
    std::ofstream file;
    file.open("save.txt");

    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            file << board[i][j].getType();
        }
        file << std::endl;
    }
    file << (whoTurn() ? "1" : "0") << std::endl;

    file.close();
}

void Board::loadGame()
{
    std::ifstream file;
    file.open("save.txt");
    if(!file.is_open())
    {
        std::cout << "no save file found" << std::endl;
        return;
    }

    std::vector<std::vector<Piece>> _board(8, std::vector<Piece>(8));
    std::vector<std::vector<bool>> _wThreads(8, std::vector<bool>(8));
    std::vector<std::vector<bool>> _bThreads(8, std::vector<bool>(8));
    std::vector<double> _points(2);

    std::string line;
    int i = 7;
    while (getline(file, line) && i >= 0)
    {
        std::cout << "line is " << line << std::endl;

        for (int j = 0; j < 8; j++)
        {
            if (line[j] != '.')
            {
                _board[i][j] = Piece(line[j], (line[j] < 97 ? 1 : 0), j, i, getPoint(line[j]));
            }
            else
            {
                _board[i][j] = Piece(line[j], 0, j, i, 0);
            }
        }
        i--;
    }

    this->turn = (line[0] == '1' ? 1 : 0);
    this->gameOver = 0;
    this->check = -1;
    this->board = _board;
    this->wThreads = _wThreads;
    this->bThreads = _bThreads;
    this->points = _points;

    file.close();
}

// AI functions -----------------------------------------------------------------------------------------------------------------

void Board::suggestMove(bool color)
{
    // std::vector<std::string> moves = findMoves(color);
    // std::vector<std::string> bestMoves;
    // double bestPoints = -1000;
    // double points;
    // std::string bestMove;

    // for (auto &move : moves)
    // {
    //     points = evaluateMove(move, color);
    //     if (points > bestPoints)
    //     {
    //         bestPoints = points;
    //         bestMove = move;
    //     }
    // }
    // for (auto &move : moves)
    // {
    //     points = evaluateMove(move, color);
    //     if (points == bestPoints)
    //     {
    //         bestMoves.push_back(move);
    //     }
    // }
    // srand(time(NULL));
    // int random = rand() % bestMoves.size();
    // std::cout << "best move is " << bestMoves[random] << std::endl;
}





// Setters and Getters -------------------------------------------------------------------------------------------------------------

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

bool Board::whoTurn()
{
    return this->turn;
}

bool Board::isGameOver()
{
    return this->gameOver;
}

void Board::setGameOver(bool state)
{
    this->gameOver = state;
}

void Board::setCheck(int state)
{
    this->check = state;
}

int Board::getCheck()
{
    return this->check;
}

void Board::nextTurn()
{
    this->turn = !this->turn;
}

bool Board::isPiece(int x, int y)
{
    return (this->board[y][x].getType() != '.');
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

bool Board::isBlack(int x, int y)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() == 0);
}

bool Board::isWhite(int x, int y)
{
    return (isPiece(x, y) && getPiece(x, y).getColor() == 1);
}

Piece &Board::getPiece(int x, int y)
{
    return this->board[y][x];
}

// DEBUGGING PURPOSES

void Board::printThreads(bool color)
{
    std::vector<std::vector<bool>> &threads = (color ? wThreads : bThreads);

    color ? std::cout << std::endl
                      << "White Threads:" << std::endl
          : std::cout << "Black Threads:" << std::endl;

    std::cout << std::endl;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << threads[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "    - - - - - - - -" << std::endl;
    std::cout << "    ";
    std::cout << std::endl;
}
