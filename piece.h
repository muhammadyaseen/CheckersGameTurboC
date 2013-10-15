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
    //Is this a red or blue piece ?
    PieceType type = color == RED ? Red : Black ;

    // configure the properties of associated cell
    cell->IsOccupied = 1;  //this cell now has a piece belonging to it.
    cell->OccupiedBy = type;

    board->Pieces[pieceNo].IsKing = 0;
    board->Pieces[pieceNo].State = OnBoard;
    board->Pieces[pieceNo].Type = type;
    
    board->Pieces[pieceNo].ID = pieceNo;

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
    setcolor(BLUE);
}

#endif	/* PIECE_H */

