#ifndef PIECE_H
#define	PIECE_H

#include "datastructures.h"

//void DrawPiece(PtrBoard, PtrCell, int, int);

/* 
 * @description : Used to draw the piece, This can be called anywhere you need to draw a piece.
 * 
 * @param - board - Address of the global struct Board variable. We use it to 'fill' in the array entries, as we build the piece
 * @param - cell - Address of the cell to which this piece belongs
 * @param - pieceNo - Index of this piece in the Pieces array in Board struct
 * @param - Color used to draw this piece
 * 
 */

void DrawPiece(PtrBoard board, PtrCell cell, int pieceNo, int color, int isKing = FALSE)
{    
    //store a reference to the cell in piece array
    board->Pieces[pieceNo].Cell = cell;
    
    //Is this a red or blue piece ?
    int type = color == RED ? RED : BLUE ;

    // configure the properties of associated cell
    cell->IsOccupied = TRUE;  //this cell now has a piece belonging to it.
    cell->OccupiedBy = type;

    board->Pieces[pieceNo].IsKing = isKing; //we also set this param in MovePiece function
    board->Pieces[pieceNo].State = OnBoard;
    board->Pieces[pieceNo].Type = type;
        
    board->Pieces[pieceNo].Index = pieceNo;

    //store a reference to this piece in cell
    cell->Piece = &board->Pieces[pieceNo];
    
    //test code
    if (cell->Row == 2 && cell->Column == 3) cell->Piece->IsKing = TRUE;
    
    if (cell->Row == 5 && cell->Column == 4) cell->Piece->IsKing = TRUE;
    //end test code
    
    //set draw color of circle / piece
    setcolor(color);

    //center of circle; this is also used as seed point
    int circleX = (cell->Left  + cell->Right) / 2;
    int circleY = (cell->Top + cell->Bottom) / 2;

    //draws the circle for this piece
    circle( circleX ,circleY, RADIUS  );

    setfillstyle(SOLID_FILL, color);

    floodfill( circleX, circleY, color );
    
    //delay(150);
    
    //if the cell contains a kinged piece
    
    if (cell->Piece->IsKing)
    {
        //draws the circle for king indication        
        setcolor(WHITE);
        circle( circleX ,circleY, RADIUS / 4);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill( circleX, circleY, WHITE );
    }
    
    // reset draw color to draw the next rectangle / cell
    setcolor(BORDER_COLOR);
}

/* @description - Moves the piece from its current location to a new location during a move
 * 
 * @paramm - board - pointer to board state
 * @param - clickedCell - pointer to the cell user selected with mouse click
 * @param - target1 - represents one of the possible target cells user might selection as destination of the move
 * @param - target2 - represents one of the possible target cells user might selection as destination of the move
 * @paraam - clickedTarget - represents the cell user has selected as target / destination
 * @param - turn - color of piece whose turn it is
 */
void MovePiece(PtrMove move, int turn, PtrBoard board)
{
    //change previous cell data
    move->CurrentCell->IsOccupied = FALSE;

    //change target cell data

    move->TargetCell->Piece = move->CurrentCell->Piece;
    move->TargetCell->IsOccupied = TRUE;
    move->TargetCell->OccupiedBy = turn;

    move->CurrentCell->Piece = NULL;
    move->CurrentCell->OccupiedBy = NONE;

    //re draw prev cell

    DrawCell( move->CurrentCell, move->CurrentCell->Row, move->CurrentCell->Column );

    //redraw target cells in normal white color

    if ( move->TargetCell != NULL) DrawCell( move->TargetCell, move->TargetCell->Row, move->TargetCell->Column );
    if ( move->OtherTargetCell != NULL && move->OtherTargetCell->IsOccupied == FALSE) 
        DrawCell( move->OtherTargetCell, move->OtherTargetCell->Row, move->OtherTargetCell->Column );
    
    int isKing = FALSE;
    
    //determine if the piece is kinged or not, piece is kinged if it reaches the opposite end of the board
    
    if ( turn == RED && move->TargetCell->Row == 7 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }
    if ( turn == BLUE && move->TargetCell->Row == 0 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }

    //draw piece on target /destination cell
    DrawPiece( board, move->TargetCell, move->TargetCell->Piece->Index, turn, isKing );
    
    // If the move is a jump, then the JumpedCell needs to be updated as well
    if (move->isJump)
    {
       DrawCell(move->JumpedCell, move->JumpedCell->Row, move->JumpedCell->Column);
       move->JumpedCell->Piece->State = Removed;
       move->JumpedCell->Piece = NULL;
       move->JumpedCell->IsOccupied = FALSE;
       move->JumpedCell->OccupiedBy = 0;
    }
    
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
    
    Move possibleMoves[numberOfPieces * 2];
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

/*  @description - Used to draw the (sort of) score board, indicating how many pieces are 'OnBoard' of a particular type
 *
 */

void DrawIndicator(PtrBoard board)
{
    char * numberRed = (char *)malloc( 3 );
    char * numberBlue = (char *)malloc( 3 );
    
    int bluePieces = 0, redPieces = 0;
    
    for ( int i = 0; i < PIECES_COUNT; i++)
    {
        if ( board->Pieces[i].Type == BLUE && board->Pieces[i].State == OnBoard )
            bluePieces++;
        
        if ( board->Pieces[i].Type == RED && board->Pieces[i].State == OnBoard )
            redPieces++;
    }
    
    int x = 650, y = 500;
    
    outtextxy(x, y, "RED : ");
    outtextxy( x, y+30, itoa(redPieces, numberRed, 10) );
    
    outtextxy(x, y+60, "BLUE : ");
    outtextxy( x, y+90, itoa(bluePieces, numberBlue, 10) );
    
    free(numberRed);
    free(numberBlue);
}

void MovePieceY(PtrMove move, int turn, PtrBoard board)
{
    //change previous cell data
    move->CurrentCell->IsOccupied = FALSE;

    //change target cell data

    move->TargetCell->Piece = move->CurrentCell->Piece;
    move->TargetCell->IsOccupied = TRUE;
    move->TargetCell->OccupiedBy = turn;

    move->CurrentCell->Piece = NULL;
    move->CurrentCell->OccupiedBy = NONE;

    //re draw prev cell

    DrawCell( move->CurrentCell, move->CurrentCell->Row, move->CurrentCell->Column );

    //redraw target cells in normal white color

    if ( move->TargetCell != NULL) DrawCell( move->TargetCell, move->TargetCell->Row, move->TargetCell->Column );
    
//    if ( move->OtherTargetCell != NULL && move->OtherTargetCell->IsOccupied == FALSE) 
//        DrawCell( move->OtherTargetCell, move->OtherTargetCell->Row, move->OtherTargetCell->Column );
    
    for(int t = 0; t < 4; t++)
    {
        if ( move->OtherTargetCells[t] != NULL )
            DrawCell( move->OtherTargetCells[t], move->OtherTargetCells[t]->Row, move->OtherTargetCells[t]->Column );
    }
    
    int isKing = FALSE;
    
    //determine if the piece is kinged or not, piece is kinged if it reaches the opposite end of the board
    
    if ( turn == RED && move->TargetCell->Row == 7 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }
    if ( turn == BLUE && move->TargetCell->Row == 0 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }

    //draw piece on target /destination cell
    DrawPiece( board, move->TargetCell, move->TargetCell->Piece->Index, turn, isKing );
    
    // If the move is a jump, then the JumpedCell needs to be updated as well
    if (move->isJump)
    {
       DrawCell(move->JumpedCell, move->JumpedCell->Row, move->JumpedCell->Column);
       move->JumpedCell->Piece->State = Removed;
       move->JumpedCell->Piece = NULL;
       move->JumpedCell->IsOccupied = FALSE;
       move->JumpedCell->OccupiedBy = NONE;
    }
    
}
#endif	/* PIECE_H */

