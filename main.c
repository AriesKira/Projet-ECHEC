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



int main(){

    //Initialisation
    Pawn pawnArray[NUMBER_OF_PAWN] = {};

    Pawn pawn = {.cordX = 0, .cordY = 0, .pawnName = "Pawn", .boardRepresentation = 'P', .teamColor = BLACK};
    pawn.cordY = invertCords(pawn.cordY);
   
    //Temporaire
    pawnArray[0] = pawn;

    /* 
        BOUCLE d'exécution :
            fait apparaitre les pièce en fonction de leur cordonnées propres X
            bouger les pions
            afficher le plateau de jeu X
    */

    //Boucle de jeu
    printChessBoard(pawnArray);

    //Selection du pion
    Pawn* pawnSelected;
    int userCordX, userCordY;
    printf("Choisissez la piece a bouger via ces positions X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    userCordX--;
    userCordY--;

    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        printf("Pion nomme : \t%c\t %d %d\t(cordY to => invertCordY)\n", pawnArray[i].pawnName, pawnArray[i].cordX, pawnArray[i].cordY);
    }

    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
    }
    else{
        for (int i = 0; i < NUMBER_OF_PAWN; i++)
        {
            if(pawnArray[i].cordX == userCordX && pawnArray[i].cordY == invertCords(userCordY)){
                pawnSelected = &pawnArray[i];
                break;
            }
        }
        printf("Vous avez selectionnez le pion nomme : %s\n", pawnSelected->pawnName);
    }

    
    
    //Deplacement du pion
    printf("Choisissez la nouvelle position de cette piece en X et Y (ex: 1 8): ");
    scanf("%d %d", &userCordX, &userCordY);
    userCordX--;
    userCordY--;

    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
    }
    else{
        /*Calcul du vecteur de direction X et Y // Necessite d'être ramené entre -1 et 1
        int moveDirX = userCordX - pawnSelected.cordX;
        int moveDirY = userCordY - invertCords(pawnSelected.cordY);

        printf("Vecteur de direction X et Y : \t %d %d", moveDirX, moveDirY);*/

        //printf("Vecteur de direction X et Y : \t %d %d", userCordX, userCordY);

        pawnSelected->cordX = userCordX;
        pawnSelected->cordY = invertCords(userCordY);
        printChessBoard(pawnArray);
    }
}