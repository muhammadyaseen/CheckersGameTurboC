#ifndef PIECE_H
#define	PIECE_H

#include "datastructures.h"

void DrawPiece(PtrBoard, PtrCell, int, int, int);
int NoOfPieces(int *, int *, PtrBoard);

/* 
 * @description : Used to draw the piece, This can be called anywhere you need to draw a piece.
 * 
 * @param - board - sAddress of the global struct Board variable. We use it to 'fill' in the array entries, as we build the piece
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
//    if (cell->Row == 2 && cell->Column == 3) cell->Piece->IsKing = TRUE;
//    
//    if (cell->Row == 5 && cell->Column == 4) cell->Piece->IsKing = TRUE;
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

/* @description - 
 * 
 * @param - 
 * @param - 
 * @param - 
 * 
 * @return -
 */
//void MovePieceForAI(PtrBoard board, PtrCell selectedCell , PtrCell target, int turn)
//{
//    //change previous cell data               
//    selectedCell->IsOccupied = FALSE;
//
//    //change target cell data
//    target->Piece = selectedCell->Piece;
//    target->IsOccupied = TRUE;
//
//    selectedCell->Piece = NULL;
//
//    //re draw previous cell
//    DrawCell( selectedCell, selectedCell->Row, selectedCell->Column );
//
//    //draw piece on target cell
//    DrawPiece( board, target, target->Piece->Index, turn );
//    
//}

/* @description - Used to draw the (sort of) score board, indicating how many pieces are 'OnBoard' of a particular type
 * @param - 
 * @param - 
 * @param - 
 * 
 * @return -
 */

void DrawIndicator(PtrBoard board)
{
    char * numberRed = (char *)malloc( 3 );
    char * numberBlue = (char *)malloc( 3 );
    
    int bluePieces = 0, redPieces = 0;
    
//    for ( int i = 0; i < PIECES_COUNT; i++)
//    {
//        if ( board->Pieces[i].Type == BLUE && board->Pieces[i].State == OnBoard )
//            bluePieces++;
//        
//        if ( board->Pieces[i].Type == RED && board->Pieces[i].State == OnBoard )
//            redPieces++;
//    }
    
    NoOfPieces(&redPieces, &bluePieces, board);
     
    int x = 650, y = 500;
    
    outtextxy(HUDLINE + 70,y-50,"Number of pieces left");
    
    //red circle
    setcolor(RED);
    circle(HUDLINE + 130, y+60, 25);
    setfillstyle(SOLID_FILL, RED); //fills the color red in it
    floodfill(HUDLINE + 130, y+60, RED);
    outtextxy( HUDLINE +115, y+100, itoa(redPieces, numberRed, 10) );
    
    //blue circle
    setcolor(BLUE);
    circle(HUDLINE + 270, y+60, 25);
    setfillstyle(SOLID_FILL, BLUE); //fills the color blue in it
    floodfill(HUDLINE + 270, y+60, BLUE);
    outtextxy( HUDLINE + 255, y+100, itoa(bluePieces, numberBlue, 10) );
    
    setcolor(CYAN);
    free(numberRed);
    free(numberBlue);
}

/* @description - 
 * 
 * @param - 
 * @param - 
 * @param - 
 * 
 * @return -
 */
void MovePiece(PtrMove move, int turn, PtrBoard board, int forAI = FALSE)
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
    if (!forAI)
    {
        for(int t = 0; t < 3; t++)
        {
            if ( move->OtherTargetCells[t] != NULL )
                DrawCell( move->OtherTargetCells[t], move->OtherTargetCells[t]->Row, move->OtherTargetCells[t]->Column );
        }
    }
    
    int isKing = FALSE;
    
    //determine if the piece is kinged or not, piece is kinged if it reaches the opposite end of the board
    
    if ( turn == RED && move->TargetCell->Row == ROW - 1 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }
    if ( turn == BLUE && move->TargetCell->Row == 0 ) { move->TargetCell->Piece->IsKing = TRUE; isKing = TRUE; }

    //draw piece on target /destination cell
    DrawPiece( board, move->TargetCell, move->TargetCell->Piece->Index, turn, move->TargetCell->Piece->IsKing );
    
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

/* @description - 
 * 
 * @param - 
 * @param - 
 * @param - 
 * 
 * @return -
 */
void PlayAITurn(PtrBoard board, int AIColor)
{         
    // Get the Opponent's Color to predict their moves
    int opponentColor = (AIColor == RED) ? BLUE : RED;
    
//    PieceType AIPiece = (turn == BLUE) ? Blue : Red;
//    PieceType opponentPiece = (turn == BLUE) ? Red : Blue;
    
    // Array to hold all the pieces the AI or user can control
    Piece AIPieces[ PIECES_COUNT/2 ];
    Piece opponentPieces[ PIECES_COUNT/2 ];
    
    // Holds the number of pieces for use in for loops
    int numberOfAIPieces = 0; 
    int numberOfOpponentPieces = 0;
    
    // Goes through all the pieces on the board
    for (int i = 0; i < (PIECES_COUNT); i++)
    {   
        // Checks to see whom the piece belongs to and whether it is on the
        // the board, that is not removed or "jumped over".  
        if (board->Pieces[i].State == OnBoard)
        {
            if (board->Pieces[i].Type == AIColor)
                AIPieces[ numberOfAIPieces++ ] = board->Pieces[i];
            
            if (board->Pieces[i].Type == opponentColor)
                opponentPieces[ numberOfOpponentPieces++ ] = board->Pieces[i];
        }
    
    } // End of pieces gathering for-loop
    
    //========================================================================//
    
    Move possibleMoves[numberOfAIPieces * 4];
    int numberOfPossibleMoves = 0;
    
    // A buffer to temporarily store the moves so they can be evaluated.
    PtrMove buffer[4];
    
    for(int i = 0; i < 4; i++)
        buffer[i] = (PtrMove) calloc( 1, sizeof(Move) ); //initializes address to NULL values
    
    for (int i = 0; i < numberOfAIPieces; i++)
    {
        // Enters when the function does return targets
        if (IdentifyAndHighlightTargets(AIPieces[i].Cell, buffer, AIColor, board, TRUE))
        {
            // If a target exists, it stores all the data in the PossibleMoves 
            // array
            for (int j = 0; j < 4; j++)
            {
                if ( (*buffer[j]).TargetCell != NULL )
                {
                    possibleMoves[numberOfPossibleMoves] = *buffer[j];
                    possibleMoves[numberOfPossibleMoves].movePriority = 0;
                    
                    numberOfPossibleMoves++;
                }
            }    
        }
        
    } // End of PossibleMoves calculating for-loop
    
    //========================================================================//
    
    Move opponentMoves[numberOfOpponentPieces * 4];
    int numberOfOpponentMoves = 0;
    
    // Resetting the buffer
    for(int i = 0; i < 4; i++)
        buffer[i] = (PtrMove) calloc( 1, sizeof(Move) ); //initializes address to NULL values
    
    for (int i = 0; i < numberOfOpponentPieces; i++)
    {
        // Enters when the function does return targets
        if (IdentifyAndHighlightTargets(opponentPieces[i].Cell, buffer, opponentColor, board, TRUE))
        {
            // If a target exists, it stores all the data in the PossibleMoves array
            for (int j = 0; j < 4; j++)
            {
                if ( (*buffer[j]).TargetCell != NULL )
                {
                    opponentMoves[numberOfOpponentMoves++] = *buffer[j];                    
                }
            }    
        }
        
    } // End of OpponentMoves calculating for-loop
    
    //========================================================================//
    
    Move goodMoves[numberOfPossibleMoves];
    int numberOfGoodMoves = 0;
    
    // Opponent based moves
    for(int i = 0; i < numberOfOpponentMoves; i++)
    {
        if (opponentMoves[i].isJump)
        {
            for(int j = 0; j < numberOfPossibleMoves; j++)
            {
                if (possibleMoves[j].TargetCell == opponentMoves[i].TargetCell &&
                    opponentMoves[i].TargetCell->IsOccupied == FALSE)
                {
                    goodMoves[numberOfGoodMoves] =  possibleMoves[j];
                    goodMoves[numberOfGoodMoves].movePriority = HIGH_PRIORITY;
                    
                    numberOfGoodMoves++;
                }
            }
        }
    }
    
    // A bool for whether the move is safe or not
    int safe = TRUE;
    
    // Jump moves
    for(int i = 0; i < numberOfPossibleMoves; i++)
    {
        if (possibleMoves[i].isJump)
        {
            safe = TRUE;
            
            for(int j = 0; j < numberOfOpponentMoves; j++)
            {
                if ( (possibleMoves[i].TargetCell == opponentMoves[j].TargetCell  && // Tests to see if the target cell can be jumped over by an opponent's piece
                      possibleMoves[i].JumpedCell != opponentMoves[j].CurrentCell) &&// and whether that cell is the jumped piece's target cell or not
                    
                        !(possibleMoves[i].TargetCell->Column == 7 ||                    // All of this checks whether the move finishes on the edge of the board
                          possibleMoves[i].TargetCell->Column == 0 ||                    // since those are safe spots and should not make the safe bool false
                          possibleMoves[i].TargetCell->Row == 7    ||
                          possibleMoves[i].TargetCell->Row == 0       )               )
                {
                    safe = FALSE;
                    break;
                }
            }
            
            if (safe)
            {
                goodMoves[numberOfGoodMoves] =  possibleMoves[i];
                goodMoves[numberOfGoodMoves].movePriority = MODERATE_PRIORITY;

                numberOfGoodMoves++;
            }
        }
    }
    
    // Position based moves
    for (int i = 0; i < numberOfPossibleMoves; i++)
    {
        if (possibleMoves[i].TargetCell->Column == 7 ||
            possibleMoves[i].TargetCell->Column == 0 ||
            possibleMoves[i].TargetCell->Row == 7 ||
            possibleMoves[i].TargetCell->Row == 0)
        {
            goodMoves[numberOfGoodMoves] =  possibleMoves[i];
            goodMoves[numberOfGoodMoves].movePriority = LOW_PRIORITY;
            
            numberOfGoodMoves++;
        }
        
    }
    
    //========================================================================//
    
    Move highPriorityMoves[numberOfGoodMoves];
    Move moderatePriorityMoves[numberOfGoodMoves];
    Move lowPriorityMoves[numberOfGoodMoves];
    
    int numberOfHighPriorityMoves = 0;
    int numberOfModeratePriorityMoves = 0;
    int numberOfLowPriorityMoves = 0;
    
    for(int i = 0; i < numberOfGoodMoves; i++)
    {
        if(goodMoves[i].movePriority == HIGH_PRIORITY)
            highPriorityMoves[numberOfHighPriorityMoves++] = goodMoves[i];
        
        if(goodMoves[i].movePriority == MODERATE_PRIORITY)
            moderatePriorityMoves[numberOfModeratePriorityMoves++] = goodMoves[i];
        
        if(goodMoves[i].movePriority == LOW_PRIORITY)
            lowPriorityMoves[numberOfLowPriorityMoves++] = goodMoves[i];
        
    }
    
    //========================================================================//
    
    // Delay
    delay(1500);
    
    int moveIndex; 
    
    if(numberOfHighPriorityMoves != 0)
    {
        // Randomly select a move
        moveIndex = rand() % numberOfHighPriorityMoves;

        // Moves the piece
        MovePiece(&highPriorityMoves[moveIndex], AIColor, board, TRUE);
    }
    else if(numberOfModeratePriorityMoves != 0)
    {
        // Randomly select a move
        moveIndex = rand() % numberOfModeratePriorityMoves;

        // Moves the piece
        MovePiece(&moderatePriorityMoves[moveIndex], AIColor, board, TRUE);
    }
    else if(numberOfLowPriorityMoves != 0)
    {
        // Randomly select a move
        moveIndex = rand() % numberOfLowPriorityMoves;

        // Moves the piece
        MovePiece(&lowPriorityMoves[moveIndex], AIColor, board, TRUE);
    }
    else if(numberOfGoodMoves != 0)
    {
        // Randomly select a move
        moveIndex = rand() % numberOfGoodMoves;

        // Moves the piece
        MovePiece(&goodMoves[moveIndex], AIColor, board, TRUE);

    }
    else
    {
        // Randomly select a move
        moveIndex = rand() % numberOfPossibleMoves;

        // Moves the piece
        MovePiece(&possibleMoves[moveIndex], AIColor, board, TRUE);
        
    }
}

int NoOfPieces(int * redPieces, int * bluePieces, PtrBoard board)
{
    for ( int i = 0; i < PIECES_COUNT; i++)
    {
        if ( board->Pieces[i].Type == BLUE && board->Pieces[i].State == OnBoard )
            (*bluePieces)++;
        
        if ( board->Pieces[i].Type == RED && board->Pieces[i].State == OnBoard )
            (*redPieces)++;
    }
}
int PiecesLeft(PtrBoard board)
{
    int bluePieces = 0, redPieces = 0;
    
    NoOfPieces(&redPieces, &bluePieces, board);
    
    return bluePieces && redPieces;
}

#endif	/* PIECE_H */

