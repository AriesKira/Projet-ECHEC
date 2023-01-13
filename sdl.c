#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include "pawnCreation.h"
#include "pawnMoves.h"

#define Window_HEIGHT 900
#define Window_WIDTH 1300

pawn * pawnArray;


int main(int argc, char** argv) {
    SDL_Window *window =NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Texture* chessboard = NULL;
    
    pawnArray = malloc(sizeof(pawn)*32);
    pawn LWknight;
    pawn RWknight;
    pawn Wqueen;
    pawn Bqueen;
    

    pawnArray[0] = LWknight;
    pawnArray[1] = RWknight;
    pawnArray[2] = Wqueen;
    pawnArray[3] = Bqueen;

    if(SDL_Init(SDL_INIT_VIDEO) !=0 ) {
        SDL_ExitWithError("Erreur initialisation SDL\n");
        return 0;
    }

    if (SDL_CreateWindowAndRenderer(Window_WIDTH,Window_HEIGHT,0,&window,&rendu)!=0) {
        SDL_ExitWithError("Erreur initialisation fenêtre + rendu\n");
        return 0;
    }
    
    
    chessboard = createChessboard(window,rendu);
    if (chessboard == NULL) {
        SDL_ExitWithError("Erreur création echéquier\n");
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(window);
        return 0;
    }
    pawnFiller(&LWknight,"knight",0,330,720,window,rendu);
    pawnFiller(&RWknight,"knight",0,780,720,window,rendu);
    pawnFiller(&Wqueen,"queen",0,510,720,window,rendu);
    pawnFiller(&Bqueen,"queen",1,510,90,window,rendu);

    SDL_RenderPresent(rendu);
    SDL_bool programLaunched = SDL_TRUE;

    while (programLaunched) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.clicks) {
                    case SDL_BUTTON_LEFT:
                        printf("%d.%d\n",event.button.x,event.button.y);
                        continue;
                    
                    default:
                        break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    
                        case SDLK_ESCAPE:
                            printf("fin du programme");
                            programLaunched = SDL_FALSE;
                            break;
                        case SDLK_z:
                            SDL_RenderClear(rendu);
                            createChessboard(window,rendu);
                            moveUp(&LWknight,window,rendu);
                            SDL_RenderPresent(rendu);
                            break;
                        case SDLK_d:
                            SDL_RenderClear(rendu);
                            createChessboard(window,rendu);
                            moveRight(&LWknight,window,rendu);
                            SDL_RenderPresent(rendu);
                            break;
                        case SDLK_s:
                            SDL_RenderClear(rendu);
                            createChessboard(window,rendu);
                            moveDown(&LWknight,window,rendu);
                            SDL_RenderPresent(rendu);
                            break;
                        case SDLK_q:
                            SDL_RenderClear(rendu);
                            createChessboard(window,rendu);
                            moveLeft(&LWknight,window,rendu);
                            SDL_RenderPresent(rendu);
                            break;
                        default:
                            
                            
                            continue;
                        }
                    break;
                case SDL_QUIT :
                    programLaunched = SDL_FALSE;
                    break;
                
                default:
                    break;
                }
        }
        
    }
    
    
    

    SDL_DestroyTexture(chessboard);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}

