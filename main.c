#include <stdlib.h>
#include <stdio.h>
#include "pawnMoves.h"

#define SIZE_BOARD 8
#define NUMBER_OF_PAWN 32
#define WHITE 0
#define BLACK 1


void spawnChessPawn(char** chessBoard, Pawn* pawnArray){
    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        chessBoard[pawnArray[i].cordY][pawnArray[i].cordX] = pawnArray[i].boardRepresentation; 
    }

    printf("Has spawned\n");

}


/* 
Changer printChessBoard pour ne plus avoir char** chssBoard
explication :
Le but est de ne plus gérer l'affichage des pions en fonction d'un tableau mais de tout faire graphiquement
printChessboard prendrait en argument le tableau des pièce pawnArray
1-printChessBoard regarde les positions actuelle de chaque pions et les stock dans un tableau 
2- a cahque tour de boucle si un pion est à la position actuel de la boucle affiche le pion en question 
3- free le tableau parce que c cool de free
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

int invertCords(int cordY) {
    return 7 - cordY;
}

void pawnSelection(Pawn** pawnSelected, Pawn pawnArray[NUMBER_OF_PAWN]){
    int userCordX, userCordY;

    printf("Choisissez la piece a bouger via ces coordonnees X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    
    userCordX--;
    userCordY--;

    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
        exit(EXIT_FAILURE);
    }
    else{
        for (int i = 0; i < NUMBER_OF_PAWN; i++)
        {
            if(pawnArray[i].cordX == userCordX && pawnArray[i].cordY == invertCords(userCordY)){
                *pawnSelected = &pawnArray[i];
                printf("Vous avez selectionnez le pion nomme : %s\n", (*pawnSelected)->pawnName);
                break;
            }
        }
    }
}

void pawnMovement(Pawn* pawnSelected){
    int userCordX, userCordY;

    printf("Choisissez la nouvelle position X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    
    userCordX--;
    userCordY--;

    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
        exit(EXIT_FAILURE);
    }
    else{
        int vectorDirX, vectorDirY;
        vectorDirX = userCordX - pawnSelected->cordX;
        vectorDirY = invertCords(userCordY) - pawnSelected->cordY;

        //Il faudrait nettoyer cette masse de code, la sectionnez en de plus petites fonction etc...
        //Personnellement, le premiers switch sur (pawnSelected->pawnMovementType) est un peu inutile, mais je n'ai pas le temps de le refactorer
        switch (pawnSelected->pawnMovementType)
        {
            case 'X':
                switch (pawnSelected->pawnFunction)
                {
                    case 'K':
                        //Peut être mis dans une fonction : RestreignMovement 
                        if (vectorDirX > 1)
                        {
                            vectorDirX = 1;
                        }
                        else if(vectorDirX < -1){
                            vectorDirX = -1;
                        }
                        if (vectorDirY > 1)
                        {
                            vectorDirY = 1;
                        }
                        else if(vectorDirY < -1){
                            vectorDirY = -1;
                        }
                        
                        //Peut être mis dans une fonction : DiagonalMovement 
                        if (vectorDirX == vectorDirY || vectorDirX == -vectorDirY)
                        {
                            printf("Mouvement diagonale lateral : OK\n");
                            pawnSelected->cordX = pawnSelected->cordX + vectorDirX;
                            pawnSelected->cordY = pawnSelected->cordY + vectorDirY;
                        }
                        else{
                            printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Diagonale Lateral\n");
                        }
                        break;

                    case 'Q':

                        //Peut être mis dans une fonction : DiagonalMovement 
                        if (vectorDirX == vectorDirY || vectorDirX == -vectorDirY)
                        {
                            printf("Mouvement diagonale lateral : OK\n");
                            pawnSelected->cordX = userCordX;
                            pawnSelected->cordY = invertCords(userCordY);
                        }
                        else{
                            printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Diagonale Lateral\n");
                        }
                        break;
                    
                    default:
                        printf("La pièce ne peut pas se déplacer en diagonale\n");
                        break;
                }
                break;
            case 'D':
                switch (pawnSelected->pawnFunction)
                {
                    case 'J':

                        //Peut être mis dans une fonction : DiagonalMovement 
                        if (vectorDirX == vectorDirY || vectorDirX == -vectorDirY)
                        {
                            printf("Mouvement diagonale : OK\n");
                            pawnSelected->cordX = userCordX;
                            pawnSelected->cordY = invertCords(userCordY);
                        }
                        else{
                            printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Diagonale\n");
                        }
                        break;
                    
                    default:
                        printf("La pièce ne peut pas se déplacer en diagonale\n");
                        break;
                }
                break;
            case 'L':
                switch (pawnSelected->pawnFunction)
                {
                    case 'P':
                        //Peut être mis dans une fonction : RestreignMovementPawnOnly
                        if(pawnSelected->teamColor == BLACK && vectorDirY >= 2 && pawnSelected->cordY == 1)
                        {
                            vectorDirY = 2;
                        }
                        else if (vectorDirY <= -2 && pawnSelected->teamColor == WHITE && pawnSelected->cordY == 6)
                        {
                            vectorDirY = -2;
                        }
                        else if (vectorDirY > 1)
                        {
                            vectorDirY = 1;
                        }
                        else if(vectorDirY < -1)
                        {
                            vectorDirY = -1;
                        }
                        
                        //Peut être mis dans une fonction : LateralMovementPawnOnly
                        if(vectorDirX == 0 && vectorDirY >= 0 && pawnSelected->teamColor == BLACK){
                            printf("Mouvement verticale ou horizontale : OK\n");
                            pawnSelected->cordY = pawnSelected->cordY + vectorDirY;
                        }
                        else if(vectorDirX == 0 && vectorDirY <= 0 && pawnSelected->teamColor == WHITE){
                            printf("Mouvement verticale ou horizontale : OK\n");
                            pawnSelected->cordY = pawnSelected->cordY + vectorDirY;
                        }
                        else{
                            printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Laterale\n");
                        }
                        break;

                    case 'T':
                        //Peut être mis dans une fonction : LateralMovement
                        if(vectorDirX == 0 || vectorDirY == 0){
                            printf("Mouvement verticale ou horizontale : OK\n");
                            pawnSelected->cordX = userCordX;
                            pawnSelected->cordY = invertCords(userCordY);
                        }
                        else{
                            printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Laterale\n");
                        }
                        break;
                    
                    default:
                        printf("La pièce ne peut pas se déplacer en diagonale\n");
                        break;
                }
                break;
            case 'C':
                //Peut être mis dans une fonction : CavalryMovement
                if(vectorDirX == 2 || vectorDirY == 1 || vectorDirX == 1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 ||
                vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == -1 || vectorDirX == -1 || vectorDirY == -2){
                    printf("Mouvement du cavalier : OK\n");
                    pawnSelected->cordX = userCordX;
                    pawnSelected->cordY = invertCords(userCordY);
                }
                else{
                    printf("Les coordonnées ne sont pas bonnes pour cette pièces en particulier\t ERREUR : Cavalier\n");
                }
                break;
            
            default:
                printf("Erreur dans les nouvelles coordonnées\n");
                break;
        }
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

    Pawn pawn = {.cordX = 3, .cordY = 0, .pawnName = "King", .boardRepresentation = 'K', .teamColor = WHITE, .pawnFunction ='K', .pawnMovementType = 'X'};
    pawn.cordY = invertCords(pawn.cordY);
    Pawn pawn2 = {.cordX = 7, .cordY = 7, .pawnName = "Pawn", .boardRepresentation = 'P', .teamColor = BLACK, .pawnFunction ='P', .pawnMovementType = 'L'};
    pawn2.cordY = invertCords(pawn2.cordY);
    Pawn pawn3 = {.cordX = 0, .cordY = 0, .pawnName = "Pawn", .boardRepresentation = 'P', .teamColor = WHITE, .pawnFunction ='P', .pawnMovementType = 'L'};
    pawn3.cordY = invertCords(pawn3.cordY);
   
    //Temporaire
    pawnArray[0] = pawn;
    pawnArray[1] = pawn2;
    pawnArray[2] = pawn3;

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