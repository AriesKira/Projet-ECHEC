#include <stdlib.h>
#include <stdio.h>

typedef struct Pawn Pawn;
struct Pawn{
    int cordX;
    int cordY;
    char* pawnName;
    char boardRepresentation;
    int teamColor;
};


void movePawn(Pawn* pawn) {

    if (pawn->teamColor == 0) {
        if (pawn->cordY == 6) {
            
        }
        
    }
}
