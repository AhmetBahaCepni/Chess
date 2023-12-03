#include "../libraries/Board.hpp"


void Board::saveGame() const
{
    std::ofstream file;
    file.open("log/save.txt");

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
    file.open("log/save.txt");
    if(!file.is_open())
    {
        std::cout << "no save file found" << std::endl;
        return;
    }

    std::vector<std::vector<Piece>> _board(8, std::vector<Piece>(8));
    std::vector<std::vector<bool>> _wThreads(8, std::vector<bool>(8));
    std::vector<std::vector<bool>> _bThreads(8, std::vector<bool>(8));
    std::vector<bool> _castlingVariables(4); 
    std::vector<double> _points(2);

    std::string line;
    int i = 7;
    while (getline(file, line) && i >= 0)
    {
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
    this->castlingVariables = _castlingVariables;

    file.close();
}