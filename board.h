#ifndef BOARD_H
#define	BOARD_H

void DrawBoard(PtrBoard);


void DrawBoard(PtrBoard board)
{
   //Cells will be of blue border
    
   setcolor(BLUE);
   
   //goes from 0 to ROW*COL, we are using it to keep track of cells array in board
   int cellNo = 0;
   
   //goes from 0 to 12, we are using it to keep track of pieces array in board
   int pieceNo = 0;
   
   for(int row = 0; row < ROW; row++)
   {     
       for(int col = 0; col < COL; col++)
        {
           // configure the cell properties so that it can be drawn
            board->Cells[cellNo].Left = WIDTH * col;
            board->Cells[cellNo].Top = HEIGHT * row;
            board->Cells[cellNo].Right = WIDTH * (1+col);
            board->Cells[cellNo].Bottom =  HEIGHT * (1+row);
            
            board->Cells[cellNo].IsOccupied = 0;
            
            board->Cells[cellNo].Row = row;
            board->Cells[cellNo].Column = col;
            
            //Draws the cell configured above
            DrawCell( &board->Cells[cellNo], row, col, board );
            
            // if it is a 'white' cell      AND        this row should have Pieces 
            if ( ( (col + row )  % 2 == 0 ) && ( row < DRAW_START_UP || row > DRAW_START_DOWN) )
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

