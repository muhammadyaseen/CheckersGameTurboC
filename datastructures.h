#ifndef DATASTRUCTURES_H
#define	DATASTRUCTURES_H

#define ROW 8
#define COL 8
#define WIDTH 75
#define HEIGHT 75
#define RADIUS 25
#define DRAW_START_UP 3    // draw piece in first two rows
#define DRAW_START_DOWN 4  // draw piece in last two rows
#define BORDER_COLOR CYAN
#define CHANGE_PIECE 100

enum PieceType { Red, Blue };
enum PieceState { OnBoard, Removed };
enum GameState { Welcome, Playing, PlayerWin, CPUWin };

typedef enum PieceType PieceType;
typedef enum PieceState PieceState;
typedef enum GameState GameState;

typedef struct Board Board;
typedef struct Cell Cell;
typedef struct Piece Piece;

typedef struct Board * PtrBoard;
typedef struct Cell * PtrCell;
typedef struct Piece * PtrPiece;

struct Cell {
    int ID;
    int Top;
    int Right;
    int Bottom;
    int Left;
    
    int IsOccupied;
    int OccupiedBy;
    
    int Row;
    int Column;
    
    //the piece which this cell contains
    PtrPiece Piece;
    
};

struct Piece {
    int ID;
    int Type;
    int IsKing;
    PieceState State;
    
    //cell on which this piece is currently on
    PtrCell Cell;
    
};

struct Board {
    
    Cell Cells[ ROW * COL ];
    
    //12 for 6x6 24 for 8x8
    //Each piece can be on one and only one cell
    Piece Pieces[ 24 ]; 
    
};


#endif

