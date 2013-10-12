#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#include "datastructures.h"
#include "cell.h"
#include "piece.h"
#include "board.h"

Board CheckersBoard;

int main(void)
{
   int mode, driver = DETECT;
   
   initgraph(&driver, &mode, NULL); 
   
   //Draws the initial state of board
   DrawBoard( &CheckersBoard );
   
   getche();
   closegraph();
   
   return 0;
}