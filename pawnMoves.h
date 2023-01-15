#include "pawnCreation.h"

#define LEFT_SIDE 239
#define RIGHT_SIDE 959
#define TOP_SIDE 89
#define BOTTOM_SIDE 809

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

chessboardSquare A8 = {.x = LEFT_SIDE+1,.y = TOP_SIDE+1};chessboardSquare B8 = {.x = 330,.y = TOP_SIDE+1};chessboardSquare C8 = {.x = 420,.y = TOP_SIDE+1};chessboardSquare D8= {.x = 510,.y = TOP_SIDE+1} ;chessboardSquare E8 ={.x = 600,.y = TOP_SIDE+1};chessboardSquare F8 = {.x = 690,.y = TOP_SIDE+1};chessboardSquare G8 = {.x = 780,.y = TOP_SIDE+1};chessboardSquare H8 = {.x = RIGHT_SIDE+1,.y = TOP_SIDE +1};
chessboardSquare A7 = {.x = LEFT_SIDE+1,.y = 180};chessboardSquare B7 = {.x = 330,.y = 180};chessboardSquare C7 = {.x = 420,.y = 180};chessboardSquare D7 = {.x = 510,.y = 180};chessboardSquare E7 ={.x = 600,.y = 180};chessboardSquare F7 = {.x = 690,.y = 180};chessboardSquare G7 = {.x = 780,.y = 180};chessboardSquare H7 = {.x = RIGHT_SIDE+1,.y = 180};
chessboardSquare A6 = {.x = LEFT_SIDE+1,.y = 270};chessboardSquare B6 = {.x = 330,.y = 270};chessboardSquare C6 = {.x = 420,.y = 270};chessboardSquare D6 = {.x = 510,.y = 370};chessboardSquare E6 ={.x = 600,.y = 270};chessboardSquare F6 = {.x = 690,.y = 270};chessboardSquare G6 = {.x = 780,.y = 270};chessboardSquare H6 = {.x = RIGHT_SIDE+1,.y = 270};
chessboardSquare A5 = {.x = LEFT_SIDE+1,.y = 360};chessboardSquare B5 = {.x = 330,.y = 360};chessboardSquare C5 = {.x = 420,.y = 360};chessboardSquare D5 = {.x = 510,.y = 360};chessboardSquare E5 ={.x = 600,.y = 360};chessboardSquare F5 = {.x = 690,.y = 360};chessboardSquare G5 = {.x = 780,.y = 360};chessboardSquare H5 = {.x = RIGHT_SIDE+1,.y = 360};
chessboardSquare A4 = {.x = LEFT_SIDE+1,.y = 450};chessboardSquare B4 = {.x = 330,.y = 450};chessboardSquare C4 = {.x = 420,.y = 450};chessboardSquare D4 = {.x = 510,.y = 450};chessboardSquare E4 ={.x = 600,.y = 450};chessboardSquare F4 = {.x = 690,.y = 450};chessboardSquare G4 = {.x = 780,.y = 450};chessboardSquare H4 = {.x = RIGHT_SIDE+1,.y = 450};
chessboardSquare A3 = {.x = LEFT_SIDE+1,.y = 540};chessboardSquare B3 = {.x = 330,.y = 540};chessboardSquare C3 = {.x = 420,.y = 540};chessboardSquare D3 = {.x = 510,.y = 540};chessboardSquare E3 ={.x = 600,.y = 540};chessboardSquare F3 = {.x = 690,.y = 540};chessboardSquare G3 = {.x = 780,.y = 540};chessboardSquare H3 = {.x = RIGHT_SIDE+1,.y = 540};
chessboardSquare A2 = {.x = LEFT_SIDE+1,.y = 630};chessboardSquare B2 = {.x = 330,.y = 630};chessboardSquare C2= {.x = 420,.y = 630};chessboardSquare D2= {.x = 510,.y = 630};chessboardSquare E2= {.x = 600,.y = 630};chessboardSquare F2= {.x = 690,.y = 630};chessboardSquare G2= {.x = 780,.y = 630};chessboardSquare H2= {.x = LEFT_SIDE+1,.y = 630};
chessboardSquare A1 = {.x = LEFT_SIDE+1,.y = 720};chessboardSquare B1= {.x = 330,.y = 720};chessboardSquare C1= {.x = 420,.y = 720};chessboardSquare D1= {.x = 510,.y = 720};chessboardSquare E1= {.x = 600,.y = 720};chessboardSquare F1= {.x = 690,.y = 720};chessboardSquare G1= {.x = 780,.y = 720};chessboardSquare H1= {.x = RIGHT_SIDE+1,.y = 720};


chessboardSquare selectedSquare(int x,int y) {
    if (x>=LEFT_SIDE && x < 330 ){
        if (y <= BOTTOM_SIDE && y > 720) {
            return A1;
        }
        if (y <= 720 && y > 630) {
            return A2;
        }
        if (y <= 630 && y > 540) {
            return A3;
        }
        if (y <= 540 && y > 450) {
            return A4;
        }
        if (y <= 450 && y > 360) {
            return A5;
        }
        if (y <= 360 && y > 270) {
            return A6;
        }
        if (y <= 270 && y > 180) {
            return A7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return A8;
        }
    }else if (x>=330 && x < 420) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return B1;
        }
        if (y <= 720 && y > 630) {
            return B2;
        }
        if (y <= 630 && y > 540) {
            return B3;
        }
        if (y <= 540 && y > 450) {
            return B4;
        }
        if (y <= 450 && y > 360) {
            return B5;
        }
        if (y <= 360 && y > 270) {
            return B6;
        }
        if (y <= 270 && y > 180) {
            return B7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return B8;
        }
    }else if (x>=420 && x < 510) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return C1;
        }
        if (y <= 720 && y > 630) {
            return C2;
        }
        if (y <= 630 && y > 540) {
            return C3;
        }
        if (y <= 540 && y > 450) {
            return C4;
        }
        if (y <= 450 && y > 360) {
            return C5;
        }
        if (y <= 360 && y > 270) {
            return C6;
        }
        if (y <= 270 && y > 180) {
            return C7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return C8;
        }
    }else if (x>=510 && x < 600) {
       if (y <= BOTTOM_SIDE && y > 720) {
            return D1;
        }
        if (y <= 720 && y > 630) {
            return D2;
        }
        if (y <= 630 && y > 540) {
            return D3;
        }
        if (y <= 540 && y > 450) {
            return D4;
        }
        if (y <= 450 && y > 360) {
            return D5;
        }
        if (y <= 360 && y > 270) {
            return D6;
        }
        if (y <= 270 && y > 180) {
            return D7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return D8;
        }
    }else if (x>=600 && x < 690) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return E1;
        }
        if (y <= 720 && y > 630) {
            return E2;
        }
        if (y <= 630 && y > 540) {
            return E3;
        }
        if (y <= 540 && y > 450) {
            return E4;
        }
        if (y <= 450 && y > 360) {
            return E5;
        }
        if (y <= 360 && y > 270) {
            return E6;
        }
        if (y <= 270 && y > 180) {
            return E7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return E8;
        }
    }else if (x>=690 && x < 780) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return F1;
        }
        if (y <= 720 && y > 630) {
            return F2;
        }
        if (y <= 630 && y > 540) {
            return F3;
        }
        if (y <= 540 && y > 450) {
            return F4;
        }
        if (y <= 450 && y > 360) {
            return F5;
        }
        if (y <= 360 && y > 270) {
            return F6;
        }
        if (y <= 270 && y > 180) {
            return F7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return F8;
        }
    }else if (x>=780 && x < 870) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return G1;
        }
        if (y <= 720 && y > 630) {
            return G2;
        }
        if (y <= 630 && y > 540) {
            return G3;
        }
        if (y <= 540 && y > 450) {
            return G4;
        }
        if (y <= 450 && y > 360) {
            return G5;
        }
        if (y <= 360 && y > 270) {
            return G6;
        }
        if (y <= 270 && y > 180) {
            return G7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return G8;
        }
    }else if (x>=870 && x < RIGHT_SIDE) {
        if (y <= BOTTOM_SIDE && y > 720) {
            return H1;
        }
        if (y <= 720 && y > 630) {
            return H2;
        }
        if (y <= 630 && y > 540) {
            return H3;
        }
        if (y <= 540 && y > 450) {
            return H4;
        }
        if (y <= 450 && y > 360) {
            return H5;
        }
        if (y <= 360 && y > 270) {
            return H6;
        }
        if (y <= 270 && y > 180) {
            return H7;
        }
        if (y <= 180 && y > TOP_SIDE) {
            return H8;
        }
    }else {
        chessboardSquare ERROR = {.x = 0,.y = 0};
        printf("Erreur Coordonnées INVALIDE\n");
        return ERROR;
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
