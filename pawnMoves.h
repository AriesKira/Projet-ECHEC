#include "pawnCreation.h"

#define LEFT_SIDE 239
#define RIGHT_SIDE 959
#define TOP_SIDE 89
#define BOTTOM_SIDE 809
#define CELL_SIZE 90
#define NB_CELL_PER_SIDE 8

typedef struct chessboardSquare chessboardSquare;
struct chessboardSquare {
    int x;
    int y;
};

//-----------------BOARD MANAGEMENT---------------//
chessboardSquare allowedMoves[28];
chessboardSquare chessboard[NB_CELL_PER_SIDE][NB_CELL_PER_SIDE];

void generateChessboardSquareArray() {
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++) {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++) {
            chessboard[rowX][rowY].x = (LEFT_SIDE + 1) + (rowX * CELL_SIZE);
            chessboard[rowX][rowY].y = (TOP_SIDE + 1) + (rowY * CELL_SIZE);
        }
    }
}


chessboardSquare selectedSquare(int selectedX,int selectedY){
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++) {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++) {
            if (selectedX < (LEFT_SIDE + 1) || selectedX > (RIGHT_SIDE + 1)) {
                chessboardSquare ERROR = {.x = 0,.y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedY < (TOP_SIDE + 1) || selectedY > (BOTTOM_SIDE + 1)) {
                chessboardSquare ERROR = {.x = 0,.y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedX >= (rowX * CELL_SIZE + (LEFT_SIDE + 1)) && selectedX < ((rowX+1) * CELL_SIZE + (LEFT_SIDE + 1))) {
                if (selectedY >= (rowY * CELL_SIZE + (TOP_SIDE + 1)) && selectedY < ((rowY+1) * CELL_SIZE + (TOP_SIDE + 1))) {
                    //printf("\n\n(%d, %d)\n\n", rowX, rowY);
                    return chessboard[rowX][rowY];
                }
            }
        }
    }
}

int selectedPawn(chessboardSquare selectedSquare,bool colorPlaying) {
    for (int i = 0; i < sizeof(pawnArray)/2; i++) {
        if (pawnArray[i]->CurrentPosition.x == selectedSquare.x && pawnArray[i]->CurrentPosition.y == selectedSquare.y) {
            if (pawnArray[i]->teamColor != colorPlaying) {
                return-2;
            }
            return i;
        }
    }

    return -1;
}
//-----------BASE MOVES----------------//

int isValidMove(pawn pawn,bool colorPlaying) {
    chessboardSquare pawnsSquare = {.x = pawn.CurrentPosition.x,.y = pawn.CurrentPosition.y};
    int hasPawn;
    int pawnType;
    hasPawn = selectedPawn(pawnsSquare,colorPlaying);
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
        if (pawnArray[hasPawn]->teamColor == pawn.teamColor) {
            return -1;
        }
    }
    if (hasPawn == -2) {
        return 2;
    }
    
    return 1;
}
//---------------PAWN MOVES------------------//



void knightAllowedMoves(pawn knight,bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0,.y = 0};
    struct displayer {
        int x;
        int y;
    }displayer;
    pawn baseKnight = knight;
    

    // MOVE 1
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int j = 0; j < 8; j++) {
        knight.CurrentPosition.x += dx[j] * 90;
        knight.CurrentPosition.y += dy[j] * 90;
        if (isValidMove(knight,colorPlaying) == 1 || isValidMove(knight,colorPlaying) == 2) {
            displayer.x = knight.CurrentPosition.x;
            displayer.y = knight.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        knight.CurrentPosition.x = baseKnight.CurrentPosition.x;
        knight.CurrentPosition.y = baseKnight.CurrentPosition.y;
    }
    // Afficher les mouvements possibles


}
void queenAllowedMoves(pawn queen,bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    pawn baseQueen = queen;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0,.y = 0};
    struct displayer{
        int x;
        int y;
    }displayer;
   
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);
    //Move UP
    for (int j = 1; queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            continue;
        }
    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    
    //Move Down
    for (int j = 1; queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
        
    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //Move Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE; j++) {
        queen.CurrentPosition.x += move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //Move Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //MOVE UP - RIGHT
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE UP - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying) == 1) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
        }
        if (isValidMove(queen,colorPlaying) == 2) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            break;
        }
        if (isValidMove(queen,colorPlaying) == -1) {
            break;
        }
    }
    
}

void displayMovesAvailable(SDL_Window * window,SDL_Renderer * render) {
    SDL_RenderClear(render);
    createChessboard(window,render);
    for (int i = 0; i < sizeof(pawnArray)/2; i++) {
        createPawn(window,render,pawnArray[i]);
    }
    SDL_Rect displayer;
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);
    for (int i = 0; i < 28; i++) {
        displayer.h = 89;
        displayer.w = 89;
        displayer.x = allowedMoves[i].x;
        displayer.y = allowedMoves[i].y;
        SDL_RenderFillRect(render,&displayer);
    }

    SDL_RenderPresent(render);
    
}


void diplayAllowedMoves(pawn selectedPawn,bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    int pawnType;
    funcNumb(selectedPawn.type,selectedPawn.teamColor, &pawnType);
    switch (pawnType) {
    case 1:
        //pawnAllowedMoves(selectedPawn,window,render);
        break;
    case 2:
        knightAllowedMoves(selectedPawn,colorPlaying,window,render);
        displayMovesAvailable(window,render);
        break;
    case 3:
        //bishopAllowedMoves(selectedPawn,window,render);
        break;
    case 4:
        //rookAllowedMoves(selectedPawn,window,render);
        break;
    case 5 :
        queenAllowedMoves(selectedPawn,colorPlaying,window,render);
        displayMovesAvailable(window,render);
        break;
    case 6:
        //kingAllowedMoves(selectedPawn,window,render);
        break;
    case 7:
        //pawnAllowedMoves(selectedPawn,window,render);
        break;
    case 8:
        knightAllowedMoves(selectedPawn,colorPlaying,window,render);
        displayMovesAvailable(window,render);
        break;
    case 9:
        //bishopAllowedMoves(selectedPawn,window,render);
        break;
    case 10:
        //rookAllowedMoves(selectedPawn,window,render);
        break;
    case 11:
        queenAllowedMoves(selectedPawn,colorPlaying,window,render);
        displayMovesAvailable(window,render);
        break;
    case 12:
        //kingAllowedMoves(selectedPawn,window,render);
        break;
    default:
        printf("Mouvement introuvable\n");
        break;
    }
}

void movePawn(pawn* pawn,chessboardSquare chosenMove,SDL_Window* window,SDL_Renderer* render) {
    pawn->CurrentPosition.x = chosenMove.x;
    pawn->CurrentPosition.y = chosenMove.y;
    printf("pawn has moved to : x = %d / y = %d\n",pawn->CurrentPosition.x,pawn->CurrentPosition.y);
}

int isAllowedMove(chessboardSquare chosenMove) {
    for (int i = 0; i < 28; i++) {
        if (allowedMoves[i].x == chosenMove.x && allowedMoves[i].y == chosenMove.y) {
            return 1;
        }else if (allowedMoves[i].x == 0 && allowedMoves[i].y == 0) {
            continue;
        }
        continue;
    }
    return 0;
}

void emptyAllowedMoves() {
    for (int i = 0; i < 28; i++) {
        allowedMoves[i].x = -1;
        allowedMoves[i].y = -1;
    }
}

void eatPawn(int target) {
    pawnArray[target]->alive = false;
    pawnArray[target]->CurrentPosition.x = 0;
    pawnArray[target]->CurrentPosition.y = 0;
}

