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
    
    if ( (col + row )  % 2 != 0)
    {
        int seedX = cellToDraw->Right - 1;
        int seedY =  cellToDraw->Bottom - 1;
                
        setfillstyle(SOLID_FILL, WHITE);
        
        floodfill( seedX, seedY, BORDER_COLOR );       
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
            //line(board->Cells[i].Left, board->Cells[i].Top, board->Cells[i].Right, board->Cells[i].Bottom );
            //line(board->Cells[i].Right, board->Cells[i].Top, board->Cells[i].Left, board->Cells[i].Bottom );
            
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

int IdentifyTargets(int turn, PtrCell selectedCell, PtrCell *target1, PtrCell *target2, PtrBoard board)
{
       //identify targets : Piece can only move in diagonals ( in white cells )

       //max 2 targets are possible for a move, minimum 0

       int target1Row, target2Row, target1Col, target2Col;

       if ( turn == RED )   //red piece go downwards
       {
            target1Row = selectedCell->Row + 1;
            target2Row = selectedCell->Row + 1;

            target1Col = selectedCell->Column + 1;
            target2Col = selectedCell->Column - 1;    
       }
       else //blue pieces go downwards
       {
            target1Row = selectedCell->Row - 1;
            target2Row = selectedCell->Row - 1;

            target1Col = selectedCell->Column + 1;
            target2Col = selectedCell->Column - 1; 
       }

       *target1 = GetCellByRowColumn(target1Row, target1Col, board, TRUE);

       *target2 = GetCellByRowColumn(target2Row, target2Col, board, TRUE);

       // If both targets are null, user must again select the piece to complete the move
       if ( (*target1) == NULL && (*target2) == NULL )
           return FALSE;
       
       return TRUE;
       //now, targets have been identified and highlighted
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

       // If both targets are null, user must again select the piece to complete the move
       if ( (*target1) == NULL && (*target2) == NULL )
           return FALSE;
       
       // If either of the target exists and is not occupied
       setfillstyle(SOLID_FILL, YELLOW);

       if ( (*target1) != NULL && (*target1)->IsOccupied == 0 )
       {
            floodfill( (*target1)->Left + 1, (*target1)->Bottom - 1 , BORDER_COLOR );
       }
       
       if ( (*target2) != NULL && (*target2)->IsOccupied == 0 )
       {
            floodfill( (*target2)->Left + 1, (*target2)->Bottom - 1 , BORDER_COLOR );
       }

       return TRUE;
       //now, targets have been identified and highlighted

}

int InterceptTargetClicks(PtrCell *clickedTarget, PtrCell target1, PtrCell target2, PtrBoard board)
{
    int targetX, targetY;
    getmouseclick(WM_LBUTTONDOWN, targetX, targetY);

    if ( ! ( targetX == -1 && targetY == -1 ) )
    {
       //check whether the correct target is selecting using X,Y co-ords

       *clickedTarget = GetClickedCell(targetX, targetY, board );

       if ( (*clickedTarget) != NULL ) //this check ensures that at least user clicked on a 'cell' and no where else on screen
       {
           //now we can check whether the clicked cell was one of the target cells
           //one of the two target cells could be null
           
           if( target1 != NULL && ( (*clickedTarget)->Row == target1->Row && (*clickedTarget)->Column == target1->Column ) )
           {
               //target one was selected as destination
               outtextxy(550, 60, "target 1");
               return TRUE;

           } 
           else if (  target2 != NULL && ( (*clickedTarget)->Row == target2->Row && (*clickedTarget)->Column == target2->Column ) )
           {
               //target one was selected as destination
               outtextxy(550, 70, "target 2");
               return TRUE;
           }
           else
           {
               //user clicked on a non-target / non-highlighted cell
               outtextxy(550, 80, "non target");
               return FALSE;
           }
       }
    }
    
    return FALSE;
}
#endif	/* CELL_H */

