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

chessboardSquare selectedSquare(int x,int y);
void moveRight (pawn* pawn,SDL_Window *window,SDL_Renderer *render);
void moveLeft (pawn* pawn,SDL_Window *window,SDL_Renderer *render);
void moveUp (pawn* pawn,SDL_Window *window,SDL_Renderer *render);
void moveDown (pawn* pawn,SDL_Window *window,SDL_Renderer *render);
void pawnFiller(pawn* pawn,char* pawnType,int color,int x,int y,SDL_Window *window,SDL_Renderer *render);


//-----------------BOARD MANAGEMENT---------------//

chessboardSquare chessboard[NB_CELL_PER_SIDE][NB_CELL_PER_SIDE];

void generateChessboardSquareArray(){
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++)
    {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++)
        {
            chessboard[rowX][rowY].x = (LEFT_SIDE + 1) + (rowX * CELL_SIZE);
            chessboard[rowX][rowY].y = (TOP_SIDE + 1) + (rowY * CELL_SIZE);
            printf("\nX : %d   Y : %d\n", rowX, rowY);
        }
    }
}


chessboardSquare selectedSquare(int selectedX,int selectedY){
    for (int rowX = 0; rowX < NB_CELL_PER_SIDE; rowX++)
    {
        for (int rowY = 0; rowY < NB_CELL_PER_SIDE; rowY++)
        {

            /*
                Ici, je rajoute des +1 après chaque FLAG car les flag de base (TOP_SIDE...) ne sont pas des valeur pile sur 90 (TOP_SIDE = 89 au lieu de 90)
            */

            if (selectedX < (LEFT_SIDE + 1) || selectedX > (RIGHT_SIDE + 1))
            {
                chessboardSquare ERROR = {.x = 0,.y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedY < (TOP_SIDE + 1) || selectedY > (BOTTOM_SIDE + 1))
            {
                chessboardSquare ERROR = {.x = 0,.y = 0};
                printf("Erreur Coordonnées INVALIDE\n");
                return ERROR;
            }

            if (selectedX >= (rowX * CELL_SIZE + (LEFT_SIDE + 1)) && selectedX < ((rowX+1) * CELL_SIZE + (LEFT_SIDE + 1)))
            {
                if (selectedY >= (rowY * CELL_SIZE + (TOP_SIDE + 1)) && selectedY < ((rowY+1) * CELL_SIZE + (TOP_SIDE + 1)))
                {
                    //printf("\n\n(%d, %d)\n\n", rowX, rowY);
                    return chessboard[rowX][rowY];
                }
            }
        }
    }
}

//-----------BASE MOVES----------------//
void moveUp (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    pawn->CurrentPosition.y = pawn->CurrentPosition.y - 90;
}

void moveDown (pawn* pawn,SDL_Window *window,SDL_Renderer *render) { 
    pawn->CurrentPosition.y = pawn->CurrentPosition.y + 90;
}

void moveLeft (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    pawn->CurrentPosition.x = pawn->CurrentPosition.x - 90;
}

void moveRight (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    pawn->CurrentPosition.x = pawn->CurrentPosition.x + 90;
}

int isValidMove(int x, int y) {
    if (x > RIGHT_SIDE) {
        return 0;
    }
    if (x < LEFT_SIDE + 1) {
        return 0;
    }
    if (y < TOP_SIDE + 1) {
        return 0;
    }
    if (y > BOTTOM_SIDE) {
        return 0;
    }
    return 1;
}
//---------------PAWN MOVES------------------//

pawn* selectedPawn(chessboardSquare selectedSquare) {
    for (int i = 0; i < sizeof(pawnArray)/2; i++) {
        if (pawnArray[i]->CurrentPosition.x == selectedSquare.x && pawnArray[i]->CurrentPosition.y == selectedSquare.y) {
            return pawnArray[i];
        }
    }

    printf("Aucun Pion ici\n");
    return &ERROR;
}

void knghtAllowedMoves(pawn knight,SDL_Window* window,SDL_Renderer* render) {
    //move en L vers le haut
    SDL_Rect displayer;
    displayer.h = 89;
    displayer.w = 89;
    pawn baseKnight = knight;
    displayAll(window,render);
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);

    //MOVE 1
    moveUp(&knight,window,render);
    moveUp(&knight,window,render);
    moveLeft(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 2
    moveUp(&knight,window,render);
    moveUp(&knight,window,render);
    moveRight(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 3
    moveLeft(&knight,window,render);
    moveLeft(&knight,window,render);
    moveUp(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 4
    moveRight(&knight,window,render);
    moveRight(&knight,window,render);
    moveUp(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 5
    moveLeft(&knight,window,render);
    moveLeft(&knight,window,render);
    moveDown(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 6
    moveRight(&knight,window,render);
    moveRight(&knight,window,render);
    moveDown(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 7
    moveDown(&knight,window,render);
    moveDown(&knight,window,render);
    moveRight(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;
    //MOVE 8
    moveDown(&knight,window,render);
    moveDown(&knight,window,render);
    moveLeft(&knight,window,render);
    if (isValidMove(knight.CurrentPosition.x,knight.CurrentPosition.y)) {
        displayer.x = knight.CurrentPosition.x;
        displayer.y = knight.CurrentPosition.y;
        SDL_RenderFillRect(render,&displayer);
    }
    knight = baseKnight;

    SDL_RenderPresent(render);

}
