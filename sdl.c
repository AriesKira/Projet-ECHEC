#include "checkMate.h"

#define Window_HEIGHT 900
#define Window_WIDTH 1400



int main(int argc, char** argv) {
    SDL_Window *window =NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture *chessBoard= NULL;
    SDL_Texture *legend = NULL;
    SDL_Texture * check = NULL;
    bool pawnWasSelected = false;
    bool colorPlaying = false;
    int checkMate = 0;
    
    int chosenPawn;
    int targetPawn;

    pawnArray = malloc(sizeof(pawn)*5);
    pawn LWknight;
    pawn RWknight;
    pawn LBknight;
    pawn RBknight;
    pawn Wqueen;
    pawn Bqueen;
    pawn Bking;
    pawn Wking;
    pawn LWrook;
    pawn RWrook;
    pawn LBrook;
    pawn RBrook;
    pawn LWbishop;
    pawn RWbishop;
    pawn LBbishop;
    pawn RBbishop;
    pawn Wpawn1;
    pawn Wpawn2;
    pawn Wpawn3;
    pawn Wpawn4;
    pawn Wpawn5;
    pawn Wpawn6;
    pawn Wpawn7;
    pawn Wpawn8;
    pawn Bpawn1;
    pawn Bpawn2;
    pawn Bpawn3;
    pawn Bpawn4;
    pawn Bpawn5;
    pawn Bpawn6;
    pawn Bpawn7;
    pawn Bpawn8;

    if(SDL_Init(SDL_INIT_VIDEO) !=0 ) {
        SDL_ExitWithError("Erreur initialisation SDL\n");
        return 0;

    }

    if (SDL_CreateWindowAndRenderer(Window_WIDTH,Window_HEIGHT,0,&window,&render)!=0) {
        SDL_ExitWithError("Erreur initialisation fenêtre + render\n");
        return 0;
    }
    
    
    chessBoard = createChessboard(window,render);
    if (chessBoard == NULL) {
        SDL_ExitWithError("Erreur création echéquier\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        return 0;
    }
    legend = createLegend(window,render);
    if (legend == NULL) {
        SDL_ExitWithError("Erreur création de la légende\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        return 0;
    }
    pawnFiller(&LWknight,"knight",0,330,720,window,render);
    pawnFiller(&RWknight,"knight",0,780,720,window,render);
    pawnFiller(&LBknight,"knight",1,330,90,window,render);
    pawnFiller(&RBknight,"knight",1,780,90,window,render);
    pawnFiller(&Wqueen,"queen",0,510,720,window,render);
    pawnFiller(&Bqueen,"queen",1,510,90,window,render);
    pawnFiller(&Wking,"king",0,600,720,window,render);
    pawnFiller(&Bking,"king",1,600,90,window,render);
    pawnFiller(&LWrook,"rook",0,240,720,window,render);
    pawnFiller(&RWrook,"rook",0,870,720,window,render);
    pawnFiller(&LBrook,"rook",1,240,90,window,render);
    pawnFiller(&RBrook,"rook",1,870,90,window,render);
    pawnFiller(&LWbishop,"bishop",0,420,720,window,render);
    pawnFiller(&RWbishop,"bishop",0,690,720,window,render);
    pawnFiller(&LBbishop,"bishop",1,420,90,window,render);
    pawnFiller(&RBbishop,"bishop",1,690,90,window,render);
    pawnFiller(&Wpawn1,"pawn",0,240,630,window,render);
    pawnFiller(&Wpawn2,"pawn",0,330,630,window,render);
    pawnFiller(&Wpawn3,"pawn",0,420,630,window,render);
    pawnFiller(&Wpawn4,"pawn",0,510,630,window,render);
    pawnFiller(&Wpawn5,"pawn",0,600,630,window,render);
    pawnFiller(&Wpawn6,"pawn",0,690,630,window,render);
    pawnFiller(&Wpawn7,"pawn",0,780,630,window,render);
    pawnFiller(&Wpawn8,"pawn",0,870,630,window,render);
    pawnFiller(&Bpawn1,"pawn",1,240,180,window,render);
    pawnFiller(&Bpawn2,"pawn",1,330,180,window,render);
    pawnFiller(&Bpawn3,"pawn",1,420,180,window,render);
    pawnFiller(&Bpawn4,"pawn",1,510,180,window,render);
    pawnFiller(&Bpawn5,"pawn",1,600,180,window,render);
    pawnFiller(&Bpawn6,"pawn",1,690,180,window,render);
    pawnFiller(&Bpawn7,"pawn",1,780,180,window,render);
    pawnFiller(&Bpawn8,"pawn",1,870,180,window,render);



    pawnArray[0] = &LWknight;
    pawnArray[1] = &RWknight;
    pawnArray[2] = &LBknight;
    pawnArray[3] = &RBknight;
    pawnArray[4] = &Wqueen;
    pawnArray[5] = &Bqueen;
    pawnArray[6] = &Wking;
    pawnArray[7] = &Bking;
    pawnArray[8] = &LWrook;
    pawnArray[9] = &RWrook;
    pawnArray[10] = &LBrook;
    pawnArray[11] = &RBrook;
    pawnArray[12] = &LWbishop;
    pawnArray[13] = &RWbishop;
    pawnArray[14] = &LBbishop;
    pawnArray[15] = &RBbishop;
    pawnArray[16] = &Wpawn1;
    pawnArray[17] = &Wpawn2;
    pawnArray[18] = &Wpawn3;
    pawnArray[19] = &Wpawn4;
    pawnArray[20] = &Wpawn5;
    pawnArray[21] = &Wpawn6;
    pawnArray[22] = &Wpawn7;
    pawnArray[23] = &Wpawn8;
    pawnArray[24] = &Bpawn1;
    pawnArray[25] = &Bpawn2;
    pawnArray[26] = &Bpawn3;
    pawnArray[27] = &Bpawn4;
    pawnArray[28] = &Bpawn5;
    pawnArray[29] = &Bpawn6;
    pawnArray[30] = &Bpawn7;
    pawnArray[31] = &Bpawn8;


    
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
                        pawn boardCopy[sizeOfPawnArray];
                        copyBoard(boardCopy);
                            if (pawnWasSelected) {
                                chessboardSquare chosenMove = selectedSquare(event.button.x,event.button.y);
                                printf("%d / %d\n",chosenMove.x,chosenMove.y);
                                if (isAllowedMove(chosenMove)==1) {
                                    if (selectedPawn(boardCopy, chosenMove,colorPlaying) == -2) {
                                        targetPawn = selectedPawn(boardCopy, chosenMove,!colorPlaying);
                                        eatPawn(targetPawn);
                                    }
                                    
                                    movePawn(pawnArray[chosenPawn],chosenMove,window,render);
                                    movePawn(&boardCopy[chosenPawn], chosenMove, window, render);
                                    emptyAllowedMoves();
                                    if ((checkMate = isCheck(boardCopy,colorPlaying,false,window,render))== 2) {
                                        displayWinner(colorPlaying,window,render);
                                        SDL_Delay(5000);
                                        programLaunched = SDL_FALSE;
                                        break;
                                    }
                                    colorPlaying = !colorPlaying;
                                }
                                displayAll(colorPlaying,checkMate,window,render);
                                emptyAllowedMoves();
                                
                                pawnWasSelected = false;
                            } else {
                                chessboardSquare chosenSquare;
                                printf("%d.%d\n",event.button.x,event.button.y);
                                chosenSquare = selectedSquare(event.button.x,event.button.y);
                                printf("%d / %d\n",chosenSquare.x, chosenSquare.y);
                                chosenPawn = selectedPawn(boardCopy, chosenSquare, colorPlaying);
                                if (chosenPawn == -1 || chosenPawn == -2) {
                                    continue;
                                }else{
                                    pawn tmpPawn = copyPawn(boardCopy, chosenPawn);
                                    printf("%s\n",pawnArray[chosenPawn]->type);
                                    diplayAllowedMoves(tmpPawn,colorPlaying,checkMate,window,render);
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
    
    
    

    SDL_DestroyTexture(chessBoard);
    SDL_DestroyRenderer(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}

