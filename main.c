#include <stdlib.h>
#include <stdio.h>
#include "pawnMoves.h"

#define SIZE_BOARD 8
#define NUMBER_OF_PAWN 32
#define WHITE 0
#define BLACK 1
#define DEAD 2



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
                if (pawnArray[i].cordX == y && pawnArray[i].cordY == x && pawnArray[i].teamColor != DEAD)
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

int isPawnsFromTheSameTeam(Pawn* firstPawn, Pawn* secondPawn){
    if (firstPawn->teamColor == secondPawn->teamColor)
        return 1;
    else
        return 0;
}

int isNotInTheBoard(int userCordX, int userCordY){
    if (userCordX < 0 || userCordX > 7 || userCordY < 0 || userCordY > 7)
    {
        printf("Veuillez selectionnez des coordonnees correctes\n");
        return 1;
    }
    return 0;
}

int isWrongPawnSelected(int userCordX, int userCordY, Pawn pawnArray[NUMBER_OF_PAWN], int* indexPawn, int isItWhiteTurn){
    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        if(pawnArray[i].cordX == userCordX && pawnArray[i].cordY == invertCords(userCordY) && pawnArray[i].teamColor != DEAD){
            if (isItWhiteTurn && pawnArray[i].teamColor == WHITE || !isItWhiteTurn && pawnArray[i].teamColor == BLACK){
                *indexPawn = i;
                return 0;
            }       
            else{
                printf("Ce n'est pas le tour de cette equipe de jouer\n");
                return 1;
            }
        }
    }
    printf("Il n'y a pas de pions a cette case\n");
    return 1;
}

isPawnSelectionPuttingKingInDanger(){

    /*
        Pour cette partie la, simulez :
        - Simulons chaque coup possible de l'équipe adverse
            - Si un pion détecte que son mouvement : mange une pièce adverse + ce pion "pawnFunction" est K "ROI" => Refuser sélection de ce pions avec comme message :
            "Votre roi est en échec\n"
            - Sinon faire la sélection
    */

   

    printf("Le roi n'est pas en danger\n");
    return 0;
}

void pawnSelection(Pawn** pawnSelected, Pawn pawnArray[NUMBER_OF_PAWN], int isItWhiteTurn){
    int userCordX, userCordY, indexPawn;

    do
    {
        printf("Choisissez la piece a bouger via ces coordonnees X et Y (ex: 1 8): ");
        scanf("%d %d", &userCordX, &userCordY);
        
        userCordX--;
        userCordY--;
    } while (isNotInTheBoard(userCordX, userCordY) || isWrongPawnSelected(userCordX, userCordY, pawnArray, &indexPawn, isItWhiteTurn) || isPawnSelectionPuttingKingInDanger());
    *pawnSelected = &pawnArray[indexPawn];
    printf("Vous avez selectionnez le pion nomme : %s\n", (*pawnSelected)->pawnName);
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
        //printf("Mouvement tour de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        //printf("Mouvement TOUR IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
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
        //printf("Mouvement pion de ' %s ' est possible\n", pawnSelected->pawnName);
        *userCordY = invertCords(pawnSelected->cordY) - vectorDirY;
        return 1;
    }
    else if(vectorDirX == 0 && vectorDirY < 0 && pawnSelected->teamColor == WHITE){
        //printf("Mouvement pion de ' %s ' est possible\n", pawnSelected->pawnName);
        *userCordY = invertCords(pawnSelected->cordY) - vectorDirY;
        return 1;
    }
    else{
        //printf("Mouvement PION IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
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
        //printf("Mouvement fou de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        //printf("Mouvement FOU IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

int isKnightMovementPossible(Pawn* pawnSelected, int userCordX, int userCordY){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, userCordY);

    if(vectorDirX == 2 || vectorDirY == 1 || vectorDirX == 1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 ||
        vectorDirX == -2 || vectorDirY == 1 || vectorDirX == -1 || vectorDirY == 2 || vectorDirX == -2 || vectorDirY == -1 || vectorDirX == -1 || vectorDirY == -2){
        //printf("Mouvement chevalier de ' %s ' est possible\n", pawnSelected->pawnName);
        return 1;
    }
    else{
        //printf("Mouvement CHEVALIER IMPOSSIBLE POUR ' %s '\n", pawnSelected->pawnName);
        return 0;
    }
}

isPawnMovementPuttingKingInDanger(){

    /*
        Pour cette partie la, simulez :
            - Désactivons la pièce
            - Simulons chaque coup possible de l'équipe adverse
                - Si un pion détecte que son mouvement : mange une pièce adverse + ce pion "pawnFunction" est K "ROI" => Refuser mouvement de ce pions avec comme message :
                "Votre metteriez votre roi est en échec\n"
                - Sinon faire le mouvement
    */

   

    printf("Le roi n'est pas en danger\n");
    return 0;
}



/*

    FONCTIONS EXCLUSIVES AUX COLLISIONS DES PIONS

*/
int isKnightCollisionValid(Pawn* pawnSelected, int* userCordX, int* userCordY, Pawn* pawnArray){
    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        if (pawnSelected != &pawnArray[i] && (*userCordX == pawnArray[i].cordX && invertCords(*userCordY) == pawnArray[i].cordY)){
            if(isPawnsFromTheSameTeam(pawnSelected, &pawnArray[i]))
                return 0;
            else
                pawnArray[i].teamColor = DEAD;
                *userCordX = pawnArray[i].cordX;
                *userCordY = invertCords(pawnArray[i].cordY);
                return 1;
        }
    }
    return 1;
}

int isPawnCollisionValid(Pawn* pawnSelected, int* userCordX, int* userCordY, Pawn* pawnArray){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, *userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, *userCordY);

    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        if(pawnSelected->teamColor == WHITE && (pawnSelected->cordY - vectorDirY) == pawnArray[i].cordY && (pawnSelected->cordX - vectorDirX) == pawnArray[i].cordX && vectorDirX != 0)
        {
            pawnArray[i].teamColor = DEAD;
            *userCordX = pawnArray[i].cordX;
            *userCordY = invertCords(pawnArray[i].cordY);
            return 1;
        }
        else if(pawnSelected->teamColor == BLACK && (pawnSelected->cordY - vectorDirY) == pawnArray[i].cordY && (pawnSelected->cordX - vectorDirX) == pawnArray[i].cordX && vectorDirX != 0)
        {
            pawnArray[i].teamColor = DEAD;
            *userCordX = pawnArray[i].cordX;
            *userCordY = invertCords(pawnArray[i].cordY);
            return 1;
        }
    }
    return 0;
}

int isAllPawnCollisionValid(Pawn* pawnSelected, int* userCordX, int* userCordY, Pawn* pawnArray){
    int vectorDirX = vectorDirCalculation(1, pawnSelected, *userCordX);
    int vectorDirY = vectorDirCalculation(0, pawnSelected, *userCordY);

    vectorDirX = vectorLimitation(vectorDirX, 1, -1);
    vectorDirY = vectorLimitation(vectorDirY, 1, -1);

    int lastCoordX, lastCoordY, newCordX, newCordY;
    newCordX = pawnSelected->cordX - vectorDirX;
    newCordY = invertCords(pawnSelected->cordY) + vectorDirY;

    for (int t = 0; t < SIZE_BOARD; t++)
    {
        for (int i = 0; i < NUMBER_OF_PAWN; i++)
        {
            if ((newCordX == pawnArray[i].cordX && invertCords(newCordY) == pawnArray[i].cordY) && pawnSelected != &pawnArray[i]){
                if(isPawnsFromTheSameTeam(pawnSelected, &pawnArray[i]))
                    return 0;
                else if(!isPawnsFromTheSameTeam(pawnSelected, &pawnArray[i]) && pawnSelected->pawnFunction != 'P'){
                    pawnArray[i].teamColor = DEAD;
                    *userCordX = pawnArray[i].cordX;
                    *userCordY = invertCords(pawnArray[i].cordY);
                    return 1;
                }
                else
                    return 0;
            }
        }

        if(newCordX == *userCordX && newCordY == *userCordY)
            return 1;

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

    /*
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    FIXE LE FAIT D'ARRETER LE JEU SI ON CHOISI UNE MAUVAISE COORDONNEES
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    */

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
            if(isTowerMovementPossible(pawnSelected, userCordX, userCordY) && isAllPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            else if(isBishopMovementPossible(pawnSelected, userCordX, userCordY)  && isAllPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'B':
            if(isBishopMovementPossible(pawnSelected, userCordX, userCordY)  && isAllPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'C':
            if(isKnightMovementPossible(pawnSelected, userCordX, userCordY) && isKnightCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'T':
            if(isTowerMovementPossible(pawnSelected, userCordX, userCordY) && isAllPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray))
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;

        case 'P':
           if((isPawnMovementPossible(pawnSelected, userCordX, &userCordY)  && isAllPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray)
            || isPawnCollisionValid(pawnSelected, &userCordX, &userCordY, pawnArray)) && !isPawnMovementPuttingKingInDanger())
                movePawnFreely(pawnSelected, userCordX, userCordY);
            break;
        
        default:
            break;
    }
}



int main(){
    //Initialisation
    Pawn pawnArray[NUMBER_OF_PAWN * 2] = {};
    int isItWhiteTurn = 1;

    for (int i = 0; i < NUMBER_OF_PAWN; i++)
    {
        Pawn pawn = {.cordX = i, .cordY = invertCords(6), .pawnName = "Pawn", .boardRepresentation = 'B', .teamColor = BLACK, .pawnFunction ='P'};
        pawnArray[i] = pawn;
    }
    Pawn pawn = {.cordX = 1, .cordY = invertCords(5), .pawnName = "Pion", .boardRepresentation = 'P', .teamColor = WHITE, .pawnFunction ='P'};
    pawnArray[8] = pawn;

    //Boucle de jeu
    do
    {   
        printChessBoard(pawnArray);
        Pawn* pawnSelected = NULL;
        pawnSelection(&pawnSelected, pawnArray, isItWhiteTurn);
        pawnMovement(pawnSelected, pawnArray);
        isItWhiteTurn = (isItWhiteTurn - 1) * -1;
    } while (1 == 1);
}