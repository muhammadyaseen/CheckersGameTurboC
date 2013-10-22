#ifndef DATASTRUCTURES_H
#define	DATASTRUCTURES_H

#define ROW 8
#define COL 8
#define PIECES_COUNT 24    // 12 for 6x6 24 for 8x8
#define WIDTH 75           // Width of each cell
#define HEIGHT 75          // Height of each cell
#define RADIUS 25          // Radius of the pieces
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
typedef struct Moves Moves;

typedef struct Board * PtrBoard;
typedef struct Cell * PtrCell;
typedef struct Piece * PtrPiece;


struct Cell {
    int Index;
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
    
    int Index;
    int Type;
    int IsKing;
    PieceState State;
    
    //cell on which this piece is currently on
    PtrCell Cell;
    
};

struct Board {
    
    Cell Cells[ ROW * COL ];
    
    //Each piece can be on one and only one cell
    Piece Pieces[ PIECES_COUNT ]; 
    
};

struct Moves {
    PtrPiece Piece;      // Pointer to the piece that will make the move (subject of move)
    PtrCell TargetCell;  // Pointer to the cell the piece will be moved to
    PtrCell CurrentCell; // Pointer to the cell the piece is currently on
};

#endif

