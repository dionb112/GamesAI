#include "AI.h"
#include <iostream>
#include <vector>

using namespace std;

void AI::init(int aiPlayer) {
    _aiPlayer = aiPlayer;
    if (_aiPlayer == X_VAL) {
        _humanPlayer = O_VAL;
    } else {
        _humanPlayer = X_VAL;
    }
}

void AI::performMove(Board& board) {
	countMoves = 1;
    AiMove bestMove = getBestMove(board, _aiPlayer, 5); // trying depth of one for recursion tree
    board.setVal(bestMove.x, bestMove.y, _aiPlayer);
}

AiMove AI::getBestMove(Board& board, int player, int depth) {

    // Base case, check for end state
    int rv = board.checkVictory();
    if (rv == _aiPlayer) {
        return AiMove(10);
    } else if (rv == _humanPlayer) {
        return AiMove(-10);
    } else if (rv == TIE_VAL) {
        return AiMove(0);
	} else if (depth == 0) {
		return AiMove(0);
	}

    std::vector<AiMove> moves;

//	cout << "Before recursive moves..\n";
//	cout << "Player = " << player << "\n";

    // Do the recursive function calls and construct the moves vector
    for (int y = 0; y < board.getSize(); y++) {
        for (int x = 0; x < board.getSize(); x++) {
            if (board.getVal(x, y) == NO_VAL) {
                AiMove move;
                move.x = x;
                move.y = y;
                board.setVal(x, y, player);
                if (player == _aiPlayer) {
                    move.score = getBestMove(board, _humanPlayer, depth-1).score;
                } else {
                    move.score = getBestMove(board, _aiPlayer, depth-1).score;
                }
                moves.push_back(move);
                board.setVal(x, y, NO_VAL);
            }
        }
    }

	// Pick the best move for the current player
    int bestMove = 0;
    if (player == _aiPlayer) {
        int bestScore = -1000000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score > bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    } else {
        int bestScore = 1000000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score < bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
	// Uncomment to see moves being considered
//	cout << "Best move = " << moves[bestMove].x << ", " << moves[bestMove].y << "\n";
//	cout << "Move count: " << countMoves++ << "\n";

	// Return the best move
    return moves[bestMove];
}