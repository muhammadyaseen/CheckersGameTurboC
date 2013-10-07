/* 
 * File:   MoveFunctions.h
 * 
 * Functions to move the pieces go here.
 * 
 */

#ifndef MOVEFUNCTIONS_H
#define	MOVEFUNCTIONS_H

#include "Enums&Structs.h"
#include "Rules.h"

/*Copy  this part if the code in every header file*/
#define ROW 8
#define COL 8

typedef enum PieceType PieceType;
typedef enum PieceState PieceState;

typedef struct Piece Piece;
typedef struct Piece * PtrPiece;

typedef struct Board Board;
typedef struct Board * PtrBoard;

typedef struct Cell Cell;
typedef struct Cell * PtrCell;
/*End of required copy pasting*/

#endif	/* MOVEFUNCTIONS_H */

