/* 
 * File:   Structs.h
 * 
 * Declare you necessary Structures and Enumerations here. Remember to add a 
 * declaration to the copy paste range across all the files if you want to be
 * able to use them properly.
 *  
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

enum PieceType { Red, Black };
enum PieceState { OnBoard, Removed };

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

struct Cell {
    
    int Top;
    int Right;
    int Bottom;
    int Left;
    
    int IsOccupied;             
    PieceType OccupiedBy;       // Returns PieceType, Red or Black
    
    int Row;
    int Column;
    
    //the piece which this cell contains
    PtrPiece Piece;
    
};

struct Piece {
    
    PieceType Type;
    int IsKing;
    PieceState State;
    
    //cell on which this piece is currently on
    PtrCell Cell;
    
};

struct Board {
    
    Cell Cells[ ROW * COL ];
    
    //12 for 6x6
    //24 for 8x8
    //Each piece can be on one and only one cell
    Piece Pieces[ 24 ]; 
    
};


#endif	/* STRUCTS_H */

