#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "datastructures.h"
#include "cell.h"
#include "piece.h"
#include "board.h"

Board CheckersBoard;

int main(void)
{  
   initwindow(1200, 900);
   
   //Draws the initial state of board
   DrawBoard( &CheckersBoard );
   
   //set two pieces as king, for testing
//   PtrCell test1 = GetCellByRowColumn(2,3, &CheckersBoard);//, FALSE, BLUE);
//   test1->Piece->IsKing = TRUE;
//   PtrCell test2 = GetCellByRowColumn(5,4, &CheckersBoard);//, FALSE, BLUE);
//   test2->Piece->IsKing = TRUE;
   
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   
   outtextxy(700, 90,"No Piece Selected");
   
   int turn = RED;
   
   int mouseX, mouseY, selectionChanged = FALSE;
   
   char * turnColor  = (char *)malloc( 5 * sizeof(char) );
   
   strcpy(turnColor, "RED");
   
   Move moves[4];
   
   //PtrMove moves = (PtrMove) malloc(sizeof(Move) * 4); //provision for 4 moves
   
   int moveCount = 0;
   
   while(TRUE)
   {
       DrawIndicator(&CheckersBoard);
       
       //turn indicator
       strcmp(turnColor, "BLUE") ? outtextxy(600, 110, "RED's turn") : outtextxy(600, 110,"BLUE's turn");
       
       //check if correct piece is selected
       if ( !selectionChanged )
       {
           //selectionChanged = FALSE;
           getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
       }
       // if the button was clicked, then we check if the correct piece was selected
       if ( !( mouseX == -1 && mouseY == -1 ) )
       {
           //for ex, it this is blue's turn but user clicks on a red piece
           //this check tests that scenario
           if ( getpixel(mouseX, mouseY) != turn )
           {
               outtextxy(600, 90,"Select correct piece");
               
               if ( turn == RED )
                   outtextxy(600, 110,"Select RED colored piece");
               else 
                   outtextxy(600, 110,"Select BLUE colored piece");    
           }
           else
           {              
               //user has selected the correct piece, now we have to identify the possible targets for the move
               PtrCell clickedCell = GetClickedCell( mouseX, mouseY, &CheckersBoard );
                                            
               if ( !IdentifyAndHighlightTargets(clickedCell, moves, &moveCount, turn, &CheckersBoard ) )
               {
                   selectionChanged = FALSE;
                   continue;
               }
               //now, targets have been identified and highlighted
               
               //we need to intercept clicks on target
               
               //IDenftify which target was selected
               PtrCell clickedTarget = NULL;
               
               //this forces the user to select a valid target
               //until the the mouse is clicked, this loop will keep on polling the device
               int moveSelected = 0;
               
               while( ! ( moveSelected = InterceptTargetClicksY(&clickedTarget, moves, &moveCount, &mouseX, &mouseY, turn, &CheckersBoard, clickedCell->Piece->IsKing) ) )
               {
                  //well, we can wait till the user selects a target
               } //end while for target selection
               
               //When we exit the above loop, clickedTarget contains the address of a valid target 
                              
               //now we have to move the piece to clicked cell
               
               if ( moveSelected != CHANGE_PIECE )
               {
                   MovePieceY(&moves[moveSelected - 1], turn, &CheckersBoard);

                   //set values for next turn
                   turn = turn == BLUE ? RED : BLUE; 
                   strcmp(turnColor, "RED") ? strcpy(turnColor, "RED") : strcpy(turnColor, "BLUE") ;
                   
                   selectionChanged = FALSE;
                   
               }
               else
               {
                   selectionChanged = TRUE;
               }

           }
       }
   }

   closegraph();
      
   return 0;
}