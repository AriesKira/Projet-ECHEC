#include <stdlib.h>
#include <stdio.h>

typedef struct Pawn Pawn;
struct Pawn{
    int cordX;
    int cordY;
    char* pawnName;
    char pawnFunction;
    //On peut remplacer pawnFunction par un score, mais c'est moins lisible pour nous les humains
    int pawnScore;
    char boardRepresentation;
    int teamColor;
};

#define SIZE_BOARD 8
#define NUMBER_OF_PAWN 32
#define WHITE 0
#define BLACK 1
#define DEAD 2


int invertCords(int cordY) {
    return 7 - cordY;
}

int isPawnsFromTheSameTeam(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int moveToCordX, int moveToCordY){
    if (chessboard[selectedPawnCordY][selectedPawnCordX].teamColor == chessboard[moveToCordY][moveToCordX].teamColor)
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

int isWrongPawnSelected(int userCordX, int userCordY, Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int* returnY, int* returnX, int isItWhiteTurn){
    for (int y = 0; y < SIZE_BOARD; y++)
    {
        for (int x = 0; x < SIZE_BOARD; x++)
        {
            if(userCordY == chessboard[y][x].cordY && userCordX == chessboard[y][x].cordX && chessboard[y][x].teamColor != DEAD)
            {
                if ((isItWhiteTurn == 1 && chessboard[y][x].teamColor == WHITE) ||
                (isItWhiteTurn == 0 && chessboard[y][x].teamColor == BLACK))
                {
                    *returnX = x;
                    *returnY = y;
                    return 0;
                }
                else{
                    printf("Ce n'est pas le tour de cette equipe\n");
                    return 1;
                }
            }
        }
    }

    printf("Il n'y a pas de pions a cette case\n");
    return 1;
}

void printChessBoard(Pawn pawnArray[SIZE_BOARD][SIZE_BOARD]){
    for (int x = 0; x < SIZE_BOARD; x++) //Affichage console
        printf("----");               
    printf("\n"); 

    for (int y = 0; y < SIZE_BOARD; y++)
    {
        for (int x = 0; x < SIZE_BOARD; x++)
        {
            printf("| ");  //Affichage console
            if (pawnArray[y][x].boardRepresentation != ' ')
                printf("%c ", pawnArray[y][x].boardRepresentation);
            else
                printf("  ");  //Affichage console
        }
        printf("|\n"); 

        for (int x = 0; x < SIZE_BOARD; x++) //Affichage console
            printf("----");               
        printf("\n");  
    }
}

int limitValueToOne(int myValue){
    if(myValue > 0)
        return 1;
    else if(myValue < 0)
        return -1;
    else
        return 0;
}

void pawnSelection(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int isItWhiteTurn, int* indexX, int* indexY){
    int userCordX, userCordY;
    do
    {
        printf("Choisissez la piece a bouger via ces coordonnees X et Y (ex: 1 8): ");
        scanf("%d %d", &userCordX, &userCordY);
        userCordX--;
        userCordY--;
    } while (isNotInTheBoard(userCordX, userCordY) || isWrongPawnSelected(userCordX, userCordY, chessboard, indexY, indexX, isItWhiteTurn));
}

int pawnLogic(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int* moveToCordX, int* moveToCordY){
    
    switch (chessboard[selectedPawnCordY][selectedPawnCordX].pawnFunction)
    {
        case 'K':
            if (isKingMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, *moveToCordX, *moveToCordY))
                return 1;
            break;

        case 'Q':
            if (isBishopMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY) ||
            isTowerMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY))
                return 1;
            break;

        case 'B':
            if (isBishopMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY))
                return 1;
            break;

        case 'C':
            if (isKnightMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, *moveToCordX, *moveToCordY))
                return 1;
            break;

        case 'T':
            if (isTowerMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY))
                return 1;
            break;

        case 'P':
            if (isPawnMovementValid(chessboard, selectedPawnCordX, selectedPawnCordY, *moveToCordX, *moveToCordY))
                return 1;
            break;
        
        default:
            break;
    }
    return 0;
}

void pawnMovement(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int* isMouvementDone){

    int moveToCordX, moveToCordY;
    do
    {
        printf("Choisissez la nouvelle position X et Y (ex: 1 8): ");
        scanf("%d %d", &moveToCordX, &moveToCordY);
        moveToCordX--;
        moveToCordY--;
        printf("%d moveX %d\t %d moveY %d\n", selectedPawnCordX, moveToCordX, selectedPawnCordY, moveToCordY);

        if (selectedPawnCordX == moveToCordX && selectedPawnCordY == moveToCordY)
        {
            *isMouvementDone = 0;
            break;
        }
    } while (isNotInTheBoard(moveToCordX, moveToCordY) || !pawnLogic(chessboard, selectedPawnCordX, selectedPawnCordY, &moveToCordX, &moveToCordY));

    if (selectedPawnCordX != moveToCordX || selectedPawnCordY != moveToCordY)
    {
        movePawnToDestination(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY);
        *isMouvementDone = 1;
    }
}

void movePawnToDestination(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int moveToCordX, int moveToCordY){
    chessboard[moveToCordY][moveToCordX].teamColor = chessboard[selectedPawnCordY][selectedPawnCordX].teamColor;
    chessboard[moveToCordY][moveToCordX].pawnName = chessboard[selectedPawnCordY][selectedPawnCordX].pawnName;
    chessboard[moveToCordY][moveToCordX].pawnFunction = chessboard[selectedPawnCordY][selectedPawnCordX].pawnFunction;
    chessboard[moveToCordY][moveToCordX].boardRepresentation = chessboard[selectedPawnCordY][selectedPawnCordX].boardRepresentation;
    chessboard[moveToCordY][moveToCordX].pawnScore = chessboard[selectedPawnCordY][selectedPawnCordX].pawnScore;

    chessboard[selectedPawnCordY][selectedPawnCordX].teamColor = DEAD;
    chessboard[selectedPawnCordY][selectedPawnCordX].pawnName = "Nothing";
    chessboard[selectedPawnCordY][selectedPawnCordX].pawnFunction = ' ';
    chessboard[selectedPawnCordY][selectedPawnCordX].boardRepresentation = ' ';
    chessboard[selectedPawnCordY][selectedPawnCordX].pawnScore = 0;
}

int isTowerMovementValid(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int* moveToCordX, int* moveToCordY){
    int lastVectorDirX = chessboard[selectedPawnCordY][selectedPawnCordX].cordX - *moveToCordX;
    int lastVectorDirY = chessboard[selectedPawnCordY][selectedPawnCordX].cordY - *moveToCordY;
    int limitVectorDirX = limitValueToOne(lastVectorDirX);
    int limitVectorDirY = limitValueToOne(lastVectorDirY);
    int vectorDirX = limitVectorDirX;
    int vectorDirY = limitVectorDirY;

    if((lastVectorDirX == 0 || lastVectorDirY == 0) &&
    !isPawnsFromTheSameTeam(chessboard, selectedPawnCordX, selectedPawnCordY, *moveToCordX, *moveToCordY)){
        for (int i = 0; i < SIZE_BOARD; i++)
        {
            if(chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordX == *moveToCordX && chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordY == *moveToCordY)
            {
                return 1;
            }
            else if(chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor == DEAD)
            {
                if (vectorDirX != 0)
                    vectorDirX += limitVectorDirX;
                if(vectorDirY != 0)            
                    vectorDirY += limitVectorDirY;
            }
            else if (chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor != chessboard[selectedPawnCordY][selectedPawnCordX].teamColor 
            && chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor != DEAD)
            {
                *moveToCordX = chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordX; 
                *moveToCordY = chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordY; 
                return 1;
            }
        }
    }
    printf("Mouvement impossible, veuillez choisir des coordonnées valides pour cette pièce\n");
    return 0;
}

int isBishopMovementValid(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int* moveToCordX, int* moveToCordY){
    int lastVectorDirX = chessboard[selectedPawnCordY][selectedPawnCordX].cordX - *moveToCordX;
    int lastVectorDirY = chessboard[selectedPawnCordY][selectedPawnCordX].cordY - *moveToCordY;
    int limitVectorDirX = limitValueToOne(lastVectorDirX);
    int limitVectorDirY = limitValueToOne(lastVectorDirY);
    int vectorDirX = limitVectorDirX;
    int vectorDirY = limitVectorDirY;

    if((lastVectorDirX == lastVectorDirY || lastVectorDirX == -lastVectorDirY) &&
    !isPawnsFromTheSameTeam(chessboard, selectedPawnCordX, selectedPawnCordY, *moveToCordX, *moveToCordY)){
        for (int i = 0; i < SIZE_BOARD; i++)
        {
            if(chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordX == *moveToCordX && chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordY == *moveToCordY)
            {
                return 1;
            }
            else if(chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor == DEAD)
            {
                if (vectorDirX != 0)
                    vectorDirX += limitVectorDirX;
                if(vectorDirY != 0)            
                    vectorDirY += limitVectorDirY;
            }
            else if (chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor != chessboard[selectedPawnCordY][selectedPawnCordX].teamColor 
            && chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].teamColor != DEAD)
            {
                *moveToCordX = chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordX; 
                *moveToCordY = chessboard[selectedPawnCordY - vectorDirY][selectedPawnCordX - vectorDirX].cordY; 
                return 1;
            }
        }
    }
    return 0;
}

int isKnightMovementValid(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int moveToCordX, int moveToCordY){
    int lastVectorDirX = chessboard[selectedPawnCordY][selectedPawnCordX].cordX - moveToCordX;
    int lastVectorDirY = chessboard[selectedPawnCordY][selectedPawnCordX].cordY - moveToCordY;

    if(((lastVectorDirX == 2 && lastVectorDirY == 1) || 
    (lastVectorDirX == 1 && lastVectorDirY == 2) || 
    (lastVectorDirX == -2 && lastVectorDirY == 1) || 
    (lastVectorDirX == -1 && lastVectorDirY == 2) ||
    (lastVectorDirX == -2 && lastVectorDirY == 1) || 
    (lastVectorDirX == -1 && lastVectorDirY == 2) || 
    (lastVectorDirX == -2 && lastVectorDirY == -1) || 
    (lastVectorDirX == -1 && lastVectorDirY == -2)) &&
    !isPawnsFromTheSameTeam(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY))
        return 1;
    else
        return 0;
}

int isKingMovementValid(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int moveToCordX, int moveToCordY){
    int lastVectorDirX = chessboard[selectedPawnCordY][selectedPawnCordX].cordX - moveToCordX;
    int lastVectorDirY = chessboard[selectedPawnCordY][selectedPawnCordX].cordY - moveToCordY;

    if((-1 <= lastVectorDirX && lastVectorDirX <= 1) && (-1 <= lastVectorDirY && lastVectorDirY <= 1) &&
    !isPawnsFromTheSameTeam(chessboard, selectedPawnCordX, selectedPawnCordY, moveToCordX, moveToCordY))
        return 1;
    else
        return 0;
}

int isPawnMovementValid(Pawn chessboard[SIZE_BOARD][SIZE_BOARD], int selectedPawnCordX, int selectedPawnCordY, int moveToCordX, int moveToCordY){
    int lastVectorDirX = chessboard[selectedPawnCordY][selectedPawnCordX].cordX - moveToCordX;
    int lastVectorDirY = chessboard[selectedPawnCordY][selectedPawnCordX].cordY - moveToCordY;

    if((chessboard[selectedPawnCordY][selectedPawnCordX].teamColor == WHITE && lastVectorDirX == 0 && lastVectorDirY == 1) &&
    (chessboard[selectedPawnCordY-lastVectorDirY][selectedPawnCordX].teamColor == DEAD))
        return 1;
    else if((chessboard[selectedPawnCordY][selectedPawnCordX].teamColor == BLACK && lastVectorDirX == 0 && lastVectorDirY == -1) &&
    (chessboard[selectedPawnCordY-lastVectorDirY][selectedPawnCordX].teamColor == DEAD))
        return 1;
    else if((chessboard[selectedPawnCordY][selectedPawnCordX].teamColor == WHITE && (lastVectorDirX == 1 || lastVectorDirX == -1) && lastVectorDirY == 1) &&
    (chessboard[selectedPawnCordY-lastVectorDirY][selectedPawnCordX-lastVectorDirX].teamColor == BLACK))
        return 1;
    else if((chessboard[selectedPawnCordY][selectedPawnCordX].teamColor == BLACK && (lastVectorDirX == 1 || lastVectorDirX == -1) && lastVectorDirY == -1) &&
    (chessboard[selectedPawnCordY-lastVectorDirY][selectedPawnCordX-lastVectorDirX].teamColor == WHITE))
        return 1;
    else
        return 0;
}

int main(){
    Pawn chessboard[SIZE_BOARD][SIZE_BOARD];
    int isItWhiteTurn = 1;

    for (int y = 0; y < SIZE_BOARD; y++)
    {
        for (int x = 0; x < SIZE_BOARD; x++)
        {
            if (y == 1)
            {
                Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black Pawn", .boardRepresentation = 'P', .teamColor = BLACK, .pawnFunction ='P', .pawnScore = 1};
                chessboard[y][x] = pawn;
            }
            else if(y == 0)
            {
                if(x == 0 || x == 7)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black Tower", .boardRepresentation = 'T', .teamColor = BLACK, .pawnFunction ='T', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 1 || x == 6)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black Knight", .boardRepresentation = 'C', .teamColor = BLACK, .pawnFunction ='C', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 2 || x == 5)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black Bishop", .boardRepresentation = 'B', .teamColor = BLACK, .pawnFunction ='B', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 4)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black King", .boardRepresentation = 'K', .teamColor = BLACK, .pawnFunction ='K', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 3)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Black Queen", .boardRepresentation = 'Q', .teamColor = BLACK, .pawnFunction ='Q', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
            }
            else if(y == 6)
            {
                Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White Pawn", .boardRepresentation = 'P', .teamColor = WHITE, .pawnFunction ='P', .pawnScore = 1};
                chessboard[y][x] = pawn;
            }
            else if(y == 7)
            {
                if(x == 0 || x == 7)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White Tower", .boardRepresentation = 'T', .teamColor = WHITE, .pawnFunction ='T', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 1 || x == 6)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White Knight", .boardRepresentation = 'C', .teamColor = WHITE, .pawnFunction ='C', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 2 || x == 5)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White Bishop", .boardRepresentation = 'B', .teamColor = WHITE, .pawnFunction ='B', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 3)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White King", .boardRepresentation = 'K', .teamColor = WHITE, .pawnFunction ='K', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
                else if(x == 4)
                {
                    Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "White Queen", .boardRepresentation = 'Q', .teamColor = WHITE, .pawnFunction ='Q', .pawnScore = 1};
                    chessboard[y][x] = pawn;
                }
            }
            else
            {
                Pawn pawn = {.cordX = x, .cordY = y, .pawnName = "Nothing", .boardRepresentation = ' ', .teamColor = DEAD, .pawnFunction =' ', .pawnScore = 0};
                chessboard[y][x] = pawn;
            }
        }
    }

    int returnedIndexCordX, returnedIndexCordY, isMouvementDone;
    do
    {   
        printChessBoard(chessboard);
        do
        {
            pawnSelection(chessboard, isItWhiteTurn, &returnedIndexCordX, &returnedIndexCordY);
            pawnMovement(chessboard, returnedIndexCordX, returnedIndexCordY, &isMouvementDone);
        } while (isMouvementDone == 0);
        isItWhiteTurn = (isItWhiteTurn - 1) * -1;
    } while (1 == 1);
}