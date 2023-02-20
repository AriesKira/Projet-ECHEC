#include "pawnCreation.h"

typedef struct chessboardSquare chessboardSquare;
struct chessboardSquare {
    int x;
    int y;
};

int isCheck(pawn *chessboard, bool colorPlaying, bool isValidation, SDL_Window *window, SDL_Renderer *render);
void printBoard(pawn *board);


//-----------------BOARD MANAGEMENT---------------//

chessboardSquare allowedMoves[27];
chessboardSquare chessboard[NB_CELL_PER_SIDE][NB_CELL_PER_SIDE];

void generateChessboardSquareArray() {
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++) {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++) {
            chessboard[rowX][rowY].x = (LEFT_SIDE + 1) + (rowX * CELL_SIZE);
            chessboard[rowX][rowY].y = (TOP_SIDE + 1) + (rowY * CELL_SIZE);
        }
    }
}


chessboardSquare selectedSquare(int selectedX, int selectedY) {
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++) {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++) {
            if (selectedX < (LEFT_SIDE + 1) || selectedX > (RIGHT_SIDE + 1)) {
                chessboardSquare ERROR = {.x = 0, .y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedY < (TOP_SIDE + 1) || selectedY > (BOTTOM_SIDE + 1)) {
                chessboardSquare ERROR = {.x = 0, .y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedX >= (rowX * CELL_SIZE + (LEFT_SIDE + 1)) &&
                selectedX < ((rowX + 1) * CELL_SIZE + (LEFT_SIDE + 1))) {
                if (selectedY >= (rowY * CELL_SIZE + (TOP_SIDE + 1)) &&
                    selectedY < ((rowY + 1) * CELL_SIZE + (TOP_SIDE + 1))) {
                    //printf("\n\n(%d, %d)\n\n", rowX, rowY);
                    return chessboard[rowX][rowY];
                }
            }
        }
    }
    chessboardSquare ERROR = {.x = 0, .y = 0};
    return  ERROR;
}

int selectedPawn(pawn *board, chessboardSquare selectedSquare, bool colorPlaying) {
    for (int i = 0; i < sizeOfPawnArray; i++) {
        if (board[i].CurrentPosition.x == selectedSquare.x && board[i].CurrentPosition.y == selectedSquare.y) {
            if (board[i].teamColor != colorPlaying) {
                return -2;
            }
            return i;
        }
    }

    return -1;
}
//-----------BASE MOVES----------------//

int isValidMove(pawn *board, pawn pawn, bool colorPlaying, bool kingCurrentlyChecking, SDL_Window *window,
                SDL_Renderer *render) {
    chessboardSquare pawnsSquare = {.x = pawn.CurrentPosition.x, .y = pawn.CurrentPosition.y};
    int hasPawn;
    int pawnType;

    hasPawn = selectedPawn(board, pawnsSquare, colorPlaying);
    if (pawn.CurrentPosition.x >= RIGHT_SIDE) {
        return 0;
    }
    if (pawn.CurrentPosition.x < LEFT_SIDE + 1) {
        return 0;
    }
    if (pawn.CurrentPosition.y < TOP_SIDE + 1) {
        return 0;
    }
    if (pawn.CurrentPosition.y > BOTTOM_SIDE) {
        return 0;
    }

    if (hasPawn != -2 && hasPawn != -1) {
        if (board[hasPawn].teamColor == pawn.teamColor) {
            return -1;
        }
    }
    if (hasPawn == -2) {
        return 2;
    }

    return 1;
}
//---------------PAWN MOVES------------------//

int isSelfCheck(pawn *board, pawn pawny, bool colorPlaying, SDL_Window *window, SDL_Renderer *render, pawn basePawn,
                int pawnIndex) {
    board[pawnIndex].CurrentPosition = pawny.CurrentPosition;   
    int checked = isCheck(board, !colorPlaying, true, window, render);
    board[pawnIndex].CurrentPosition = (basePawn).CurrentPosition;
    return checked;
}

void knightAllowedMoves(pawn *board, pawn knight, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;
    pawn baseKnight = knight;

    chessboardSquare pawnPosition = {.x = knight.CurrentPosition.x,.y = knight.CurrentPosition.y};
    int pawnIndex = selectedPawn(board, pawnPosition, colorPlaying);

    // MOVE 1
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int j = 0; j < 8; j++) {
        knight.CurrentPosition.x += dx[j] * 90;
        knight.CurrentPosition.y += dy[j] * 90;
        if (isValidMove(board, knight, colorPlaying, false, window, render) == 1 ||
            isValidMove(board, knight, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, knight, colorPlaying, window, render, baseKnight, pawnIndex)) {
                knight.CurrentPosition.x = baseKnight.CurrentPosition.x;
                knight.CurrentPosition.y = baseKnight.CurrentPosition.y;
                continue;
            }
            displayer.x = knight.CurrentPosition.x;
            displayer.y = knight.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        knight.CurrentPosition.x = baseKnight.CurrentPosition.x;
        knight.CurrentPosition.y = baseKnight.CurrentPosition.y;
    }
    // Afficher les mouvements possibles


}



void queenAllowedMoves(pawn *board, pawn queen, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    pawn baseQueen = queen;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;

    chessboardSquare queenPosition = {.x = queen.CurrentPosition.x,.y = queen.CurrentPosition.y};
    int queenIndex = selectedPawn(board, queenPosition,colorPlaying);

    //Move UP
    for (int j = 1; queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.y -= move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;

    //Move Down
    for (int j = 1; queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.y += move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }

    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //Move Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE; j++) {
        queen.CurrentPosition.x += move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //Move Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //MOVE UP - RIGHT
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE UP - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y += move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y += move;
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, queen, colorPlaying, window, render, baseQueen, queenIndex)) {
                queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
                queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
                continue;
            }
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, queen, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;

}

void pawnAllowedMoves(pawn *board, pawn pawnSelected, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    pawn basePawn = pawnSelected;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;

    chessboardSquare pawnPosition = {.x = pawnSelected.CurrentPosition.x,.y = pawnSelected.CurrentPosition.y};
    int pawnIndex = selectedPawn(board, pawnPosition, colorPlaying);

    if (pawnSelected.CurrentPosition.x == basePawn.basePosition.x &&
        pawnSelected.CurrentPosition.y == basePawn.basePosition.y && pawnSelected.teamColor == 0) {
        for (int j = 1; pawnSelected.CurrentPosition.y > basePawn.CurrentPosition.y - (move * 2); i++) {
            pawnSelected.CurrentPosition.y -= move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 1) {
                if (!checkValidation && isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x;
                    pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;
                    continue;
                }
                displayer.x = pawnSelected.CurrentPosition.x;
                displayer.y = pawnSelected.CurrentPosition.y;
                allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                allowedMoves[i] = allowedMoveFiller;
                i++;
            }
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                break;
            }
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == -1) {
                break;
            }
        }
        pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;

    } else if (pawnSelected.CurrentPosition.x == basePawn.basePosition.x &&
               pawnSelected.CurrentPosition.y == basePawn.basePosition.y && pawnSelected.teamColor == 1) {
        for (int j = 1; pawnSelected.CurrentPosition.y < basePawn.basePosition.y + (move * 2); i++) {
            pawnSelected.CurrentPosition.y += move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 1) {
                if (!checkValidation && isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x;
                    pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;
                    continue;
                }
                displayer.x = pawnSelected.CurrentPosition.x;
                displayer.y = pawnSelected.CurrentPosition.y;
                allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                allowedMoves[i] = allowedMoveFiller;
                i++;
            }
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                break;
            }
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == -1) {
                break;
            }
        }
        pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;
    } else {
        //Move UP
        if (pawnSelected.teamColor == 0) {
            pawnSelected.CurrentPosition.y -= move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 1) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.x -= move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x + move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;
            pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x;
        } else {
            //Move UP
            pawnSelected.CurrentPosition.y += move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 1) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.x -= move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x + move;
            if (isValidMove(board, pawnSelected, colorPlaying, false, window, render) == 2) {
                if (!checkValidation && !isSelfCheck(board, pawnSelected, colorPlaying, window, render, basePawn, pawnIndex)) {
                    displayer.x = pawnSelected.CurrentPosition.x;
                    displayer.y = pawnSelected.CurrentPosition.y;
                    allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                    allowedMoves[i] = allowedMoveFiller;
                    i++;
                }
            }
            pawnSelected.CurrentPosition.y = basePawn.CurrentPosition.y;
            pawnSelected.CurrentPosition.x = basePawn.CurrentPosition.x;
        }
    }
}

void rookAllowedMoves(pawn *board, pawn rook, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    pawn baseRook = rook;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;

    chessboardSquare pawnPosition = {.x = rook.CurrentPosition.x,.y = rook.CurrentPosition.y};
    int pawnIndex = selectedPawn(board, pawnPosition, colorPlaying);

    //Move UP
    for (int j = 1; rook.CurrentPosition.y >= TOP_SIDE; j++) {
        rook.CurrentPosition.y -= move;
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    rook.CurrentPosition.y = baseRook.CurrentPosition.y;

    //Move Down
    for (int j = 1; rook.CurrentPosition.y < BOTTOM_SIDE; j++) {
        rook.CurrentPosition.y += move;
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == -1) {
            break;
        }

    }
    rook.CurrentPosition.y = baseRook.CurrentPosition.y;
    //Move Right
    for (int j = 1; rook.CurrentPosition.x <= RIGHT_SIDE; j++) {
        rook.CurrentPosition.x += move;
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    rook.CurrentPosition.x = baseRook.CurrentPosition.x;
    //Move Left
    for (int j = 1; rook.CurrentPosition.x >= LEFT_SIDE; j++) {
        rook.CurrentPosition.x -= move;
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, rook, colorPlaying, window, render, baseRook, pawnIndex)) {
                rook.CurrentPosition.x = baseRook.CurrentPosition.x;
                rook.CurrentPosition.y = baseRook.CurrentPosition.y;
                continue;
            }
            displayer.x = rook.CurrentPosition.x;
            displayer.y = rook.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, rook, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    rook.CurrentPosition.x = baseRook.CurrentPosition.x;

}

void bishopAllowedMoves(pawn *board, pawn bishop, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    pawn baseBishop = bishop;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;

    chessboardSquare pawnPosition = {.x = bishop.CurrentPosition.x,.y = bishop.CurrentPosition.y};
    int pawnIndex = selectedPawn(board, pawnPosition, colorPlaying);

    //MOVE UP - RIGHT
    for (int j = 1; bishop.CurrentPosition.x <= RIGHT_SIDE && bishop.CurrentPosition.y >= TOP_SIDE; j++) {
        bishop.CurrentPosition.x += move;
        bishop.CurrentPosition.y -= move;
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
    bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
    //MOVE UP - Left
    for (int j = 1; bishop.CurrentPosition.x >= LEFT_SIDE && bishop.CurrentPosition.y >= TOP_SIDE; j++) {
        bishop.CurrentPosition.x -= move;
        bishop.CurrentPosition.y -= move;
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
    bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
    //MOVE Down - Left
    for (int j = 1; bishop.CurrentPosition.x >= LEFT_SIDE && bishop.CurrentPosition.y < BOTTOM_SIDE; j++) {
        bishop.CurrentPosition.x -= move;
        bishop.CurrentPosition.y += move;
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
    bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
    //MOVE Down - Right
    for (int j = 1; bishop.CurrentPosition.x <= RIGHT_SIDE && bishop.CurrentPosition.y < BOTTOM_SIDE; j++) {
        bishop.CurrentPosition.x += move;
        bishop.CurrentPosition.y += move;
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 1) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == 2) {
            if (!checkValidation && isSelfCheck(board, bishop, colorPlaying, window, render, baseBishop, pawnIndex)) {
                bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
                bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
                continue;
            }
            displayer.x = bishop.CurrentPosition.x;
            displayer.y = bishop.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(board, bishop, colorPlaying, false, window, render) == -1) {
            break;
        }
    }
    bishop.CurrentPosition.x = baseBishop.CurrentPosition.x;
    bishop.CurrentPosition.y = baseBishop.CurrentPosition.y;
}

void kingsMoves(pawn *board, pawn king, bool colorPlaying, bool checkValidation, chessboardSquare * allowedMoves, SDL_Window *window, SDL_Renderer *render) {
    pawn baseKing = king;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0, .y = 0};
    struct displayer {
        int x;
        int y;
    } displayer;

    chessboardSquare pawnPosition = {.x = king.CurrentPosition.x,.y = king.CurrentPosition.y};
    int pawnIndex = selectedPawn(board, pawnPosition, colorPlaying);

    int moves[8][2] = {{-1, 0},
                       {1,  0},
                       {0,  -1},
                       {0,  1},
                       {-1, -1},
                       {-1, 1},
                       {1,  -1},
                       {1,  1}};


        // Itération à travers chaque mouvement possible
        for (int j = 0; j < 8; j++) {
            int dx = moves[j][0];
            int dy = moves[j][1];

            king.CurrentPosition.x = baseKing.CurrentPosition.x + (move * dx);
            king.CurrentPosition.y = baseKing.CurrentPosition.y + (move * dy);

            if (isValidMove(board, king, colorPlaying, false, window, render) == 1 ||
                isValidMove(board, king, colorPlaying, false, window, render) == 2) {
                if (!checkValidation) {
                    bool ischecked = isSelfCheck(board, king, colorPlaying, window, render, baseKing, pawnIndex);
                    if (ischecked) {
                        king.CurrentPosition.x = baseKing.CurrentPosition.x;
                        king.CurrentPosition.y = baseKing.CurrentPosition.y;
                        continue;
                    }
                }
                displayer.x = king.CurrentPosition.x;
                displayer.y = king.CurrentPosition.y;
                allowedMoveFiller = selectedSquare(displayer.x, displayer.y + 1);
                allowedMoves[i] = allowedMoveFiller;
                i++;
            }

            king.CurrentPosition.x = baseKing.CurrentPosition.x;
            king.CurrentPosition.y = baseKing.CurrentPosition.y;

     }


}

void kingAllowedMoves(pawn *board, pawn king, bool colorPlaying, chessboardSquare * allowedMoves, bool checkValidation, SDL_Window *window, SDL_Renderer *render) {
    kingsMoves(board, king, colorPlaying, checkValidation, allowedMoves, window, render);
}

void displayMovesAvailable(bool colorPlaying,bool isInCheck,SDL_Window *window, SDL_Renderer *render) {
    SDL_RenderClear(render);
    createChessboard(window, render);
    createLegend(window,render);
    for (int i = 0; i < sizeOfPawnArray; i++) {
        createPawn(window, render, pawnArray[i]);
    }
    SDL_Rect displayer;
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);
    for (int i = 0; i < 28; i++) {
        displayer.h = 89;
        displayer.w = 89;
        displayer.x = allowedMoves[i].x;
        displayer.y = allowedMoves[i].y;
        SDL_RenderFillRect(render, &displayer);
    }
    if (isInCheck) {
        createCheck(!colorPlaying,window,render);
    }

    SDL_RenderPresent(render);

}

void cleanMoveArray(chessboardSquare* array) {
    for (int i = 0; i < 27; i++) {
        array[i].x = -1;
        array[i].y = -1;
    }
}

void emptyAllowedMoves() {
    for (int i = 0; i < 28; i++) {
        allowedMoves[i].x = -1;
        allowedMoves[i].y = -1;
    }
}

void diplayAllowedMoves(pawn selectedPawn, bool colorPlaying,bool isInCheck, SDL_Window *window, SDL_Renderer *render) {
    int pawnType;
    funcNumb(selectedPawn.type, selectedPawn.teamColor, &pawnType);
    pawn board[sizeOfPawnArray];
    copyBoard(board);
    chessboardSquare moves[MAX_PAWN_MOVES];
    cleanMoveArray(moves);
    switch (pawnType) {
        case 1:
        case 7:
            pawnAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        case 2:
        case 8:
            knightAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        case 3:
        case 9:
            bishopAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        case 4:
        case 10:
            rookAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        case 5 :
        case 11:
            queenAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        case 6:
        case 12:
            kingAllowedMoves(board, selectedPawn, colorPlaying, moves, false, window, render);
            break;
        default:
            printf("Mouvement introuvable\n");
            break;
    }

    emptyAllowedMoves();
    for (int move = 0; move < MAX_PAWN_MOVES; ++move) {
        allowedMoves[move] = moves[move];
    }
    displayMovesAvailable(colorPlaying,isInCheck,window, render);
}

void movePawn(pawn *pawn, chessboardSquare chosenMove, SDL_Window *window, SDL_Renderer *render) {
    pawn->CurrentPosition.x = chosenMove.x;
    pawn->CurrentPosition.y = chosenMove.y;
    printf("pawn has moved to : x = %d / y = %d\n", pawn->CurrentPosition.x, pawn->CurrentPosition.y);
}

int isAllowedMove(chessboardSquare chosenMove) {
    for (int i = 0; i < 28; i++) {
        if (allowedMoves[i].x == chosenMove.x && allowedMoves[i].y == chosenMove.y) {
            return 1;
        } else if (allowedMoves[i].x == 0 && allowedMoves[i].y == 0) {
            continue;
        }
        continue;
    }
    return 0;
}


void eatPawn(int target) {
    pawnArray[target]->alive = false;
    pawnArray[target]->CurrentPosition.x = 0;
    pawnArray[target]->CurrentPosition.y = 0;
}


