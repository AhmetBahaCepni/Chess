#include "../libraries/Board.hpp"

void Board::suggestMove(bool color)
{
    std::string bestMove = "";
    std::vector<std::string> friendMoves;
    std::vector<std::string> bestMoves;
    unsigned int random;
    double friendPoints;
    double bestPoints;
    
    friendMoves = getPossibleMoves(color);

    bestPoints = -1000;
    for(std::string move : friendMoves)
    {
        Piece& friendPiece = getPiece(move[1] - '1', move[0] - 'a');

        movePiece(move);
        if(isCheck(color))
        {
            undoMove(move);
            continue;
        }
        if(isCheck(!color))
        {
            if(isCheckMate(!color))
            {
                undoMove(move);
                bestMove = move;
                break;
            }
        }
        if(friendPiece.getUnderAttack())
        {
            undoMove(move);
            continue;
        }
        friendPoints = this->points[color] - this->points[!color];
        if(friendPoints >= bestPoints)
        {
            if(friendPoints > bestPoints)
                bestMoves.clear();
            bestPoints = friendPoints;
            bestMoves.push_back(move);
        }
        undoMove(move);
    }
    if(bestMoves.size() < 1 && bestMove == "")
    {
        std::cout << "no good move found" << std::endl;
    }
    else 
    {
        if(bestMove != "")
            std::cout << bestMove << std::endl;
        else
        {
            srand(time(NULL));
            random = rand() % bestMoves.size();
            std::cout << bestMoves[random] << std::endl;
        }
    }
}

std::vector<std::string> Board::getPossibleMoves(bool color)
{
    std::vector<std::string> _moves;

    for (auto &line : board)
    {
        for (auto &piece : line)
        {
            if (piece.getType() != '.')
            {
                if (piece.getColor() == color)
                {
                    for (auto &move : piece.getMoves())
                    {
                        _moves.push_back(move);
                    }
                }
            }
        }
    }

    return _moves;
}
// void Board::suggestMove(bool color)
// {
//     std::vector<std::string> bestMoves;
//     std::vector<std::string> friendMoves;
//     std::vector<std::string> opponentMoves;
//     double  bestOpponentPoints;
//     double  bestFriendPoints;
//     double netPoints = -1000;
//     double points;
//     int random;
//     std::string checkMove = "";
//     std::string bestMove = "";

//     for (auto &line : board)
//     {
//         for (auto &piece : line)
//         {
//             if (piece.getType() != '.')
//             {
//                 if (piece.getColor() == color)
//                 {
//                     for (auto &move : piece.getMoves())
//                     {
//                         friendMoves.push_back(move);
//                     }
//                 }
//             }
//         }
//     }
//     bestFriendPoints = -1000;
//     for(unsigned int i = 0; i < friendMoves.size(); i++)
//     {
//         std::string friendMove = friendMoves[i];
//         movePiece(friendMove);
//         if(isCheck(color))
//         {
//             undoMove(friendMove);
//             continue;
//         }
//         if(isCheck(!color))
//         {
//             if(isCheckMate(!color))
//             {
//                 undoMove(friendMove);
//                 bestMove = friendMove;
//                 break;
//             }
//             checkMove = friendMove;
//         }
        
//         opponentMoves.clear();
//         bestFriendPoints = this->points[color] - this->points[!color];
//         bestOpponentPoints = -1000;
//         for (auto &line : board)
//         {
//             for (auto &piece : line)
//             {
//                 if (piece.getType() != '.')
//                 {
//                     if (piece.getColor() == !color)
//                     {
//                         for (auto &move : piece.getMoves())
//                         {
//                             opponentMoves.push_back(move);
//                         }
//                     }
//                 }
//             }
//         }
//         for(unsigned int j = 0; j < opponentMoves.size(); j++)
//         {
//             std::string opponentMove = opponentMoves[j];

//             movePiece(opponentMove);
//             if(isCheck(!color) || isCheck(color))
//             {
//                 undoMove(opponentMove);
//                 continue;
//             }
//             points = this->points[!color] - this->points[color];
//             if(points > bestOpponentPoints)
//             {
//                 bestOpponentPoints = points;
//             }
//             undoMove(opponentMove);
//         }
//         if(bestFriendPoints - bestOpponentPoints > netPoints)
//         {
//             netPoints = bestFriendPoints - bestOpponentPoints;
//             bestMoves.clear();
//             bestMoves.push_back(friendMove);
//         }
//         undoMove(friendMove);
//     }
//     if(bestMoves.size() < 1 && checkMove == "" && bestMove == "")
//     {
//         std::cout << "no good move found" << std::endl;
//     }
//     else 
//     {
//         if(bestMove != "")
//             std::cout << bestMove << std::endl;
//         else if(checkMove != "")
//             std::cout << checkMove << std::endl;
//         else
//         {
//             srand(time(NULL));
//             random = rand() % bestMoves.size();
//             std::cout << bestMoves[random] << std::endl;
//         }
//     }
// }