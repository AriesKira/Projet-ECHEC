#include <stdlib.h>
#include <stdio.h>
#include "pawnMoves.h"

#define SIZE_BOARD 8
#define NUMBER_OF_PAWN 32
#define WHITE 0
#define BLACK 1


/*

    FONCTIONS GENERALE DU JEU

*/

void printChessBoard(Pawn pawnArray[NUMBER_OF_PAWN]){
    for (int x = 0; x < SIZE_BOARD; x++) //Affichage console
    {
        printf("----");               
    }
    printf("\n"); 

    for (int x = 0; x < SIZE_BOARD; x++)
    {
        for (int y = 0; y < SIZE_BOARD; y++)
        {
            printf("| ");  //Affichage console

            int hasFoundAPawn = 0; //Affichage console

            for (int i = 0; i < NUMBER_OF_PAWN; i++)
            {
                //Inverser cordX = y et cordY = x pour avoir le plateau dans le bon sens
                if (pawnArray[i].cordX == y && pawnArray[i].cordY == x)
                {
                    printf("%c ", pawnArray[i].boardRepresentation); //Affichage console
                    hasFoundAPawn = 1;
                    break;
                }
            }
            if (hasFoundAPawn == 0) //Affichage console
            {
                printf("  ");
            }
        }
        printf("|\n"); 

        for (int y = 0; y < SIZE_BOARD; y++) //Affichage console
        {
            printf("----");               
        }
        printf("\n");  
    }
}



/*

    FONCTIONS GENERALES DES PIONS

*/

int invertCords(int cordY) {
    return 7 - cordY;
}

int isNotInTheBoard(int userCordX, int userCordY){
    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
        return 1;
    }
    return 0;
}

void pawnSelection(Pawn** pawnSelected, Pawn pawnArray[NUMBER_OF_PAWN]){
    int userCordX, userCordY;

    printf("Choisissez la piece a bouger via ces coordonnees X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    
    userCordX--;
    userCordY--;

    if (isNotInTheBoard(userCordX, userCordY))
        exit(EXIT_FAILURE); //A remplacer pour laisser le joueur choisir une autre pièce
    
    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        if(pawnArray[i].cordX == userCordX && pawnArray[i].cordY == invertCords(userCordY)){
            *pawnSelected = &pawnArray[i];
            printf("Vous avez selectionnez le pion nomme : %s\n", (*pawnSelected)->pawnName);
            break;
        }
    }
}

/*

    FONCTIONS EXCLUSIVES AUX MOUVEMENTS DES PIONS

*/
int vectorDirCalculation(int isDirX, Pawn* pawnSelected, int userCord){
    if (isDirX)
        return pawnSelected->cordX - userCord;
    else
        return pawnSelected->cordY - invertCords(userCord);
}

int vectorLimitation(int vectorToLimit, int greaterLimitation, int lowerLimitation){
    if (vectorToLimit > greaterLimitation)
        return greaterLimitation;
    else if(vectorToLimit < lowerLimitation)
        return lowerLimitation;
}

int isTowerMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == 0 || vectorDirY == 0){
        printf("Mouvement tour de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        printf("Mouvement TOUR IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

int isPawnMovementPossible(Pawn* pawnSelected, int userCordX, int* userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, *userCordY);

    if((pawnSelected->teamColor == BLACK && pawnSelected->cordY == 1) || (pawnSelected->teamColor == WHITE && pawnSelected->cordY == 6))
        vectorDirY = vectorLimitation(vectorDirY, 2, -2);
    else
        vectorDirY = vectorLimitation(vectorDirY, 1, -1);

    vectorDirY *= -1;

    if(vectorDirX == 0 && vectorDirY > 0 && pawnSelected->teamColor == BLACK){
        printf("Mouvement pion de ' %s ' est possible\n", pawnSelected->pawnName);
        *userCordY = invertCords(pawnSelected->cordY) - vectorDirY;
        return 1;
    }
    else if(vectorDirX == 0 && vectorDirY < 0 && pawnSelected->teamColor == WHITE){
        printf("Mouvement pion de ' %s ' est possible\n", pawnSelected->pawnName);
        *userCordY = invertCords(pawnSelected->cordY) - vectorDirY;
        return 1;
    }
    else{
        printf("Mouvement PION IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

int isKingMovementPossible(Pawn* pawnSelected, int* userCordX, int* userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, *userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, *userCordY);

    vectorDirX = vectorLimitation(vectorDirX, 1, -1);
    vectorDirY = vectorLimitation(vectorDirY, 1, -1);

    *userCordX = pawnSelected->cordX - vectorDirX;
    *userCordY = invertCords(pawnSelected->cordY) + vectorDirY;

    return 1;
}

int isBishopMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == vectorDirY || vectorDirX == -vectorDirY){
        printf("Mouvement fou de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        printf("Mouvement FOU IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

int isKnightMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == 2 || vectorDirY == 1 || vectorDirX == 1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 ||
        vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == -1 || vectorDirX == -1 || vectorDirY == -2){
        printf("Mouvement chevalier de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        printf("Mouvement CHEVALIER IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}



/*

    FONCTIONS EXCLUSIVES AUX COLLISIONS DES PIONS

*/
int isKnightCollisionValid(Pawn* pawnSelected, int userCordX, int userCordY, Pawn* pawnArray){
    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        if (pawnSelected != &pawnArray[i] && (userCordX == pawnArray[i].cordX && invertCords(userCordY) == pawnArray[i].cordY))
            return 0;
    }
    return 1;
}

int isAllPawnCollisionValid(Pawn* pawnSelected, int userCordX, int userCordY, Pawn* pawnArray){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    vectorDirX = vectorLimitation(vectorDirX, 1, -1);
    vectorDirY = vectorLimitation(vectorDirY, 1, -1);

    printf("VECTEUR Y : %d\n", vectorDirY);

    int lastCoordX, lastCoordY, newCordX, newCordY;
    newCordX = pawnSelected->cordX - vectorDirX;
    newCordY = invertCords(pawnSelected->cordY) + vectorDirY;

    for (int t = 0; t < SIZE_BOARD; t++)
    {
        
        //Check les coordonnées de toutes les pièces
        for (int i = 0; i < NUMBER_OF_PAWN; i++)
        {
            printf("\tNOUVELLE COORDONNE X et Y : %d & %d\n", newCordX, newCordY);
            printf("\tCOORDONNE SOUHAITE X et Y : %d & %d\n\n", userCordX, userCordY);

            if ((newCordX == pawnArray[i].cordX && invertCords(newCordY) == pawnArray[i].cordY) && pawnSelected != &pawnArray[i])
                return 0;
            //printf("\tCOLLISION DETECTER AVEC %s EN : %d & %d\n\n", pawnArray[i].pawnName, userCordX, userCordY);
        }

        if(newCordX == userCordX && newCordY == userCordY)
        {
            printf("\tOK : %d & %d\n\n", userCordX, userCordY);
            return 1;
        }

        printf("--------------------------------\n");
        printf("VECTEUR X et Y : %d & %d\n", -vectorDirX, vectorDirY);
        printf("--------------------------------\n");

        //Met à jour les nouvelles coordonnées
        newCordY += vectorDirY;
        newCordX -= vectorDirX;
    }
}


/*

    FONCTIONS GENERALES AUX PIONS

*/
void movePawnFreely(Pawn* pawnSelected, int userCordX, int userCordY){
    pawnSelected->cordX = userCordX;
    pawnSelected->cordY = invertCords(userCordY);
}

void pawnMovement(Pawn* pawnSelected, Pawn pawnArray[NUMBER_OF_PAWN]){
    int userCordX, userCordY;

    printf("Choisissez la nouvelle position X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    userCordX--;
    userCordY--;
    if (isNotInTheBoard(userCordX, userCordY))
        exit(EXIT_FAILURE); //A remplacer pour laisser le joueur choisir une autre location

    switch (pawnSelected->pawnFunction)
    {
        case 'K':
            if (isKingMovementPossible(pawnSelected, &userCordX, &userCordY))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'Q':
            if(isTowerMovementPossible(pawnSelected, userCordX, userCordY) && isAllPawnCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            else if(isBishopMovementPossible(pawnSelected, userCordX, userCordY)  && isAllPawnCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'B':
            if(isBishopMovementPossible(pawnSelected, userCordX, userCordY)  && isAllPawnCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'C':
            if(isKnightMovementPossible(pawnSelected, userCordX, userCordY) && isKnightCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'T':
            if(isTowerMovementPossible(pawnSelected, userCordX, userCordY) && isAllPawnCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'P':
           if(isPawnMovementPossible(pawnSelected, userCordX, &userCordY)  && isAllPawnCollisionValid(pawnSelected, userCordX, userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;
        
        default:
            break;
    }
}



int main(){
    //Initialisation
    Pawn pawnArray[NUMBER_OF_PAWN * 2] = {};

    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        Pawn pawn = {.cordX = i, .cordY = invertCords(1), .pawnName = "Pawn", .boardRepresentation = 'P', .teamColor = WHITE, .pawnFunction ='P'};
        pawnArray[i] = pawn;
    }
    Pawn pawn = {.cordX = 0, .cordY = invertCords(3), .pawnName = "Fou", .boardRepresentation = 'B', .teamColor = WHITE, .pawnFunction ='B'};
    pawnArray[8] = pawn;

    //Boucle de jeu
    do
    {   
        printChessBoard(pawnArray);
        Pawn* pawnSelected = NULL;
        pawnSelection(&pawnSelected, pawnArray);
        pawnMovement(pawnSelected, pawnArray);
    } while (1 == 1);
}