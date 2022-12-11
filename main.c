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

    FONCTIONS EXCLUSIVES AUX PIONS

*/
int vectorDirCalculation(int isDirX, Pawn* pawnSelected, int userCord){
    if (isDirX)
        return pawnSelected->cordX - userCord;
    else
        return pawnSelected->cordY - invertCords(userCord);
}

int isLateralMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == 0 || vectorDirY == 0){
        printf("Mouvement laterale de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        printf("Mouvement LETERALE IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

int isDiagonalMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == vectorDirY || vectorDirX == -vectorDirY){
        printf("Mouvement diagonale de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        printf("Mouvement DIAGONAL IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

void pawnMovement(Pawn* pawnSelected){
    int userCordX, userCordY;

    printf("Choisissez la nouvelle position X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    userCordX--;
    userCordY--;
    if (isNotInTheBoard(userCordX, userCordY))
        exit(EXIT_FAILURE); //A remplacer pour laisser le joueur choisir une autre location

    switch (pawnSelected->pawnFunction)
    {
    case 'R':
        isLateralMovementPossible(pawnSelected, userCordX, userCordY);
        isDiagonalMovementPossible(pawnSelected, userCordX, userCordY);
        break;

    case 'Q':
        isLateralMovementPossible(pawnSelected, userCordX, userCordY);
        isDiagonalMovementPossible(pawnSelected, userCordX, userCordY);
        break;

    case 'B':
        isDiagonalMovementPossible(pawnSelected, userCordX, userCordY);
        break;

    case 'C':
        /* code */
        break;

    case 'T':
        isLateralMovementPossible(pawnSelected, userCordX, userCordY);
        break;

    case 'P':
        isLateralMovementPossible(pawnSelected, userCordX, userCordY);
        break;
    
    default:
        break;
    }
}


/*

    OBJECTIFS DU JOUR :
    - Programmer plusieurs pièces possèdant chacunes leurs propres mouvement :
        - roi
        - reine
        - fou
        - cavalier
        - tour
        - pion
    
    - Programmer les collisions entres chaques pièces

*/

int main(){

    //Initialisation
    Pawn pawnArray[NUMBER_OF_PAWN] = {};

    Pawn pawn = {.cordX = 0, .cordY = 3, .pawnName = "King", .boardRepresentation = 'K', .teamColor = WHITE, .pawnFunction ='K'};
    pawn.cordY = invertCords(pawn.cordY);
    Pawn pawn3 = {.cordX = 2, .cordY = 0, .pawnName = "Tower", .boardRepresentation = 'T', .teamColor = WHITE, .pawnFunction ='T'};
    pawn3.cordY = invertCords(pawn3.cordY);

    Pawn pawn2 = {.cordX = 0, .cordY = 0, .pawnName = "Queen", .boardRepresentation = 'Q', .teamColor = WHITE, .pawnFunction ='Q'};
    pawn2.cordY = invertCords(pawn2.cordY);
   
    //Temporaire
    pawnArray[0] = pawn;
    pawnArray[1] = pawn3;
    pawnArray[2] = pawn2;

    //Boucle de jeu
    do
    {   
        printChessBoard(pawnArray);
        Pawn* pawnSelected = NULL;
        pawnSelection(&pawnSelected, pawnArray);
        pawnMovement(pawnSelected);
    } while (1 == 1);

    /*
        Boucle de jeu
        Déplacement du personnages
        Dégommage d'eux même
    */
}