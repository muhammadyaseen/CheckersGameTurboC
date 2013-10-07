#ifndef PIECE_H
#define	PIECE_H

void DrawPiece(PtrBoard, PtrCell, int, int);



void DrawPiece(PtrBoard board, PtrCell cell, int pieceNo, int color)
{
    PieceType type = color == RED ? Red : Black ;

    // configure the properties of associated cell
    cell->IsOccupied = 1;
    cell->OccupiedBy = type;

    board->Pieces[pieceNo].IsKing = 0;
    board->Pieces[pieceNo].State = OnBoard;
    board->Pieces[pieceNo].Type = type;

    //store a reference to this piece in cell
    cell->Piece = &board->Pieces[pieceNo];
    
    //set draw color of circle / piece
    setcolor(color);

    //center of circle also used as seed
    int circleX = (cell->Left  + cell->Right) / 2;
    int circleY = (cell->Top + cell->Bottom) / 2;

    circle( circleX ,circleY, 20  );

    setfillstyle(SOLID_FILL, color);

    floodfill( circleX, circleY, color );
    
    // reset draw color to draw the next rectangle / cell
    setcolor(BLUE);
}

#endif	/* PIECE_H */

