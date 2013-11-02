
#ifndef MENU_H
#define	MENU_H

#include "datastructures.h"

#define IGNORE 0

#define WIDTH_SCREEN getmaxx()
#define HEIGHT_SCREEN getmaxy()

#define VER_LINE_X (WIDTH_SCREEN * 0.42)
#define VER_LINE_Y1 (HEIGHT_SCREEN * 0.16)
#define VER_LINE_Y2 (VER_LINE_Y1 + 218)

#define HOR_LINE_X1 (VER_LINE_X - 38)
#define HOR_LINE_X2 (HOR_LINE_X1 + 255)
#define HOR_LINE_Y (HEIGHT_SCREEN * 0.185) 

#define L 40

#define LOAD_LINE_X getmaxx()
#define LOAD_LINE_Y (HEIGHT_SCREEN * 0.72) 

#define FROSTBITE_X (WIDTH_SCREEN * 0.38)
#define FROSTBITE_Y (HEIGHT_SCREEN * 0.14)

#define FROSTBITE_LINE_Y (FROSTBITE_Y + 80)

#define NAME_X ( FROSTBITE_X - 85 )
#define NAME_Y ( FROSTBITE_LINE_Y + 80)
#define NAME_HEIGHT 50


#define RECT_LEFT (WIDTH_SCREEN * 0.29)
#define RECT_RIGHT (WIDTH_SCREEN * 0.70)

#define RECT_HEIGHT 150

#define PLAYER2_RECT_TOP (HEIGHT_SCREEN * 0.25)
#define PLAYER2_RECT_BOTTOM (HEIGHT_SCREEN * 0.37)

#define VSCOMP_RECT_TOP (PLAYER2_RECT_TOP + RECT_HEIGHT)
#define VSCOMP_RECT_BOTTOM (PLAYER2_RECT_BOTTOM + RECT_HEIGHT)

#define EXIT_RECT_TOP (PLAYER2_RECT_TOP + (2*RECT_HEIGHT) )
#define EXIT_RECT_BOTTOM (PLAYER2_RECT_BOTTOM + (2*RECT_HEIGHT) )

#define RECT_WIDTH (RECT_RIGHT - RECT_LEFT)
#define RECT_LENGTH (PLAYER2_RECT_BOTTOM - PLAYER2_RECT_TOP)

GameState gameState;

int AI_Mode= FALSE;

//global variables
int mouseX = -1, mouseY = -1;  //for mouse
int load_x1=0, load_x2=20;

void Main_Window();
void Selection_Window();
void DrawMainScreen();
void Image_Lines();
void Title_Loading();
void DrawTeamScreen();
void WriteNames();
void DrawMenu();
void DrawOptions();
void InterceptClicks();

void Main_Window() {
    DrawMainScreen();
    DrawTeamScreen();    
}

void Selection_Window() {
    DrawOptions();
    InterceptClicks();
    
}


void DrawMainScreen() {
    Image_Lines();
    Title_Loading();
}

void Image_Lines() {
    setlinestyle( SOLID_LINE, IGNORE, THICK_WIDTH );
    setcolor(WHITE);

    //vertical lines
    line (VER_LINE_X,       VER_LINE_Y1,      VER_LINE_X,       VER_LINE_Y2 );
    line (VER_LINE_X + 1*L, VER_LINE_Y1 - 14, VER_LINE_X + 1*L, VER_LINE_Y2 - 14 );
    line (VER_LINE_X + 2*L, VER_LINE_Y1,      VER_LINE_X + 2*L, VER_LINE_Y2 );
    line (VER_LINE_X + 3*L, VER_LINE_Y1 - 14, VER_LINE_X + 3*L, VER_LINE_Y2 - 14 );
    line (VER_LINE_X + 4*L, VER_LINE_Y1,      VER_LINE_X + 4*L, VER_LINE_Y2 );
    line (VER_LINE_X + 5*L, VER_LINE_Y1 - 14, VER_LINE_X + 5*L, VER_LINE_Y2 - 14 );
    
    //horizontal lines
    line (HOR_LINE_X1,       HOR_LINE_Y,       HOR_LINE_X2,       HOR_LINE_Y );
    line (HOR_LINE_X1 + 17,  HOR_LINE_Y + 1*L, HOR_LINE_X2 + 17,  HOR_LINE_Y + 1*L );
    line (HOR_LINE_X1 ,      HOR_LINE_Y + 2*L, HOR_LINE_X2,       HOR_LINE_Y + 2*L );
    line (HOR_LINE_X1 + 17,  HOR_LINE_Y + 3*L, HOR_LINE_X2 + 17 , HOR_LINE_Y + 3*L );
    line (HOR_LINE_X1 ,      HOR_LINE_Y + 4*L, HOR_LINE_X2,       HOR_LINE_Y + 4*L );

}

void Title_Loading() {
    //TheCheckers
    setcolor(RED);
    settextstyle (SIMPLEX_FONT, IGNORE, 2);
    outtextxy (WIDTH_SCREEN*0.15, HEIGHT_SCREEN*0.57, "THE");
    
    settextstyle (GOTHIC_FONT, IGNORE, 8);
    outtextxy (WIDTH_SCREEN*0.22, HEIGHT_SCREEN*0.52, "CHECKERS");

    //Loading Indicator
    delay (500);

    setcolor(WHITE);
    setlinestyle (SOLID_LINE, IGNORE, THICK_WIDTH);
      
    
    for (load_x1, load_x2 ;   load_x2<=LOAD_LINE_X;   load_x1+=20 , load_x2+=20)  {
	line (load_x1, LOAD_LINE_Y, load_x2, LOAD_LINE_Y);
	delay (50);
    }

cleardevice();
    
}

void DrawTeamScreen() {
    delay (1000);

    //Frostbite 
    setcolor(WHITE);
    settextstyle (GOTHIC_FONT, IGNORE, 5);
    outtextxy (WIDTH_SCREEN*0.38, FROSTBITE_Y, "Frostbite");

    //delay (1500);
    //line
    setlinestyle (DOTTED_LINE, IGNORE, NORM_WIDTH);
    line (WIDTH_SCREEN*0.14, FROSTBITE_LINE_Y, WIDTH_SCREEN*0.83, FROSTBITE_LINE_Y);
    
    WriteNames();
}

void WriteNames() {
    
    //delay (1500);
    
    //names
    settextstyle (SIMPLEX_FONT, IGNORE, 2);
    
    outtextxy (NAME_X     ,  NAME_Y + (0 * NAME_HEIGHT),  "Muhammad Yaseen Aftab (CS-050)" );
    outtextxy (NAME_X +  8,  NAME_Y + (1 * NAME_HEIGHT),  "Muhammad Inshal Uddin (CS-041)" );
    outtextxy (NAME_X + 60,  NAME_Y + (2 * NAME_HEIGHT),  "Asjad Sohail (CS-008)" );
    outtextxy (NAME_X + 25,  NAME_Y + (3 * NAME_HEIGHT),  "Wajiha Muzaffar Ali (CS-013)" );

    delay (1500);

    //press any key message 
    settextstyle (DEFAULT_FONT, IGNORE, 2);
    outtextxy (WIDTH_SCREEN*0.60, NAME_Y + 250, "Press any key to continue ...");

    getch();
    cleardevice();
}

void DrawOptions() {
    //checkers
    setcolor (CYAN);
    settextstyle (EUROPEAN_FONT, IGNORE, 8);
    outtextxy (WIDTH_SCREEN*0.24, HEIGHT_SCREEN*0.10, "CHECKERS");

    delay (1000);

    //options
    settextstyle (BOLD_FONT, IGNORE, 6);
    
    outtextxy ((RECT_LEFT + ((RECT_WIDTH - 245) / 2)), (PLAYER2_RECT_TOP + ((RECT_LENGTH - 50) / 2)), "2 Player");
    //delay (1000);
    outtextxy ((RECT_LEFT + ((RECT_WIDTH - 340) / 2)), (VSCOMP_RECT_TOP + ((RECT_LENGTH - 50) / 2)), "Vs Computer");
    //delay (1000);
    outtextxy ( (RECT_LEFT + ((RECT_WIDTH - 120) / 2)), (EXIT_RECT_TOP + ((RECT_LENGTH - 50) / 2)), "Quit");
    
    delay (1000);

    //option boxes
    setcolor(WHITE);
    setlinestyle (SOLID_LINE, IGNORE, NORM_WIDTH);
    
    rectangle(RECT_LEFT, PLAYER2_RECT_TOP, RECT_RIGHT, PLAYER2_RECT_BOTTOM );
    rectangle(RECT_LEFT, VSCOMP_RECT_TOP, RECT_RIGHT, VSCOMP_RECT_BOTTOM );
    rectangle(RECT_LEFT, EXIT_RECT_TOP, RECT_RIGHT, EXIT_RECT_BOTTOM );

}

void InterceptClicks() {
   
   while (TRUE)
  {
       getmouseclick( WM_LBUTTONDOWN, mouseX, mouseY );
       
       //2player
       if ( mouseX>RECT_LEFT && mouseX<RECT_RIGHT && mouseY>PLAYER2_RECT_TOP && mouseY<PLAYER2_RECT_BOTTOM )
       {   
            setcolor(YELLOW);
            rectangle(RECT_LEFT, PLAYER2_RECT_TOP, RECT_RIGHT, PLAYER2_RECT_BOTTOM );

            setcolor(WHITE);
            rectangle (RECT_LEFT, VSCOMP_RECT_TOP, RECT_RIGHT, VSCOMP_RECT_BOTTOM );
            rectangle (RECT_LEFT, EXIT_RECT_TOP, RECT_RIGHT, EXIT_RECT_BOTTOM );

            //SWITCH TO 2Player 
            gameState= TwoPlayer;
            cleardevice();
            return;
       }
       
      //vs comp
       if( mouseX>RECT_LEFT && mouseX<RECT_RIGHT && mouseY>VSCOMP_RECT_TOP && mouseY<VSCOMP_RECT_BOTTOM )
       {
            setcolor(YELLOW);
            rectangle (RECT_LEFT, VSCOMP_RECT_TOP, RECT_RIGHT, VSCOMP_RECT_BOTTOM );

            setcolor(WHITE);
            rectangle(RECT_LEFT, PLAYER2_RECT_TOP, RECT_RIGHT, PLAYER2_RECT_BOTTOM );
            rectangle (RECT_LEFT, EXIT_RECT_TOP, RECT_RIGHT, EXIT_RECT_BOTTOM );

            //SWITCH TO VsComputer 
            gameState= VsComputer;
            cleardevice();
            return;
       } 
       
       //exit
       if( mouseX>RECT_LEFT && mouseX<RECT_RIGHT && mouseY>EXIT_RECT_TOP && mouseY<EXIT_RECT_BOTTOM )
       {
            setcolor(YELLOW);
            rectangle (RECT_LEFT, EXIT_RECT_TOP, RECT_RIGHT, EXIT_RECT_BOTTOM );

            setcolor(WHITE);
            rectangle(RECT_LEFT, PLAYER2_RECT_TOP, RECT_RIGHT, PLAYER2_RECT_BOTTOM );
            rectangle (RECT_LEFT, VSCOMP_RECT_TOP, RECT_RIGHT, VSCOMP_RECT_BOTTOM );

            //terminating point of gameState while loop
            exit(0);
       }
     
    } //while ends
     
}   

#endif	/* MENU_H */

