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

/* @description : When in game loop we use this func to determine which cell was clicked.
 * 
 * @param - X - X co-ord of mouse position when click occurred
 * @param - Y - Y co-ord of mouse position when click occurred
 * @param - board - Pointer to main checkers board instance
 */

PtrCell GetClickedCell(int X, int Y, PtrBoard board)
{
    for(int i = 0; i < ROW * COL; i++)
    {
        //if X and Y lie ( not in that sense :) ) with in the rectangle of this cell
        //Or if mathematics is more natural to you, we're testing this inequality :
        // left < X < Right   AND  top < Y < bottom
        
        if ( board->Cells[i].Left < X && board->Cells[i].Right > X && board->Cells[i].Top < Y && board->Cells[i].Bottom > Y )
        {
            //draws the cross
            line(board->Cells[i].Left, board->Cells[i].Top, board->Cells[i].Right, board->Cells[i].Bottom );
            line(board->Cells[i].Right, board->Cells[i].Top, board->Cells[i].Left, board->Cells[i].Bottom );
            
            return &board->Cells[i];
        
        }
    }
    
    return NULL;
}


/* @description : Used to get a particular cell referenced by row and column
 * 
 * @param - row - Row of cell to get
 * @param - col - Column of cell to get
 * @param - forTarget - This tells the function whether this Cell is required to be 
 *                      used as a 'target' for a move (and hence we need some additional
 *                      rule checking) or for some other purpose.
 * @param - board - Pointer to main checkers board instance
 */
PtrCell GetCellByRowColumn(int row, int col,PtrBoard board, int forTarget = FALSE )
{
    if ( row >= ROW || col >= COL )
        return NULL;
    
    for(int i = 0; i < ROW * COL; i++)
    {
        if ( board->Cells[i].Row == row && board->Cells[i].Column == col )
        {
            //TODO: Check for 'OccupiedBy' before returning
            if (forTarget) 
            {
                if ( ! board->Cells[i].IsOccupied )
                    return &board->Cells[i];
                else
                    return NULL;
            }
            
            return &board->Cells[i];
        }
    }
}


int IdentifyAndHighlightTargets(int turn, PtrCell clickedCell, PtrCell *target1, PtrCell *target2, PtrBoard board)
{
       //identify targets : Piece can only move in diagonals ( in white cells )

       //max 2 targets are possible for a move, minimum 0

       int target1Row, target2Row, target1Col, target2Col;

       if ( turn == RED )   //red piece go downwards
       {
            target1Row = clickedCell->Row + 1;
            target2Row = clickedCell->Row + 1;

            target1Col = clickedCell->Column + 1;
            target2Col = clickedCell->Column - 1;    
       }
       else //blue pieces go downwards
       {
            target1Row = clickedCell->Row - 1;
            target2Row = clickedCell->Row - 1;

            target1Col = clickedCell->Column + 1;
            target2Col = clickedCell->Column - 1; 
       }

       *target1 = GetCellByRowColumn(target1Row, target1Col, board, TRUE);

       *target2 = GetCellByRowColumn(target2Row, target2Col, board, TRUE);

       setfillstyle(SOLID_FILL, YELLOW);

       //if both targets are null, user must again select the piece to complete the move
       if ( target1 == NULL && target2 == NULL )
           return FALSE;

       if ( (*target1) != NULL && (*target1)->IsOccupied == 0 )
       {
            floodfill( (*target1)->Left + 1, (*target1)->Bottom - 1 , BLUE );
       }
       if ( (*target2) != NULL && (*target2)->IsOccupied == 0 )
       {
            floodfill( (*target2)->Left + 1, (*target2)->Bottom - 1 , BLUE );
       }

       return TRUE;
       //now, targets have been identified and highlighted

}
#endif	/* CELL_H */

