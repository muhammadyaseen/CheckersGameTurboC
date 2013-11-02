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
    int winner;
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
           
               AI_Mode = TRUE;
               gameState= TwoPlayer; //VsComputer has same gameplay as TwoPlayer, we set AI_mode=TRUE, to assign AI the role of 2nd player
          
           
           case TwoPlayer:
                    
               //Draws the initial state of board
               DrawBoard( &CheckersBoard );
               
               settextstyle (SIMPLEX_FONT, IGNORE, 2);
               rectangle( MENU_BUTTON_LEFT, MENU_BUTTON_TOP, MENU_BUTTON_RIGHT, MENU_BUTTON_BOTTOM);
               outtextxy( MENU_BUTTON_LEFT + 5,MENU_BUTTON_TOP + 5,"MENU");
               
               line (VERTICAL_HUDLINE, 0,VERTICAL_HUDLINE,getmaxy()); //Draws the hud line
   
               settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   
               turn = RED;
   
               selectionChanged = FALSE;
   
               turnColor  = (char *)malloc( 5 * sizeof(char) );
   
               strcpy(turnColor, "RED");
   
               PtrMove moves[4];  //provision for 4 moves
   
               for(int i = 0; i < 4; i++)
                   moves[i] = (PtrMove) calloc( 1, sizeof(Move) ); //initializes address to NULL values
               
               //Game Loop
                while(TRUE)
                {
                    DrawIndicator(&CheckersBoard);
                    
                    if(GameOver(&winner, turn, &CheckersBoard))
                        break;
                    
                    
                    outtextxy(VERTICAL_HUDLINE + 50, 90,"No Piece Selected     ");
                    
                    //turn indicator
                    strcmp(turnColor, "BLUE") ? outtextxy(VERTICAL_HUDLINE + 50, 160, "RED's turn  ") : outtextxy(VERTICAL_HUDLINE + 50, 160,"BLUE's turn");
                    
                    //the space removes the extra 'n' after blue turn
                    
                    //check if correct piece is selected
                    if ( !selectionChanged )
                    {
                         //selectionChanged = FALSE;
                         getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
                         
                         {
                             if(mouseX>MENU_BUTTON_LEFT && mouseX<MENU_BUTTON_RIGHT && mouseY>MENU_BUTTON_TOP && mouseY<MENU_BUTTON_BOTTOM)
                             {
                                 gameState= Selection;
                                 cleardevice();
                                 break;
                             }
                         }
                    }
                    // if the button was clicked, then we check if the correct piece was selected
                    if ( !( mouseX == -1 && mouseY == -1 ) )
                    {
                         //for ex, it this is blue's turn but user clicks on a red piece
                         //this check tests that scenario
                         if ( getpixel(mouseX, mouseY) != turn )
                         {
                              outtextxy(VERTICAL_HUDLINE + 50, 90, "Select correct piece");
               
                              if ( turn == RED )
                                   outtextxy(VERTICAL_HUDLINE + 50, 110,"Select RED colored piece  ");
                              else 
                                   outtextxy(VERTICAL_HUDLINE + 50, 110,"Select BLUE colored piece");    
                         }
                    
                         else
                         {              
                             // If correct piece has been selected, then overwrite the warning
                             outtextxy(VERTICAL_HUDLINE + 50, 90, "                        ");
                             outtextxy(VERTICAL_HUDLINE + 50, 110,"                          ");
                             
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
                                 strcmp(turnColor, "BLUE") ? outtextxy(VERTICAL_HUDLINE + 50, 160, "RED's turn  ") : outtextxy(VERTICAL_HUDLINE + 50, 160,"BLUE's turn");
                                 
                                 // Overwrite the indicators in case they might have changed after the move
                                 outtextxy( VERTICAL_HUDLINE + 115, 600, "   " );
                                 outtextxy(VERTICAL_HUDLINE + 255, 600, "   " );
                   
                                 selectionChanged = FALSE;
                   
                                 if ( AI_Mode ) //if in AI mode, next turn should be taken by AI
                                 {
                                    // Draw the indicator again for AI
                                    DrawIndicator(&CheckersBoard);

                                    if(GameOver(&winner, turn, &CheckersBoard))
                                        break;

                                    PlayAITurn(&CheckersBoard, turn);
                                     
                                    //set values for next turn
                                    //in case of AI, this transfer the control back to player
                                    turn = turn == BLUE ? RED : BLUE; 
                                    strcmp(turnColor, "RED") ? strcpy(turnColor, "RED") : strcpy(turnColor, "BLUE") ;
                                    
                                    // Overwrite the indicators in case they might have changed after the move
                                    outtextxy( VERTICAL_HUDLINE + 115, 600, "   " );
                                    outtextxy(VERTICAL_HUDLINE + 255, 600, "   " );
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
              
            //case 2player ends
               break; //two player case break
           
           case Win:
           case Draw:
               setcolor(WHITE);
               switch (winner)
               {
                   case RED:
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                        outtextxy(VERTICAL_HUDLINE + 50, 160, "RED WINS     ");
                        break;
                   
                   case BLUE:
                       settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                       outtextxy(VERTICAL_HUDLINE + 50, 160, "BLUE WINS     ");
                       break;
                       
                   default:
                       outtextxy(VERTICAL_HUDLINE + 50, 110, "NO MOVES ARE POSSIBLE");
                       outtextxy(VERTICAL_HUDLINE + 50, 160, "IT'S A DRAW    ");
                       break;
               }
               
               gameState = Selection;
               delay(3000); //3 sec delay before wiping out checkers board, so that player can see what happened in the last move
               cleardevice();
               break;

       } //switch ends
  } //while gameStaet ends

   closegraph();
   return 0;
}
