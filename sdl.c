#include "pawnMoves.h"

#define Window_HEIGHT 900
#define Window_WIDTH 1300



int main(int argc, char** argv) {
    SDL_Window *window =NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture* chessboard = NULL;
    bool pawnWasSelected = false;
    bool colorPlaying = false;
    
    int chosenPawn;
    int targetPawn;

    pawnArray = malloc(sizeof(pawn)*4);
    pawn LWknight;
    pawn RWknight;
    pawn Wqueen;
    pawn Bqueen;
    
    if(SDL_Init(SDL_INIT_VIDEO) !=0 ) {
        SDL_ExitWithError("Erreur initialisation SDL\n");
        return 0;

    }

    if (SDL_CreateWindowAndRenderer(Window_WIDTH,Window_HEIGHT,0,&window,&render)!=0) {
        SDL_ExitWithError("Erreur initialisation fenêtre + render\n");
        return 0;
    }
    
    
    chessboard = createChessboard(window,render);
    if (chessboard == NULL) {
        SDL_ExitWithError("Erreur création echéquier\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        return 0;
    }
    pawnFiller(&LWknight,"knight",0,330,720,window,render);
    pawnFiller(&RWknight,"knight",0,780,720,window,render);
    pawnFiller(&Wqueen,"queen",0,510,720,window,render);
    pawnFiller(&Bqueen,"queen",1,510,90,window,render);

    pawnArray[0] = &LWknight;
    pawnArray[1] = &RWknight;
    pawnArray[2] = &Wqueen;
    pawnArray[3] = &Bqueen;
    generateChessboardSquareArray();

    SDL_RenderPresent(render);
    SDL_bool programLaunched = SDL_TRUE;

    while (programLaunched) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            switch (event.type) {
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.clicks) {
                    case SDL_BUTTON_LEFT: {
                        if (pawnWasSelected) {
                            chessboardSquare chosenMove = selectedSquare(event.button.x,event.button.y);
                            printf("%d / %d\n",chosenMove.x,chosenMove.y);
                            if (isAllowedMove(chosenMove)==1) {
                                if (selectedPawn(chosenMove,colorPlaying) == -2) {
                                    targetPawn = selectedPawn(chosenMove,!colorPlaying);
                                    eatPawn(targetPawn);
                                }
                                
                                movePawn(pawnArray[chosenPawn],chosenMove,window,render);
                                colorPlaying = !colorPlaying;
                            }
                            displayAll(window,render);
                            emptyAllowedMoves();
                            
                            pawnWasSelected = false;
                        }else {
                            chessboardSquare chosenSquare;
                            printf("%d.%d\n",event.button.x,event.button.y);
                            chosenSquare = selectedSquare(event.button.x,event.button.y);
                            printf("%d / %d\n",chosenSquare.x, chosenSquare.y);
                            chosenPawn = selectedPawn(chosenSquare, colorPlaying);
                            if (chosenPawn == -1 || chosenPawn == -2) {
                                continue;
                            }else{
                                pawn tmpPawn = {.CurrentPosition.x = pawnArray[chosenPawn]->CurrentPosition.x,.CurrentPosition.y = pawnArray[chosenPawn]->CurrentPosition.y,.teamColor = pawnArray[chosenPawn]->teamColor,.type = pawnArray[chosenPawn]->type};
                                printf("%s\n",pawnArray[chosenPawn]->type);
                                diplayAllowedMoves(tmpPawn,colorPlaying,window,render);
                                pawnWasSelected = true;
                            }
                            continue;
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
    SDL_DestroyRenderer(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}

