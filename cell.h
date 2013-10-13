#ifndef CELL_H
#define	CELL_H

#include "datastructures.h"


void DrawCell(PtrCell, int, int);

/* @description : Used to draw the rectangular ceell on board.
 * 
 * @param -  cellToDraw - Address of the configured struct Cell instance to be drawn
 * @param - row - The row in which this cell should be drawn
 * @param - col - The column in which this cell should be drawn
 */

void DrawCell(PtrCell cellToDraw, int row, int col)
{
    rectangle( cellToDraw->Left, cellToDraw->Top, cellToDraw->Right, cellToDraw->Bottom );
    
    //determines whether the drawn cell is white or black
    //Condition is true in case of white cells only
    
    if ( (col + row )  % 2 == 0)
    {
        int seedX = cellToDraw->Right - 1;
        int seedY =  cellToDraw->Bottom - 1;
                
        setfillstyle(SOLID_FILL, WHITE);
        
        floodfill( seedX, seedY, BLUE );       
    }
}


PtrCell GetClickedCell(int X, int Y, PtrBoard board)
{
    for(int i = 0; i < ROW * COL; i++)
    {
        //if X and Y lies with in the rectangle of this cell
        // left < X < Right   AND  top < Y < bottom
        
        if ( board->Cells[i].Left < X && board->Cells[i].Right > X && board->Cells[i].Top < Y && board->Cells[i].Bottom > Y )
        {
            
            line(board->Cells[i].Left, board->Cells[i].Top, board->Cells[i].Right, board->Cells[i].Bottom );
            line(board->Cells[i].Right, board->Cells[i].Top, board->Cells[i].Left, board->Cells[i].Bottom );
            
            return &board->Cells[i];
        
        }
    }
}

PtrCell GetCellByRowColumn(int row, int col,PtrBoard board)
{
    for(int i = 0; i < ROW * COL; i++)
    {
        //if X and Y lies with in the rectangle of this cell
        // left < X < Right   AND  top < Y < bottom
        
        if ( board->Cells[i].Row == row && board->Cells[i].Column == col )
        {
            return &board->Cells[i];   
        }
    }

}

#endif	/* CELL_H */

