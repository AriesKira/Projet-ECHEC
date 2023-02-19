#include "pawnMoves.h"

void fillAllowedMoves(pawn* board, pawn selectedPawn,bool colorPlaying,chessboardSquare * arrayToFill,SDL_Window* window,SDL_Renderer* render) {
    int pawnType;
    funcNumb(selectedPawn.type,colorPlaying, &pawnType);
    switch (pawnType) {
    case 1:
        pawnAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 2:
        knightAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 3:
        bishopAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window,  render);
        break;
    case 4:
        rookAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 5 :
        queenAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 6:
        kingAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 7:
        pawnAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 8:
        knightAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 9:
        bishopAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 10:
        rookAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 11:
        queenAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    case 12:
        kingAllowedMoves(board, selectedPawn,colorPlaying,arrayToFill, true, window, render);
        break;
    default:
        break;
    }
}



pawn copyPawn(pawn *board, int pawnIndex) {
    pawn copy =  {.CurrentPosition.x = board[pawnIndex].CurrentPosition.x,.CurrentPosition.y = board[pawnIndex].CurrentPosition.y,.teamColor = board[pawnIndex].teamColor,.type = board[pawnIndex].type,.basePosition.x = board[pawnIndex].basePosition.x,.basePosition.y = board[pawnIndex].basePosition.y,.alive = board[pawnIndex].alive};
    return copy;
}

void printBoard(pawn *board) {
    for (int border = 0; border < 24; ++border) {
        printf("---");
    }
    printf("\n");
    for (int column = 0; column < 8; ++column) {
        for (int row = 0; row < 8; ++row) {
            chessboardSquare square = chessboard[column][row];
            bool hasPawn = false;
            for (int pawnIndex = 0; pawnIndex < sizeOfPawnArray; ++pawnIndex) {
                pawn pawny = board[pawnIndex];
                if (pawny.alive && pawny.CurrentPosition.x == square.x && pawny.CurrentPosition.y == square.y) {
                    hasPawn = true;
                    printf("|%c%c ", pawny.teamColor ? 'b' : 'w',pawny.type[0]);
                }
            }
            if (!hasPawn) {
                printf("|  ");
            }
        }
        printf("\n");
    }
}

bool isMate(int checkPawn, int kingTarget, chessboardSquare position, SDL_Window *window, SDL_Renderer *render) {
    chessboardSquare movements[MAX_PAWN_MOVES];
    pawn board[sizeOfPawnArray];
    copyBoard(board);
    pawn king = board[kingTarget];
    for (int pawnIndex = 0; pawnIndex < sizeOfPawnArray; pawnIndex++) {
        pawn * tmpPawn = &board[pawnIndex];
        if (tmpPawn->alive == true && tmpPawn->teamColor == king.teamColor) {
            chessboardSquare basePosition = {.x = tmpPawn->CurrentPosition.x,.y = tmpPawn->CurrentPosition.y};
            cleanMoveArray(movements);
            fillAllowedMoves(board, *(tmpPawn), king.teamColor, movements, window, render);
            for (int move = 0; move < MAX_PAWN_MOVES; move++) {
                if (movements[move].x != -1 && movements[move].y != -1) {
                    int opponentPawn = -1;
                    if (selectedPawn(board, movements[move], tmpPawn->teamColor) == -2) {
                        opponentPawn = selectedPawn(board, movements[move], !tmpPawn->teamColor);
                        printf("Moving for mate %s\n", board[opponentPawn].type);
                        board[opponentPawn].CurrentPosition.x = 0;
                        board[opponentPawn].CurrentPosition.y = 0;
                        board[opponentPawn].alive = 0;

                    }
                    tmpPawn->CurrentPosition.x = movements[move].x;
                    tmpPawn->CurrentPosition.y = movements[move].y;

                    int checked = isCheck(board, !king.teamColor,true,window,render);
                    if (opponentPawn != -1) {
                        board[opponentPawn].CurrentPosition.x = movements[move].x;
                        board[opponentPawn].CurrentPosition.y = movements[move].y;
                        board[opponentPawn].alive = 1;
                    }
                    tmpPawn->CurrentPosition.x = basePosition.x;
                    tmpPawn->CurrentPosition.y = basePosition.y;
                    if (!checked) {
                        return 0;
                    }
                }
            }
        }
    }

    return  1;
}

int isCheck(pawn chessboard[MAX_PAWN_MOVES], bool colorPlaying,bool isValidation,SDL_Window* window,SDL_Renderer* render) {
    chessboardSquare arrayToFill[MAX_PAWN_MOVES];
    cleanMoveArray(arrayToFill);
    printBoard(chessboard);
    for (int i = 0; i < sizeOfPawnArray; i++) {
        if (chessboard[i].alive == true && chessboard[i].teamColor == colorPlaying) {
            pawn tmpPawn = chessboard[i];
            fillAllowedMoves(chessboard, tmpPawn, colorPlaying, arrayToFill, window, render);
            for (int j = 0; j < MAX_PAWN_MOVES; j++) {
                chessboardSquare position = arrayToFill[j];
                if (position.x == -1 && position.y == -1) {
                    break;
                }
                int target = selectedPawn(chessboard, position, !colorPlaying);
                if (target > -1 && strcmp(chessboard[target].type,"king") == 0 && chessboard[target].teamColor != colorPlaying) {
                    if (isValidation) {
                        return 1;
                    }
                    if(isMate(i,target, position, window, render)) {
                        return 2;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}