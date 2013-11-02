#ifndef BOARD_H
#define	BOARD_H

#include "datastructures.h"


void DrawBoard(PtrBoard);

/* 
 * @description : Used to draw the initial state of board when the game starts
 * 
 * @param - board - Address of the global struct Board variable. We use it to 'fill' in the array entries, as we build cells and pieces
 * 
 */

void DrawBoard(PtrBoard board)
{
   //Cells will be of blue border   
   setcolor(BORDER_COLOR);
   
   //goes from 0 to ROW*COL, we are using it to keep track / index of cells array in board
   int cellNo = 0;
   
   //goes from 0 to 12 (for 8 x 8), we are using it to keep track /index of pieces array in board
   int pieceNo = 0;
   
   for(int row = 0; row < ROW; row++)
   {     
       for(int col = 0; col < COL; col++)
        {
           // configure the cell properties so that it can be drawn
            board->Cells[cellNo].Left = WIDTH * col + BORAD_OFFSET;
            board->Cells[cellNo].Top = HEIGHT * row  + BORAD_OFFSET;
            board->Cells[cellNo].Right = WIDTH * (1+col)  + BORAD_OFFSET;
            board->Cells[cellNo].Bottom =  HEIGHT * (1+row)  + BORAD_OFFSET;
            board->Cells[cellNo].Index = cellNo;
            
            board->Cells[cellNo].IsOccupied = FALSE;
            board->Cells[cellNo].OccupiedBy = NONE;
            
            board->Cells[cellNo].Row = row;
            board->Cells[cellNo].Column = col;
            
            
            //Draws the cell configured above
            DrawCell( &board->Cells[cellNo], row, col );
            
            // if it is a 'white' cell      AND        this row should have Pieces 
            if ( ( (col + row )  % 2 != 0 ) && ( row < DRAW_START_UP || row > DRAW_START_DOWN) )
            {
                // pieces in first two rows are red, last two rows they're blue
                int drawColor = row < DRAW_START_UP ? RED : BLUE;
                
                DrawPiece(board, &board->Cells[cellNo], pieceNo++, drawColor);
            }
            
            cellNo++;
            
        }
   }
}

#endif	/* BOARD_H */

