#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "Enums&Structs.h"
#include "DrawFunctions.h"
#include "MoveFunctions.h"

/*Copy  this part of the code in every header file*/
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

enum GameState { Welcome, Playing, PlayerWin, CPUWin };

typedef enum GameState GameState;

int main(void)
{
   int mode, driver = DETECT;
   initgraph(&driver, &mode, NULL); 
   
   DrawBoard( &CheckersBoard );
   
   getche();
   closegraph();
   
   return 0;
}