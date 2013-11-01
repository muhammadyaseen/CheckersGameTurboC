#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "menu.h"
#include "datastructures.h"
#include "cell.h"
#include "piece.h"
#include "board.h"

Board CheckersBoard;

int main(void)
{  
   initwindow(1200, 900);
   
    int turn;
    int selectionChanged;
    char * turnColor;
   
   //Draws Welcome Screen and Name Screen
   Main_Window();
   gameState = Selection;
   
   //GameState Loop
   while(TRUE)
   { 
       switch (gameState) 
       {
           case Selection:
           
               Selection_Window();
               
               break;
           
           case VsComputer:
           
               AI_Mode= TRUE;
               gameState= TwoPlayer; //VsComputer has same gameplay as TwoPlayer, we set AI_mode=TRUE, to assign AI the role of 2nd player
          
           
           case TwoPlayer:
                    
               //Draws the initial state of board
               DrawBoard( &CheckersBoard );
               
               line (HUDLINE,0,HUDLINE,getmaxy()); //Draws the hud line
               /*
                Will move the files over the hud line with HUDLINE and any further pixels
               */     
               settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   
               outtextxy(HUDLINE + 50, 90,"No Piece Selected");
   
               turn = RED;
   
               selectionChanged = FALSE;
   
               turnColor  = (char *)malloc( 5 * sizeof(char) );
   
               strcpy(turnColor, "RED");
   
               PtrMove moves[4];  //provision for 4 moves
   
               for(int i = 0; i < 4; i++)
                   moves[i] = (PtrMove) calloc( 1, sizeof(Move) ); //initializes address to NULL values
               
               //Game Loop
                while(PiecesLeft(&CheckersBoard))
                {
                    DrawIndicator(&CheckersBoard);
       
                    //turn indicator
                    strcmp(turnColor, "BLUE") ? outtextxy(HUDLINE + 50, 160, "RED's turn  ") : outtextxy(HUDLINE + 50, 160,"BLUE's turn");
                    //the space removes the extra 'n' after blue turn
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
                              outtextxy(HUDLINE + 50, 90,"Select correct piece");
               
                              if ( turn == RED )
                                   outtextxy(HUDLINE + 50, 110,"Select RED colored piece");
                              else 
                                   outtextxy(HUDLINE + 50, 110,"Select BLUE colored piece");    
                         }
                    
                         else
                         {              
                             //user has selected the correct piece, now we have to identify the possible targets for the move
                             PtrCell clickedCell = GetClickedCell( mouseX, mouseY, &CheckersBoard );
                                            
                             if ( !IdentifyAndHighlightTargets(clickedCell, moves, turn, &CheckersBoard ) )
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
               
                             while( ! ( moveSelected = InterceptTargetClicks(&clickedTarget, moves, &mouseX, &mouseY, turn, &CheckersBoard, clickedCell->Piece->IsKing) ) )
                             {
                                 //well, we can wait till the user selects a target
                             } //end while for target selection
               
                             //When we exit the above loop, clickedTarget contains the address of a valid target 
                              
                             //now we have to move the piece to clicked cell
               
                             if ( moveSelected != CHANGE_PIECE )
                             {
                                 MovePiece(moves[moveSelected - 1], turn, &CheckersBoard);

                                 //set values for next turn
                                 //in case of AI mode, this transfers the control to AI (fear the AI!)
                                 turn = turn == BLUE ? RED : BLUE; 
                                 strcmp(turnColor, "RED") ? strcpy(turnColor, "RED") : strcpy(turnColor, "BLUE") ;
                   
                                 selectionChanged = FALSE;
                   
                                 if ( AI_Mode ) //if in AI mode, next turn should be taken by AI
                                 {
                                     PlayAITurn(&CheckersBoard, turn);
                   
                                    //set values for next turn
                                    //in case of AI, this transfer the control back to player
                                    turn = turn == BLUE ? RED : BLUE; 
                                    strcmp(turnColor, "RED") ? strcpy(turnColor, "RED") : strcpy(turnColor, "BLUE") ;
                                 }
                             }
                             else
                             {
                                 selectionChanged = TRUE;
                             }

                         }
                  }
       
                 //Re-initialize and free the memory for moves array so that we can flush the information we stored for previous move
                 for(int i = 0; i < 4; i++)
                      moves[i] = (PtrMove) calloc(1,  sizeof(Move) );
                    
             
                
              } //while ends (Game Loop)
                
              gameState= Win;
              
              break;
            
            //case 2player ends
           
           case Win: 
           
               gameState = Selection;
               delay(1500); //1.5 sec delay before wiping out checkers board, so that player can see what happened in the last move
               cleardevice();
               break;

       } //switch ends
  } //while gameStaet ends

   closegraph();
   return 0;
}
