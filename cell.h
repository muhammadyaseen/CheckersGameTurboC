#ifndef CELL_H
#define	CELL_H

#include "datastructures.h"


void DrawCell(PtrCell, int, int);
void IdentifyAndHighlightJumpDestinations(PtrCell *, PtrCell *, PtrCell, int, PtrBoard);


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
PtrCell GetCellByRowColumn(int row, int col,PtrBoard board, int forTarget = FALSE, int turn = 0, int forJumpTarget = FALSE)
{
    if ( row >= ROW || col >= COL )
        return NULL;
    
    for(int i = 0; i < ROW * COL; i++)
    {
        if ( board->Cells[i].Row == row && board->Cells[i].Column == col )
        {
                     
            if (forJumpTarget) 
            {
                //If cell is not occupied (i.e. empty white cell) 
                if ( !board->Cells[i].IsOccupied )
                    return &board->Cells[i];
                else
                    return NULL;
            }
                        
            if (forTarget) 
            {
                //If cell is not occupied (i.e. empty white cell) or cell is occupied by opponent, then this cell is fit as a target
                if ( !board->Cells[i].IsOccupied || board->Cells[i].OccupiedBy != turn )
                    return &board->Cells[i];
                else
                    return NULL;
            }
            
            return &board->Cells[i];
        }
    }
    
    return NULL;
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

int IdentifyAndHighlightTargets(PtrCell clickedCell, PtrMove moves, int *moveCount, int turn, PtrBoard board)
{
    PtrCell target1, target2; //Declaring temporary PtrCells to hold the targets
        
    *moveCount = 0;           // Re-initializing the moveCount so it overwrites 
                              // the existing moveArray
    
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
    else //blue pieces go upwards
    {
        target1Row = clickedCell->Row - 1;
        target2Row = clickedCell->Row - 1;

        target1Col = clickedCell->Column + 1;
        target2Col = clickedCell->Column - 1; 
    }

    target1 = GetCellByRowColumn(target1Row, target1Col, board, TRUE, turn);

    target2 = GetCellByRowColumn(target2Row, target2Col, board, TRUE, turn);
    
    setfillstyle(SOLID_FILL, YELLOW);

    //if both targets are null, user must again select the piece to complete the move
    if ( (target1) == NULL && (target2) == NULL )
       return FALSE;
    
    PtrCell jumpDest1 = (PtrCell) NULL; //in case target1 has an opponent cell this represents destination after jump
    PtrCell jumpDest2 = (PtrCell) NULL; //in case target2 has an opponent cell this represents destination after jump
    
    outtextxy(610, 250, "Iding dest 1 not null");
    
    // If targets are not null, we figure out whether they are jumps or not in advance
    if ( target1 != NULL)
        IdentifyAndHighlightJumpDestinations(&target1, &jumpDest1, clickedCell, turn, board );
    
    if ( target2 != NULL)
        IdentifyAndHighlightJumpDestinations(&target2, &jumpDest2, clickedCell, turn, board );
    
    //in case of empty white cells
    if ( (target1) != NULL && (target1)->IsOccupied == FALSE )
    {
        // Color the destination square
        floodfill( (target1)->Left + 1, (target1)->Bottom - 1 , BORDER_COLOR );
        
        // Details of the move
        moves[*moveCount].CurrentCell = clickedCell;
        moves[*moveCount].TargetCell = target1;
        moves[*moveCount].isJump = FALSE;
        
        // If the other move was a jump, then assign the appropriate cell, else if
        // the other move was a normal move, then do the same.
        
        //the other target for this move could be a jump or a normal move,
        //if it is jump, then jumpDest2 must be non-NULL, (target2 is also non-NULL, but in 
        // case of jump we go one diagonal ahead, so actual destination is jumpDest, not target)
        //if it is not a jump but a normal move target2 must be non-NULL
        
        //Note: If both jumpDest2 and target2 are NULL, OtherTargetCell will have a garbage value
        if (jumpDest2 != NULL) 
            moves[*moveCount].OtherTargetCell = jumpDest2;
        else if (target2 != NULL)
            moves[*moveCount].OtherTargetCell = target2;
        
        (*moveCount) += 1;
    }
    
    if ( (target2) != NULL && (target2)->IsOccupied == FALSE )
    {
        // Color the destination square
        floodfill( (target2)->Left + 1, (target2)->Bottom - 1 , BORDER_COLOR );
        
        // Details of the move
        moves[*moveCount].CurrentCell = clickedCell;
        moves[*moveCount].TargetCell = target2;
        moves[*moveCount].isJump = FALSE;

        // If the other move was a jump, then assign the appropriate cell, else if
        // the other move was a normal move, then do the same.
        if (jumpDest1 != NULL) moves[*moveCount].OtherTargetCell = jumpDest1;
        else if (target1 != NULL) moves[*moveCount].OtherTargetCell = target1;
        
        (*moveCount) += 1;
    }

    //in case when white cell is occupied by opponent piece
    //we need to figure out whether this cell could be jumped over or not.

    //In case of a jump, 'target1' and 'target2' represent the cell (or pieces) that will be jumped over,
    //i.e. the final target or destination of the move is one diagonal ahead of  'target1' and 'target2'
    //we must make sure that that "final target or destination" is available for the move to be considered
    //valid and possible
    //   T |  | T
    //   ---------
    //     | J|   
    //   ---------
    //   X |  | X
    // depending on the position and color of X the destination 'T' for a piece 'X' that jumps over 'J' could be different 

    //there are two "final destinations" because there could be two jumps possible
    //for ex, both 'target1' and 'target2' have an opponent cell
    
    if ( jumpDest1 != NULL )
    {
       outtextxy(610, 320, "Dest 1 not null");
       
       // jumpDest is this destination and JumpedCell was the target
       // Details of the jump are being loaded into the move struct
       moves[*moveCount].CurrentCell = clickedCell;
       moves[*moveCount].TargetCell = jumpDest1;
       moves[*moveCount].isJump = TRUE;
       moves[*moveCount].JumpedCell = target1;
       
       // If the other move was a jump, then assign the appropriate cell, else if
       // the other move was a normal move, then do the same.
       if (jumpDest2 != NULL) moves[*moveCount].OtherTargetCell = jumpDest2;
       else moves[*moveCount].OtherTargetCell = target2;
       
       (*moveCount) += 1;
    }
    else
    {
       outtextxy(610, 320, "Dest 1 is null");
       if ( target1 != NULL && target1->IsOccupied ) (target1) = NULL;
    }

    if ( jumpDest2 != NULL )
    {
       outtextxy(620, 340, "Dest 2 not null");
       
       // jumpDest is this destination and JumpedCell was the target
       // Details of the jump are being loaded into the move structure
       moves[*moveCount].CurrentCell = clickedCell;
       moves[*moveCount].TargetCell = jumpDest2;
       moves[*moveCount].isJump = TRUE;
       moves[*moveCount].JumpedCell = target2;
       
       // If the other move was a jump, then assign the appropriate cell, else if
        // the other move was a normal move, then do the same.
       if (jumpDest1 != NULL) moves[*moveCount].OtherTargetCell = jumpDest1;
       else moves[*moveCount].OtherTargetCell = target1;
       
       (*moveCount) += 1;
    }
    else
    {
       outtextxy(620, 340, "Dest 2 is null");
       if ( target2 != NULL && target2->IsOccupied ) (target2) = NULL;
    }

    return TRUE;
    //now, targets have been identified and highlighted
}

int InterceptTargetClicks(PtrCell * clickedTarget, PtrMove moves, int *moveCount, int * targetX, int * targetY, int turn, PtrBoard board)
{   
    getmouseclick(WM_LBUTTONDOWN, *targetX, *targetY);

    if ( ! ( *targetX == -1 && *targetY == -1 ) )
    {
       //check whether the correct target is selecting using X,Y co-ords

       *clickedTarget = GetClickedCell(*targetX, *targetY, board );

       if ( (*clickedTarget) != NULL ) //this check ensures that at least user clicked on a 'cell' and no where else on screen
       {
           //now we can check whether the clicked cell was one of the target cells
           //one of the two target cells could be null
           for (int i = 0; i < *moveCount; i++)
           {    
               if( moves[i].TargetCell != NULL && ( (*clickedTarget)->Row == moves[i].TargetCell->Row && (*clickedTarget)->Column == moves[i].TargetCell->Column ) )
               {
                   //target one was selected as destination
                   outtextxy(550, 60, "target 1");
                   //return TRUE;
                   return (i+1); // +1 to break out of the while loop
               } 
           }
           
           //user clicked on a non-target / non-highlighted cell

           //1. User clicked on an other piece (To select a different piece for move)
           //   In this case, we should Re-Identify the targets for newly selected piece              

           //Identify if a piece whose 'turn' it is was selected or some other thing

           if ( (*clickedTarget)->OccupiedBy == turn)
           {
               //user has selected an other piece, i.e. user wants to move this piece instead of the previously selected piece
               //we need to identify targets for this new piece
               outtextxy(550, 80, "change subject");

               //redraw target cells in normal white color
               for (int i = 0; i < *moveCount; i++)
               {
                   if ( moves[i].TargetCell != NULL) 
                       DrawCell( moves[i].TargetCell, moves[i].TargetCell->Row, moves[i].TargetCell->Column );
               }

               return CHANGE_PIECE;
           }
           
           outtextxy(550, 80, "non target");
           return FALSE;   
       }
    }
    
    return FALSE;
}

/* @descripton - It highlights the final locations of piece in case of a jump move, It also determines whether a jump is possible or not. See @note
 * @param - jumpedOverCell - This is the cell that 'would be' jumped over if the conditions are true i.e. it is not yet confirmed that
 *                           this cells is appropriate for jump
 * @param - finalDestination - Represents the final location where the piece will be moved to as a result of move, 
 *                           in case of jump, it is one diagonal ahead of the jumpedOverCell
 * @param - clickedCell - Represents the either the jumpedOverCell or target of a move, in case of jump and normal move respectively
 * 
 * @note - if for this 'jumpedOverCell', 'finalDestination' is not avaialable i.e. to say jump isn't possible, 'finalDestination' will be NULL
 * 
 */
void IdentifyAndHighlightJumpDestinations(PtrCell * jumpedOverCell, PtrCell * finalDestination, PtrCell clickedCell, int turn, PtrBoard board)
{
    if ( (*jumpedOverCell) != NULL && (*jumpedOverCell)->IsOccupied && (*jumpedOverCell)->OccupiedBy != turn )
    {   
           //calculate the co-ords of final destination for the jump
           
           if ( turn == BLUE ) //blue pieces go up
           {
               if ( clickedCell->Column < (*jumpedOverCell)->Column )
               {
                   //target is two rows forward and two columns right
                   
                   (*finalDestination) = GetCellByRowColumn( clickedCell->Row - 2, clickedCell->Column + 2, board, FALSE, turn, TRUE );
                   
                   //if this isnt null, highlight this cell
                   //make this cell the destination cell for MovePiece
                   
                   if ( (*finalDestination) != NULL )
                   {
                       setfillstyle(SOLID_FILL, YELLOW);
                       floodfill( (*finalDestination)->Left + 1, (*finalDestination)->Bottom - 1 , BORDER_COLOR );
                   }
               }
               
               if ( clickedCell->Column > (*jumpedOverCell)->Column )
               {
                   //target is two rows forward and two columns left
                   
                    (*finalDestination) = GetCellByRowColumn( clickedCell->Row - 2, clickedCell->Column - 2, board, FALSE, turn, TRUE );
                                     
                   //if this isnt null, highlight this cell
                   //make this cell the destination cell for MovePiece
                   
                   if ( (*finalDestination) != NULL )
                   {
                       setfillstyle(SOLID_FILL, YELLOW);
                       floodfill( (*finalDestination)->Left + 1, (*finalDestination)->Bottom - 1 , BORDER_COLOR );
                   }
               }
           }
           
           if ( turn == RED ) //red pieces go down
           {
               if ( clickedCell->Column < (*jumpedOverCell)->Column )
               {
                   //target is two rows below and two columns right
                   
                   (*finalDestination) = GetCellByRowColumn( clickedCell->Row + 2, clickedCell->Column + 2, board, FALSE, turn, TRUE );
                   
                   //if this isnt null, highlight this cell
                   //make this cell the destination cell for MovePiece
                   
                   if ( (*finalDestination) != NULL )
                   {
                       setfillstyle(SOLID_FILL, YELLOW);
                       floodfill( (*finalDestination)->Left + 1, (*finalDestination)->Bottom - 1 , BORDER_COLOR );
                   }
               }
               
               if ( clickedCell->Column > (*jumpedOverCell)->Column )
               {
                   //target is two rows below and two columns right
                   
                    (*finalDestination) = GetCellByRowColumn( clickedCell->Row + 2, clickedCell->Column - 2, board, FALSE, turn, TRUE );
                                     
                   //if this isnt null, highlight this cell
                   //make this cell the destination cell for MovePiece
                   
                   if ( (*finalDestination) != NULL )
                   {
                       setfillstyle(SOLID_FILL, YELLOW);
                       floodfill( (*finalDestination)->Left + 1, (*finalDestination)->Bottom - 1 , BORDER_COLOR );
                   }
               }
           }
       }
}

void PrintRC(PtrCell cell, int x, int y)
{
    char * r = (char *)malloc( 5 );
    char * c = (char *)malloc( 5 );
    
    if ( cell != (PtrCell)NULL )  
    {
        outtextxy(x,y, "Row : " );
        outtextxy(x+50,y, itoa(cell->Row,r, 10) );
        
        outtextxy(x,y+20, "Col : " );
        outtextxy(x+50,y+20, itoa(cell->Column,c,10) );
    }
    else
    {
        outtextxy(x, y, "Row : N");
        outtextxy(x,y+20, "Col : N" );
    }
}

#endif	/* CELL_H */

