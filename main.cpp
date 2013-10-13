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
   
   int turn = RED, i = 0;
   int mouseX, mouseY;
   
   char * turnColor  = (char *)malloc( 5 * sizeof(char) );
   
   strcpy(turnColor, "RED");
   
   int turnPending = 1;
   
   while(true)
   {
   
       //check of correct piece is selected
       
       getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
       
       
       if ( !( mouseX == -1 && mouseY == -1) && turnPending )
       {
           if ( getpixel(mouseX, mouseY) != turn )
           {
               outtextxy(600, 90,"Please correct colored piece");
               
               if ( turn == RED )
                   outtextxy(600, 110,"Please RED colored piece");
               else 
                   outtextxy(600, 110,"Please BLUE colored piece");    
           }
           else
           {
               //turnPending = !turnPending;
               
               PtrCell clickedCell = GetClickedCell( mouseX, mouseY, &CheckersBoard );
               
               
               
               //hightlight targets
               //max 2 min0
               
               //
               
               int target1Row, target2Row, target1Col, target2Col;
               
               if ( turn == RED )
               {
                    target1Row = clickedCell->Row + 1;
                    target2Row = clickedCell->Row + 1;
                    
                    target1Col = clickedCell->Column + 1;
                    target2Col = clickedCell->Column - 1;
                    
               }
               
               PtrCell target1 = GetCellByRowColumn(target1Row, target1Col, &CheckersBoard);
               
               PtrCell target2 = GetCellByRowColumn(target2Row, target2Col, &CheckersBoard);
               
               setfillstyle(SOLID_FILL, YELLOW);
        
               floodfill( target1->Left + 1, target1->Bottom - 1 , BLUE );
               
               floodfill( target2->Left + 1, target2->Bottom - 1 , BLUE );
               
               turn = turn == BLUE ? RED : BLUE; 
               //GetClickedPiece();
           }
       }

   
   }
   
   getche();
   
   closegraph();
   
   //getpixel
   //ismouseclick
   //getmouseclick
   
   return 0;
}