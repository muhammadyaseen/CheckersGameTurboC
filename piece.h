#ifndef PIECE_H
#define	PIECE_H

#include "datastructures.h"

void DrawPiece(PtrBoard, PtrCell, int, int);

/* 
 * @description : Used to draw the piece, This can be called anywhere you need to draw a piece.
 * 
 * @param - board - Address of the global struct Board variable. We use it to 'fill' in the array entries, as we build the piece
 * @param - cell - Address of the cell to which this piece belongs
 * @param - pieceNo - Index of this piece in the Pieces array in Board struct
 * @param - Color used to draw this piece
 * 
 */

void DrawPiece(PtrBoard board, PtrCell cell, int pieceNo, int color)
{    
    //store a reference to the cell in piece array
    board->Pieces[pieceNo].Cell = cell;
    
    //Is this a red or blue piece ?
    int type = color == RED ? RED : BLUE ;

    // configure the properties of associated cell
    cell->IsOccupied = 1;  //this cell now has a piece belonging to it.
    cell->OccupiedBy = type;

    board->Pieces[pieceNo].IsKing = 0;
    board->Pieces[pieceNo].State = OnBoard;
    board->Pieces[pieceNo].Type = type;
    
    board->Pieces[pieceNo].Index = pieceNo;

    //store a reference to this piece in cell
    cell->Piece = &board->Pieces[pieceNo];
    
    //set draw color of circle / piece
    setcolor(color);

    //center of circle; this is also used as seed point
    int circleX = (cell->Left  + cell->Right) / 2;
    int circleY = (cell->Top + cell->Bottom) / 2;

    //draws the circle for this piece
    circle( circleX ,circleY, RADIUS  );

    setfillstyle(SOLID_FILL, color);

    floodfill( circleX, circleY, color );
    
    // reset draw color to draw the next rectangle / cell
    setcolor(BORDER_COLOR);
}

void MovePiece(PtrBoard board, PtrCell clickedCell , PtrCell clickedTarget, PtrCell target1, PtrCell target2, int turn)
{
    //change prev cell data
               
    clickedCell->IsOccupied = FALSE;

    //change target cell data

    clickedTarget->Piece = clickedCell->Piece;
    clickedTarget->IsOccupied = TRUE;
    clickedTarget->OccupiedBy = turn;

    clickedCell->Piece = NULL;

    //re draw prev cell

    DrawCell( clickedCell, clickedCell->Row, clickedCell->Column );

    //redraw target cells in normal white color

    if ( target1 != NULL) DrawCell( target1, target1->Row, target1->Column );
    if ( target2 != NULL) DrawCell( target2, target2->Row, target2->Column );

    //draw piece on target cell

    DrawPiece( board, clickedTarget, clickedTarget->Piece->Index, turn );
    
}

void MovePieceForAI(PtrBoard board, PtrCell selectedCell , PtrCell target, int turn)
{
    //change previous cell data               
    selectedCell->IsOccupied = FALSE;

    //change target cell data
    target->Piece = selectedCell->Piece;
    target->IsOccupied = TRUE;

    selectedCell->Piece = NULL;

    //re draw previous cell
    DrawCell( selectedCell, selectedCell->Row, selectedCell->Column );

    //redraw target cells in normal white color

//    if ( target1 != NULL) DrawCell( target1, target1->Row, target1->Column );
//    if ( target2 != NULL) DrawCell( target2, target2->Row, target2->Column );

    //draw piece on target cell
    DrawPiece( board, target, target->Piece->Index, turn );
    
}

void PlayAITurn(PtrBoard board, int turn)
{         
    // Array to hold all the pieces the AI can control
    Piece redPieceCells[ PIECES_COUNT/2 ];
    
    int numberOfPieces = 0; // Holds the number of pieces for use in for loops
    
    // Goes through all the pieces on the board
    for (int i = 0; i < (ROW * COL); i++)
    {   
        // Checks to see if the piece color is indeed blue and on the
        // the board, that is not removed or "jumped over".
        if (board->Pieces[i].Type == Blue &&   
            board->Pieces[i].State == OnBoard)
        {
            redPieceCells[ numberOfPieces++ ] =  board->Pieces[i];
        }
    
    } // End of RedPieces gathering for-loop
    
    Moves possibleMoves[numberOfPieces * 2];
    int numberOfMoves = 0;
    
    PtrCell target1, target2;
    
    for (int i = 0; i < numberOfPieces; i++)
    {
        // Enters when the function does return targets
        if (IdentifyTargets(turn, redPieceCells[i].Cell, &target1, &target2, board))
        {
            // If a target exists, it stores all the data in the PossibleMoves 
            // array
            if ( !(target1 == NULL) )
            {
                possibleMoves[numberOfMoves].Piece = &redPieceCells[i];
                possibleMoves[numberOfMoves].CurrentCell = redPieceCells[i].Cell;
                possibleMoves[numberOfMoves].TargetCell = target1;
                
                numberOfMoves++;
            }
            
            if ( !(target2 == NULL) )
            {
                possibleMoves[numberOfMoves].Piece = &redPieceCells[i];
                possibleMoves[numberOfMoves].CurrentCell = redPieceCells[i].Cell;
                possibleMoves[numberOfMoves].TargetCell = target2;
                
                numberOfMoves++;
            }
        }
        
    } // End of PossibleMoves calculating for-loop
    
    // Randomly select a move
    int moveIndex = rand() % numberOfMoves;
    
    // Moves the piece
    MovePieceForAI(board, possibleMoves[moveIndex].CurrentCell,
                   possibleMoves[moveIndex].TargetCell, turn);
}

//created 'jump' branch

#endif	/* PIECE_H */

