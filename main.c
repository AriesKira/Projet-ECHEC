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



void printChessBoard(char** chessBoard){
    for (int y = 0; y < SIZE_BOARD; y++)
    {
        printf("----");               
    }
    printf("\n"); 
    
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int y = 0; y < SIZE_BOARD; y++)
        {
            printf("| ");            
            printf("%c ", chessBoard[i][y]);            
        }
        printf("|\n");            

        for (int y = 0; y < SIZE_BOARD; y++)
        {
            printf("----");               
        }
        printf("\n");            
    }
}

void resetChessBoard(char** chessBoard){
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int y = 0; y < SIZE_BOARD; y++)
        {
            chessBoard[i][y] = ' ';
        }          
    }
}





void moveNormalPawn(int cordX, int cordY, Pawn* pawn){
    pawn->cordX = 3;
    pawn->cordY = 3;

    printf("Has moved\n");
}

void invertCords(Pawn* pawn) {
    int inversedCordY = 7 - pawn->cordY;
    pawn->cordY = inversedCordY;
}

int main(){
    Pawn pawnArray[NUMBER_OF_PAWN] = {};

    Pawn pawn = {.cordX = 0, .cordY = 0, .pawnName = "Pawn", .boardRepresentation = 'P', .teamColor = BLACK};
    invertCords(&pawn);

    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        pawnArray[i] = pawn;
    }

    Pawn myTestPawn = {.cordX = 3, .cordY = 0, .pawnName = "Pawn", .boardRepresentation = 'O', .teamColor = WHITE};
    invertCords(&myTestPawn);
   
    pawnArray[0] = myTestPawn;
    /* 
        BOUCLE d'exécution :
            reset le plateau de jeu
            fait apparaitre les pièce en fonction de leur cordonnées propres
            bouger les pions
            afficher le plateau de jeu
    */


    /*
        29/11/2022 :
            - Création d'une première version de la struct Pawn
            - Création de fonction test (movePawn)
            - Création d'un tableau 2D dynamique, pour représenter le plateau, pour pouvoir facilement le mettre à jour dans les futures fonctions
    */ 

    char** chessBoard = NULL;
    if ((chessBoard = (char**)malloc(sizeof(char*) * SIZE_BOARD)) == NULL)
    {
        fprintf(stdout, "ERREUR : Allocation dynamique d'un pointeur a échoué");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        if ((chessBoard[i] = (char*)malloc(sizeof(char) * SIZE_BOARD)) == NULL)
        {
            fprintf(stdout, "ERREUR : Allocation dynamique d'un pointeur a échoué");
            exit(EXIT_FAILURE);
        }
    }

    //Faire les fonction implémentant la boucle de jeu primaire : ResetBoard, MoveNormalPawn, PrintBoard

    chessBoard[0][0] = 'x';
    printf("Cool: %c\n", chessBoard[0][0]);

    resetChessBoard(chessBoard);
    moveNormalPawn(myTestPawn.cordX, myTestPawn.cordY, &myTestPawn);

    printf("Cordonnées de mon pawn test : %d et %d\n", myTestPawn.cordX, myTestPawn.cordY);
    //
    //Besoin de réattribuer mon test pawn à pawnArray à chaque mouvement
    //Possible de le faire automatiquement dans la fonction
    //
    pawnArray[0] = myTestPawn;


    spawnChessPawn(chessBoard, pawnArray);
    printChessBoard(chessBoard);
    
    

    //printChessboard(chessboard);
}