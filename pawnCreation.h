#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>


typedef struct pawn pawn;
struct pawn {
    SDL_Rect basePosition;
    SDL_Rect CurrentPosition;
    SDL_Texture* pawn;
    char* type;
    int teamColor;
};

pawn ** pawnArray;
pawn ERROR = {.type = "ERROR"};

SDL_Texture* createFuncToUse(pawn* pawn,SDL_Window *window,SDL_Renderer *render);
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

//------------------PAWN CREATION--------------------------------------------//
void pawnFiller(pawn* pawn,char* pawnType,int color,int x,int y,SDL_Window *window,SDL_Renderer *render){
    pawn->basePosition.x = x;
    pawn->CurrentPosition.x = x;
    pawn->basePosition.y = y;
    pawn->CurrentPosition.y = y;
    pawn->teamColor = color;
    pawn->type = pawnType;
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

void displayAll(SDL_Window* window,SDL_Renderer* render) {

    SDL_RenderClear(render);
    createChessboard(window,render);
    for (int i = 0; i < sizeof(pawnArray)/2; i++) {
        createPawn(window,render,pawnArray[i]);
    }
    SDL_RenderPresent(render);
}
