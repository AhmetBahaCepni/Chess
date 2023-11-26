#include "../libraries/Board.hpp"

Board::Board() {
    std::vector< std::vector<Piece> > board(8, std::vector<Piece>(8));
    std::vector<Piece> whiteP;
    std::vector<Piece> blackP;

    board[0][0] = Piece('R', 1, 0, 0, 5);
    board[0][1] = Piece('N', 1, 1, 0, 3);
    board[0][2] = Piece('B', 1, 2, 0, 3);
    board[0][3] = Piece('Q', 1, 3, 0, 9);
    board[0][4] = Piece('K', 1, 4, 0, 0);
    board[0][5] = Piece('B', 1, 5, 0, 3);
    board[0][6] = Piece('N', 1, 6, 0, 3);
    board[0][7] = Piece('R', 1, 7, 0, 5);
    for (int i = 0; i < 8; i++) {
        board[1][i] = Piece('P', 1, i, 1, 1);
    }

    board[7][0] = Piece('r', 0, 0, 7, 5);
    board[7][1] = Piece('n', 0, 1, 7, 3);
    board[7][2] = Piece('b', 0, 2, 7, 3);
    board[7][3] = Piece('q', 0, 3, 7, 9);
    board[7][4] = Piece('k', 0, 4, 7, 0);
    board[7][5] = Piece('b', 0, 5, 7, 3);
    board[7][6] = Piece('n', 0, 6, 7, 3);
    board[7][7] = Piece('r', 0, 7, 7, 5);
    for (int i = 0; i < 8; i++) {
        board[6][i] = Piece('p', 0, i, 6, 1);
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Piece('.', 0, j, i, 0);
        }
    }

    // blackP.push_back(Piece('r', 0, 0, 0, 5));
    // blackP.push_back(Piece('n', 0, 0, 1, 3));
    // blackP.push_back(Piece('b', 0, 0, 2, 3));
    // blackP.push_back(Piece('q', 0, 0, 3, 9));
    // blackP.push_back(Piece('k', 0, 0, 4, 0));
    // blackP.push_back(Piece('b', 0, 0, 5, 3));
    // blackP.push_back(Piece('n', 0, 0, 6, 3));
    // blackP.push_back(Piece('r', 0, 0, 7, 5));
    // for (int i = 0; i < 8; i++) {
    //     blackP.push_back(Piece('p', 0, 1, i, 1));
    // }

    // whiteP.push_back(Piece('R', 1, 7, 0, 5));
    // whiteP.push_back(Piece('N', 1, 7, 1, 3));
    // whiteP.push_back(Piece('B', 1, 7, 2, 3));
    // whiteP.push_back(Piece('Q', 1, 7, 3, 9));
    // whiteP.push_back(Piece('K', 1, 7, 4, 0));
    // whiteP.push_back(Piece('B', 1, 7, 5, 3));
    // whiteP.push_back(Piece('N', 1, 7, 6, 3));
    // whiteP.push_back(Piece('R', 1, 7, 7, 5));
    // for (int i = 0; i < 8; i++) {
    //     whiteP.push_back(Piece('P', 1, 6, i, 1));
    // }

    // for (Piece p : blackP) {
    //     board[p.getX()][p.getY()] = p;
    // }
    // for (Piece p : whiteP) {
    //     board[p.getX()][p.getY()] = p;
    // }
    // for (int i = 2; i < 6; i++) {
    //     for (int j = 0; j < 8; j++) {
    //         board[i][j] = Piece('.', 0, i, j, 0);
    //     }
    // }

    this->turn = 1;
    this->gameOver = 0;
    this->board = board;
    this->whiteP = whiteP;
    this->blackP = blackP;
}

Board::~Board() {
    // std::cout << "Board destructor called" << std::endl;
}

Board::Board(const Board& other) {
    this->board = other.board;
    this->whiteP = other.whiteP;
    this->blackP = other.blackP;
}

Board& Board::operator=(const Board& other) {
    this->board = other.board;
    this->whiteP = other.whiteP;
    this->blackP = other.blackP;
    return *this;
}

void Board::printBoard() {
    std::cout << std::endl;
    for (int i = 7; i >= 0; i--) {
        std::cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            std::cout << this->board[i][j].getType() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "    - - - - - - - -" << std::endl;
    std::cout << "    ";
    for (int i = 0; i < 8; i++) {
        std::cout << (char)('a' + i) << " ";
    }
    std::cout << std::endl;
}

std::string Board::takeInput() {
    std::string input;
    
    while (1){
        std::cout << "Turn is " << (whoTurn() ? "White" : "Black") << ". Enter your move: " <<std::endl << ">> ";
        std::cin >> input;
        if (input.length() == 4 && (input[0] >= 'a' && input[0] <= 'h' && input[1] >= '1' && input[1] <= '8' && input[2] >= 'a' && input[2] <= 'h' && input[3] >= '1' && input[3] <= '8')) {
            break;
        }
        else{
            std::cout << std::endl << "- Invalid input. valid move examples are a1a3, b7c5, etc." << std::endl;
        }
    }
    return input;
}

bool Board::isValidMove(std::string input) {
    int startX = input[0] - 'a';
    int startY = input[1] - '1';
    int endX = input[2] - 'a';
    int endY = input[3] - '1';

    if(!isPiece(startX, startY) ||
        (getPiece(startX, startY).getColor() != whoTurn()) ||
        isFriend(endX, endY))
    {
        return false;
    }
    if(!pieceChecks(startX, startY, endX, endY))
    {
        return false;
    }
    return true;
}

bool Board::pieceChecks(int Sx, int Sy, int Ex, int Ey)
{
    Piece &start = getPiece(Sx, Sy);
    Piece &end = getPiece(Ex, Ey);

    char type = start.getType();
    if(type != 'P')
        type = tolower(type);

    switch (start.getType())
    {
    case 'P':
        if (start.getX() == end.getX())
        {
            if(end.getY() - start.getY() > 2 || end.getY() - start.getY() < 1)
                return false;
            if(isPiece(Ex, Ey))
                return false;
            if(!checkPath(Sx, Sy, Ex, Ey))
                return false;
        }
        break;
    }
    return true;
}

int min(int n1, int n2)
{
    return (n1>n2 ? n2 : n1);
}

int max(int n1, int n2)
{
    return (n1>n2 ? n1 : n2);
}

bool Board::checkPath(int Sx, int Sy, int Ex, int Ey)
{
    int minX,maxX,minY,maxY;

    if (Sx == Ex)
    {
        minY = min(Sy, Ey);
        maxY = max(Sy, Ey);
        for (int i = minY + 1; i < maxY; i++)
        {
            if(isPiece(Sx, i))
                return false;
        }
    }
    else if (Sy == Ey)
    {
        minX = min(Sx, Ex);
        maxX = max(Sx, Ex);
        for (int i = minX + 1; i < maxX; i++)
        {
            if(isPiece(i, Sy))
                return false;
        }
    }
    else if (abs(Sx - Ex) == abs(Sy - Ey))
    {
        // minX = min(Sx, Ex);
        // maxX = max(Sx, Ex);
        // minY = min(Sy, Ey);
        // maxY = max(Sy, Ey);

        // while(minX < maxX && minY < maxY)
        // {
        //     minX++;
        //     minY++;
        //     if(isPiece(minX))
        // }
    }


    return true;
}

void Board::movePiece(std::string input) {
    int startX = input[0] - 'a';
    int startY = input[1] - '1';
    int endX = input[2] - 'a';
    int endY = input[3] - '1';

    if(isOpponent(endX, endY))
    {
        hitPiece(startX, startY, endX, endY);
    }
    else
    {
        swapPieces(startX, startY, endX, endY);
    }
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

bool Board::whoTurn() {
    return this->turn;
}

bool Board::isGameOver() {
    return this->gameOver;
}

void Board::nextTurn() {
    this->turn = !this->turn;
}

bool Board::isPiece(int x, int y) {
    return (this->board[y][x].getType() != '.');
}

bool Board::isOpponent(int x, int y) {
    return (isPiece(x, y) && getPiece(x, y).getColor() != whoTurn());
}

bool Board::isFriend(int x, int y) {
    return (isPiece(x, y) && getPiece(x, y).getColor() == whoTurn());
}

bool Board::isBlack(int x, int y) {
    return (isPiece(x, y) && getPiece(x, y).getColor() == 0);
}

bool Board::isWhite(int x, int y) {
    return (isPiece(x, y) && getPiece(x, y).getColor() == 1);
}

Piece& Board::getPiece(int x, int y) {
    return this->board[y][x];
}