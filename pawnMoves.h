#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>


#define LEFT_SIDE 239
#define RIGHT_SIDE 959
#define TOP_SIDE 89
#define BOTTOM_SIDE 809

//-----------BASE MOVES----------------//
void moveUp (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    if (pawn->CurrentPosition.y -90 > TOP_SIDE) {
        pawn->CurrentPosition.y = pawn->CurrentPosition.y - 90;
        pawn->pawn = createPawn(window,render,pawn);
    }else{
        pawn->pawn = createPawn(window,render,pawn);
    }
}

void moveDown (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    if (pawn->CurrentPosition.y + 90 < BOTTOM_SIDE) {
        pawn->CurrentPosition.y = pawn->CurrentPosition.y + 90;
        pawn->pawn = createPawn(window,render,pawn);
    }else {
        pawn->pawn = createPawn(window,render,pawn);
    }
    
    
}

void moveLeft (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    if (pawn->CurrentPosition.x - 90 > LEFT_SIDE) {
        pawn->CurrentPosition.x = pawn->CurrentPosition.x - 90;
        pawn->pawn = createPawn(window,render,pawn);
    }else{
        pawn->pawn = createPawn(window,render,pawn);
    }
}

void moveRight (pawn* pawn,SDL_Window *window,SDL_Renderer *render) {
    if (pawn->CurrentPosition.x + 90 < RIGHT_SIDE) {
        pawn->CurrentPosition.x = pawn->CurrentPosition.x + 90;
        pawn->pawn = createPawn(window,render,pawn);
    }else{
        pawn->pawn = createPawn(window,render,pawn);
    }
}

//---------------PAWN MOVES------------------//
