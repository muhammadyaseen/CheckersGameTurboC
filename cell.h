#ifndef CELL_H
#define	CELL_H

void DrawCell(PtrCell, int, int, PtrBoard);



void DrawCell(PtrCell cellToDraw, int row, int col, PtrBoard board)
{
    rectangle( cellToDraw->Left, cellToDraw->Top, cellToDraw->Right, cellToDraw->Bottom );
    
    //determines whether the drawn cell is white or black
    //Condition is true in case of white cells only
    
    if ( (col + row )  % 2 == 0)
    {
        int seedX = cellToDraw->Right - 1;
        int seedY =  cellToDraw->Bottom - 1;
                
        setfillstyle(SOLID_FILL, WHITE);
        
        floodfill( seedX, seedY, BLUE );       
    }
}


#endif	/* CELL_H */

