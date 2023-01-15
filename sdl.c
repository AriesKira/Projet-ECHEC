#include "pawnMoves.h"

#define Window_HEIGHT 900
#define Window_WIDTH 1300



int main(int argc, char** argv) {
    SDL_Window *window =NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Texture* chessboard = NULL;
    
    pawnArray = malloc(sizeof(pawn)*4);
    pawn LWknight;
    pawn RWknight;
    pawn Wqueen;
    pawn Bqueen;
    
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

    pawnArray[0] = &LWknight;
    pawnArray[1] = &RWknight;
    pawnArray[2] = &Wqueen;
    pawnArray[3] = &Bqueen;

    SDL_RenderPresent(rendu);
    SDL_bool programLaunched = SDL_TRUE;

    while (programLaunched) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.clicks) {
                    case SDL_BUTTON_LEFT: {
                        chessboardSquare chosenSquare;
                        printf("%d.%d\n",event.button.x,event.button.y);
                        chosenSquare = selectedSquare(event.button.x,event.button.y);
                        printf("%d / %d\n",chosenSquare.x, chosenSquare.y);
                        pawn* chosenPawn = selectedPawn(chosenSquare);   
                        if (strcmp(chosenPawn->type,"ERROR") == 0) {
                            continue;
                        }else{
                            pawn tmpPawn = {.CurrentPosition.x = chosenPawn->CurrentPosition.x,.CurrentPosition.y = chosenPawn->CurrentPosition.y};
                            printf("%s\n",chosenPawn->type);
                            if (strcmp(chosenPawn->type,"knight")==0) {
                                knghtAllowedMoves(tmpPawn,window,rendu);
                            }
                            
                        }
                        
                        continue;
                    }
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

