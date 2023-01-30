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

//-----------------BOARD MANAGEMENT---------------//

chessboardSquare allowedMoves[27];

chessboardSquare A8 = {.x = LEFT_SIDE+1,.y = TOP_SIDE+1};chessboardSquare B8 = {.x = 330,.y = TOP_SIDE+1};chessboardSquare C8 = {.x = 420,.y = TOP_SIDE+1};chessboardSquare D8= {.x = 510,.y = TOP_SIDE+1} ;chessboardSquare E8 ={.x = 600,.y = TOP_SIDE+1};chessboardSquare F8 = {.x = 690,.y = TOP_SIDE+1};chessboardSquare G8 = {.x = 780,.y = TOP_SIDE+1};chessboardSquare H8 = {.x = 870,.y = TOP_SIDE +1};
chessboardSquare A7 = {.x = LEFT_SIDE+1,.y = 180};chessboardSquare B7 = {.x = 330,.y = 180};chessboardSquare C7 = {.x = 420,.y = 180};chessboardSquare D7 = {.x = 510,.y = 180};chessboardSquare E7 ={.x = 600,.y = 180};chessboardSquare F7 = {.x = 690,.y = 180};chessboardSquare G7 = {.x = 780,.y = 180};chessboardSquare H7 = {.x = 870,.y = 180};
chessboardSquare A6 = {.x = LEFT_SIDE+1,.y = 270};chessboardSquare B6 = {.x = 330,.y = 270};chessboardSquare C6 = {.x = 420,.y = 270};chessboardSquare D6 = {.x = 510,.y = 370};chessboardSquare E6 ={.x = 600,.y = 270};chessboardSquare F6 = {.x = 690,.y = 270};chessboardSquare G6 = {.x = 780,.y = 270};chessboardSquare H6 = {.x = 870,.y = 270};
chessboardSquare A5 = {.x = LEFT_SIDE+1,.y = 360};chessboardSquare B5 = {.x = 330,.y = 360};chessboardSquare C5 = {.x = 420,.y = 360};chessboardSquare D5 = {.x = 510,.y = 360};chessboardSquare E5 ={.x = 600,.y = 360};chessboardSquare F5 = {.x = 690,.y = 360};chessboardSquare G5 = {.x = 780,.y = 360};chessboardSquare H5 = {.x = 870,.y = 360};
chessboardSquare A4 = {.x = LEFT_SIDE+1,.y = 450};chessboardSquare B4 = {.x = 330,.y = 450};chessboardSquare C4 = {.x = 420,.y = 450};chessboardSquare D4 = {.x = 510,.y = 450};chessboardSquare E4 ={.x = 600,.y = 450};chessboardSquare F4 = {.x = 690,.y = 450};chessboardSquare G4 = {.x = 780,.y = 450};chessboardSquare H4 = {.x = 870,.y = 450};
chessboardSquare A3 = {.x = LEFT_SIDE+1,.y = 540};chessboardSquare B3 = {.x = 330,.y = 540};chessboardSquare C3 = {.x = 420,.y = 540};chessboardSquare D3 = {.x = 510,.y = 540};chessboardSquare E3 ={.x = 600,.y = 540};chessboardSquare F3 = {.x = 690,.y = 540};chessboardSquare G3 = {.x = 780,.y = 540};chessboardSquare H3 = {.x = 870,.y = 540};
chessboardSquare A2 = {.x = LEFT_SIDE+1,.y = 630};chessboardSquare B2 = {.x = 330,.y = 630};chessboardSquare C2= {.x = 420,.y = 630};chessboardSquare D2= {.x = 510,.y = 630};chessboardSquare E2= {.x = 600,.y = 630};chessboardSquare F2= {.x = 690,.y = 630};chessboardSquare G2= {.x = 780,.y = 630};chessboardSquare H2= {.x = 870,.y = 630};
chessboardSquare A1 = {.x = LEFT_SIDE+1,.y = 720};chessboardSquare B1= {.x = 330,.y = 720};chessboardSquare C1= {.x = 420,.y = 720};chessboardSquare D1= {.x = 510,.y = 720};chessboardSquare E1= {.x = 600,.y = 720};chessboardSquare F1= {.x = 690,.y = 720};chessboardSquare G1= {.x = 780,.y = 720};chessboardSquare H1= {.x = 870,.y = 720};


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
            return 0;
        }
    }
    
    
    return 1;
}
//---------------PAWN MOVES------------------//



void knightAllowedMoves(pawn knight,bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0,.y = 0};
    SDL_Rect displayer;
    displayer.h = 89;
    displayer.w = 89;
    pawn baseKnight = knight;
    displayAll(window,render);
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);

    // MOVE 1
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int j = 0; j < 8; j++) {
        knight.CurrentPosition.x += dx[j] * 90;
        knight.CurrentPosition.y += dy[j] * 90;
        if (isValidMove(knight,colorPlaying)) {
            displayer.x = knight.CurrentPosition.x;
            displayer.y = knight.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x, displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render, &displayer);
        }
        knight.CurrentPosition.x = baseKnight.CurrentPosition.x;
        knight.CurrentPosition.y = baseKnight.CurrentPosition.y;
    }
    // Afficher les mouvements possibles
    SDL_RenderPresent(render);

}
void queenAllowedMoves(pawn queen,bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    pawn baseQueen = queen;
    int move = 90;
    int i = 0;
    chessboardSquare allowedMoveFiller = {.x = 0,.y = 0};
    SDL_Rect displayer;
    displayer.h = 89;
    displayer.w = 89;
    displayAll(window,render);
    SDL_SetRenderDrawColor(render, 150, 0, 0, 0);
    //Move UP
    for (int j = 1; queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    
    //Move Down
    for (int j = 1; queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //Move Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE; j++) {
        queen.CurrentPosition.x += move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //Move Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    //MOVE UP - RIGHT
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE UP - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y >= TOP_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y -= move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Left
    for (int j = 1; queen.CurrentPosition.x >= LEFT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x -= move;
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;
    //MOVE Down - Right
    for (int j = 1; queen.CurrentPosition.x <= RIGHT_SIDE && queen.CurrentPosition.y < BOTTOM_SIDE; j++) {
        queen.CurrentPosition.x += move;
        queen.CurrentPosition.y += move;
        if (isValidMove(queen,colorPlaying)) {
            displayer.x = queen.CurrentPosition.x;
            displayer.y = queen.CurrentPosition.y;
            allowedMoveFiller = selectedSquare(displayer.x,displayer.y+1);
            allowedMoves[i] = allowedMoveFiller;
            i++;
            SDL_RenderFillRect(render,&displayer);
        }
    }
    queen.CurrentPosition.x = baseQueen.CurrentPosition.x;
    queen.CurrentPosition.y = baseQueen.CurrentPosition.y;

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
        break;
    case 3:
        //bishopAllowedMoves(selectedPawn,window,render);
        break;
    case 4:
        //rookAllowedMoves(selectedPawn,window,render);
        break;
    case 5 :
        queenAllowedMoves(selectedPawn,colorPlaying,window,render);
        break;
    case 6:
        //kingAllowedMoves(selectedPawn,window,render);
        break;
    case 7:
        //pawnAllowedMoves(selectedPawn,window,render);
        break;
    case 8:
        knightAllowedMoves(selectedPawn,colorPlaying,window,render);
        break;
    case 9:
        //bishopAllowedMoves(selectedPawn,window,render);
        break;
    case 10:
        //rookAllowedMoves(selectedPawn,window,render);
        break;
    case 11:
        queenAllowedMoves(selectedPawn,colorPlaying,window,render);
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
    for (int i = 0; i < 27; i++) {
        allowedMoves[i].x = -1;
        allowedMoves[i].y = -1;
    }
}