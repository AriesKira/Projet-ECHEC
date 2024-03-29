#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>

#define LEFT_SIDE 239
#define RIGHT_SIDE 959
#define TOP_SIDE 89
#define BOTTOM_SIDE 809
#define CELL_SIZE 90
#define NB_CELL_PER_SIDE 8
#define sizeOfPawnArray 32
#define MAX_PAWN_MOVES 27

typedef struct pawn pawn;
struct pawn {
    SDL_Rect basePosition;
    SDL_Rect CurrentPosition;
    SDL_Texture* pawn;
    char* type;
    int teamColor;
    bool alive;
};

pawn ** pawnArray;

void funcNumb (char* pawnType,int pawnColor,int* value);
void SDL_ExitWithError(const char* msg);
SDL_Texture* createChessboard(SDL_Window *window,SDL_Renderer *render);
SDL_Texture* createPawn(SDL_Window *window,SDL_Renderer *render,pawn* pawn);
char* pawnNameAndColor(pawn* pawn);

//-------TEXTURES-------------------------///
void SDL_ExitWithError(const char* msg) {
    SDL_Log("ERREUR : %s > %s\n",msg,SDL_GetError());
    SDL_Quit();
    printf("%s\n",msg);
    exit(EXIT_FAILURE);
}
SDL_Texture* createChessboard(SDL_Window *window,SDL_Renderer *render) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    image = SDL_LoadBMP("./images/chessboard.bmp");
    
    if (image == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Image");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(render,image);

    if (texture == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Texture\n");
        return 0;
    }

    SDL_FreeSurface(image);
    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur chargement de la texture\n");
        return 0;
    }
    
    rectangle.x = 200;
    rectangle.y = 50;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur affichage de la texture\n");
        return 0;
    }

    return texture;
}
SDL_Texture* createLegend(SDL_Window *window,SDL_Renderer *render) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    image = SDL_LoadBMP("./images/legend.bmp");

    if (image == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Image");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(render,image);

    if (texture == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Texture\n");
        return 0;
    }

    SDL_FreeSurface(image);
    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur chargement de la texture\n");
        return 0;
    }

    rectangle.x = 1000;
    rectangle.y = 200;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur affichage de la texture\n");
        return 0;
    }

    return texture;
}

SDL_Texture* createPawn(SDL_Window *window,SDL_Renderer *render,pawn* pawn) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
   
    char* fullPath = pawnNameAndColor(pawn);
    

    image = SDL_LoadBMP(fullPath);

    if (image == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Image");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(render,image);

    if (texture == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Texture\n");
        return 0;
    }

    SDL_FreeSurface(image);

    if(SDL_QueryTexture(texture,NULL,NULL,&pawn->CurrentPosition.w,&pawn->CurrentPosition.h)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur chargement de la texture\n");
        return 0;
    }


    if(SDL_RenderCopy(render,texture,NULL,&pawn->CurrentPosition)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur affichage de la texture\n");
        return 0;
    }

    return texture;
}
SDL_Texture* createWinner(bool colorWinning,SDL_Window *window,SDL_Renderer *render) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    if (!colorWinning) {
        image = SDL_LoadBMP("./images/whiteWinner.bmp");
    } else {
        image = SDL_LoadBMP("./images/blackWinner.bmp");
    }


    if (image == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Image");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(render,image);

    if (texture == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Texture\n");
        return 0;
    }

    SDL_FreeSurface(image);
    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur chargement de la texture\n");
        return 0;
    }

    rectangle.x = 400;
    rectangle.y = 400;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur affichage de la texture\n");
        return 0;
    }

    return texture;
}
SDL_Texture* createCheck(bool colorInCheck,SDL_Window *window,SDL_Renderer *render) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    if (colorInCheck) {
        image = SDL_LoadBMP("./images/whiteCheck.bmp");
    } else {
        image = SDL_LoadBMP("./images/blackCheck.bmp");
    }


    if (image == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Image");
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(render,image);

    if (texture == NULL) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur Texture\n");
        return 0;
    }

    SDL_FreeSurface(image);
    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur chargement de la texture\n");
        return 0;
    }

    rectangle.x = 445;
    rectangle.y = 0;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle)!=0) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Erreur affichage de la texture\n");
        return 0;
    }

    return texture;
}
//------------------PAWN CREATION--------------------------------------------//
void pawnFiller(pawn* pawn,char* pawnType,int color,int x,int y,SDL_Window *window,SDL_Renderer *render){
    pawn->basePosition.x = x;
    pawn->CurrentPosition.x = x;
    pawn->basePosition.y = y;
    pawn->CurrentPosition.y = y;
    pawn->teamColor = color;
    pawn->type = pawnType;
    pawn->alive = true;
    pawn->pawn = createPawn(window,render,pawn);
}

void funcNumb (char* pawnType,int pawnColor,int* value) {
    if (strcmp(pawnType,"pawn")== 0) {
        if (pawnColor == 0) {
            *value =  1;
        }else if (pawnColor == 1) {
            *value = 7;
        }
    }
    if (strcmp(pawnType,"knight")== 0) {
        if (pawnColor == 0) {
            *value = 2;
        }else if (pawnColor == 1) {
            *value = 8;
        }
    }
    if (strcmp(pawnType,"bishop")== 0) {
        if (pawnColor == 0) {
            *value = 3;
        }else if (pawnColor == 1) {
            *value = 9;
        }
    }
    if (strcmp(pawnType,"rook")== 0) {
        if (pawnColor == 0) {
            *value = 4;
        }else if (pawnColor == 1) {
            *value = 10;
        }
    }
    if (strcmp(pawnType,"queen")== 0) {
        if (pawnColor == 0) {
            *value = 5;
        }else if (pawnColor == 1) {
            *value = 11;
        }
    }
    if (strcmp(pawnType,"king")== 0) {
        if (pawnColor == 0) {
            *value = 6;
        }else if (pawnColor == 1) {
            *value = 12;
        }
    }
}

char* pawnNameAndColor(pawn* pawn) {
    int value;
    funcNumb(pawn->type,pawn->teamColor, &value);
    switch (value) {
    case 1:
        return "./images/Wpawn.bmp";
        break;
     case 2:
        return "./images/Wknight.bmp";
        break;
    case 3:
        return "./images/Wbishop.bmp";
        break;
    case 4:
        return "./images/Wrook.bmp";
        break;
    case 5:
        return "./images/Wqueen.bmp";
        break;
    case 6:
        return "./images/Wking.bmp";
        break;
    case 7:
        return "./images/Bpawn.bmp";
        break;
    case 8:
        return "./images/Bknight.bmp";
        break;
    case 9:
        return "./images/Bbishop.bmp";
        break;
    case 10:
        return "./images/Brook.bmp";
        break;
    case 11:
        return "./images/Bqueen.bmp";
        break;
    case 12:
        return "./images/Bking.bmp";
        break;
    default:
        printf("Pion introuvable\n");
        return 0;
        break;
    }
}

void copyBoard(pawn* boardToCopyTo) {
    for (int pawnIndex = 0; pawnIndex < sizeOfPawnArray ; ++pawnIndex) {
        pawn p = {.CurrentPosition.x = pawnArray[pawnIndex]->CurrentPosition.x,.CurrentPosition.y = pawnArray[pawnIndex]->CurrentPosition.y,.teamColor = pawnArray[pawnIndex]->teamColor,.type = pawnArray[pawnIndex]->type,.basePosition.x = pawnArray[pawnIndex]->basePosition.x,.basePosition.y = pawnArray[pawnIndex]->basePosition.y,.alive = pawnArray[pawnIndex]->alive};
        boardToCopyTo[pawnIndex] = p;
    }
}

void displayAll(bool colorPlaying,bool isInCheck,SDL_Window* window,SDL_Renderer* render) {

    SDL_RenderClear(render);
    createChessboard(window,render);
    createLegend(window,render);
    for (int i = 0; i < sizeOfPawnArray; i++) {
        if (pawnArray[i]->alive == false) {
            continue;
        } 
        createPawn(window,render,pawnArray[i]);
    }
    if (isInCheck) {
        SDL_Texture * check = createCheck(!colorPlaying,window,render);
        if (check == NULL) {
            SDL_ExitWithError("Erreur création de l'echec\n");
            SDL_DestroyRenderer(render);
            SDL_DestroyWindow(window);
        }
    }
    SDL_RenderPresent(render);
}

void displayWinner(bool colorPlaying,SDL_Window* window,SDL_Renderer* render) {
    SDL_Texture * winner = NULL;
    SDL_RenderClear(render);
    createChessboard(window,render);
    createLegend(window,render);
    for (int i = 0; i < sizeOfPawnArray; i++) {
        if (pawnArray[i]->alive == false) {
            continue;
        }
        createPawn(window,render,pawnArray[i]);
    }
    winner = createWinner(colorPlaying,window,render);
    if (winner == NULL) {
        SDL_ExitWithError("Erreur création de la légende\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
    }
    SDL_RenderPresent(render);
}