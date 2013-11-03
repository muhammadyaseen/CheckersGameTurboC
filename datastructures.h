#ifndef DATASTRUCTURES_H
#define	DATASTRUCTURES_H

#define ROW 8
#define COL 8
#define PIECES_COUNT 24    // 12 for 6x6 24 for 8x8
#define WIDTH 75           // Width of each cell
#define HEIGHT 75         // Height of each cell
#define RADIUS 25          // Radius of the pieces
#define DRAW_START_UP 3    // draw piece in first two rows
#define DRAW_START_DOWN 4  // draw piece in last two rows
#define BORDER_COLOR CYAN
#define CHANGE_PIECE 100  //if user has changed selection of piece during a turn
#define TARGET_CLICK_1 1  //return 1 if 1st target was clicked
#define TARGET_CLICK_2 2  //return 2 if 2nd target was clicked
#define NONE -404         //when a cell is not occupied by RED or BLUE
#define VERTICAL_HUDLINE ((COL + 2) * WIDTH) //Hudline will be created after col+2 and with the cell width
#define BOARD_OFFSET 50

// For AI
#define HIGH_PRIORITY 100
#define MODERATE_PRIORITY 50 
#define LOW_PRIORITY 25

enum PieceType { Red, Blue };
enum PieceState { OnBoard, Removed };
//enum GameState { Welcome, Playing, PlayerWin, CPUWin };
enum GameState {Selection, TwoPlayer, VsComputer, Win, Draw};

typedef enum PieceType PieceType;
typedef enum PieceState PieceState;
typedef enum GameState GameState;

typedef struct Board Board;
typedef struct Cell Cell;
typedef struct Piece Piece;
typedef struct Move Move;

typedef struct Board * PtrBoard;
typedef struct Cell * PtrCell;
typedef struct Piece * PtrPiece;
typedef struct Move * PtrMove;

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

struct Move {
    PtrPiece Piece;      // Pointer to the piece that will make the move (subject of move)
    PtrCell CurrentCell; // Pointer to the cell the piece is currently on
    PtrCell TargetCell;  // Pointer to the primary target cell
    PtrCell OtherTargetCells[3]; // Pointer to the secondary target cells
    int isJump;          // Whether the move is a jump or a normal  move
    PtrCell JumpedCell;  // Pointer to the cell that will be jumped over, this is
                         // the cell that'll be jumped as a result of reaching TargetCell
    int movePriority;    // For AI: Indicates how urgent the move is
};

#endif

