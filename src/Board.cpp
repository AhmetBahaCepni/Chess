#include "../libraries/Board.hpp"

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
    // we don't need to delete anything here because we only work with vectors
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
        // we need copy functions for deep copy of vectors
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

// we overload the << operator to print the board
std::ostream &operator<<(std::ostream &os, Board &board)
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "current points (W-B):  " << board.points[1] << " - " << board.points[0] << std::endl;

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