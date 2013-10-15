#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#include "datastructures.h"
#include "cell.h"
#include "piece.h"
#include "board.h"

Board CheckersBoard;

int main(void)
{
   int mode, driver = DETECT;
   
   initwindow(1200, 900);
   
   //Draws the initial state of board
   DrawBoard( &CheckersBoard );
   
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   
   outtextxy(700, 90,"No Piece Selected");
   
   int turn = RED;
   
   int mouseX, mouseY;
   
   char * turnColor  = (char *)malloc( 5 * sizeof(char) );
   
   strcpy(turnColor, "RED");
   
   while(true)
   {
       //turn indicator
       
       strcmp(turnColor, "BLUE") ? outtextxy(600, 110, "RED's turn") : outtextxy(600, 110,"BLUE's turn");
       
       //check if correct piece is selected
       
       getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
       
       // if the button was clicked, then we check if the correct piece was selected
       if ( !( mouseX == -1 && mouseY == -1) )
       {
           //for ex, it this is blue's turn but user clicks on a red piece
           //this check tests that scenario
           if ( getpixel(mouseX, mouseY) != turn )
           {
               outtextxy(600, 90,"Select correct colored piece");
               
               if ( turn == RED )
                   outtextxy(600, 110,"Please RED colored piece");
               else 
                   outtextxy(600, 110,"Please BLUE colored piece");    
           }
           else
           {
               //user has selected the correct piece, now we have to identify the possible targets for the move
               PtrCell clickedCell = GetClickedCell( mouseX, mouseY, &CheckersBoard );
              
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
               else
               {
                    target1Row = clickedCell->Row - 1;
                    target2Row = clickedCell->Row - 1;
                    
                    target1Col = clickedCell->Column + 1;
                    target2Col = clickedCell->Column - 1; 
               }
               
               PtrCell target1 = GetCellByRowColumn(target1Row, target1Col, &CheckersBoard, TRUE);
               
               PtrCell target2 = GetCellByRowColumn(target2Row, target2Col, &CheckersBoard, TRUE);
               
               setfillstyle(SOLID_FILL, YELLOW);
        
               
               //if both targets are null, user must again select the piece to complete the move
               if ( target1 == NULL && target2 == NULL )
                   continue;
               
               if ( target1 != NULL && target1->IsOccupied == 0 )
                    floodfill( target1->Left + 1, target1->Bottom - 1 , BLUE );
               
               if ( target2 != NULL && target2->IsOccupied == 0 )
                    floodfill( target2->Left + 1, target2->Bottom - 1 , BLUE );
               
               //trigger next turn
               turn = turn == BLUE ? RED : BLUE; 
               strcmp(turnColor, "RED") ? strcpy(turnColor, "RED") : strcpy(turnColor, "BLUE") ;
               //GetClickedPiece();
           }
       }
   }
   
   getche();
   
   closegraph();
      
   return 0;
}