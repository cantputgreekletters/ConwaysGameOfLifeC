#include "cgml.h"
#include <stdbool.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "mafs.h"
#include "camera.h"
Cell** CellBoard;
int cell_counter = 0;

int GetCellCounter()
{
    return cell_counter;
}

Cell NewCell(Vector2 center)
{
    Cell new_cell;
    new_cell.center = center;
    new_cell.is_alive = false;
    new_cell.alive_neighbors = 0;
    return new_cell;
}

Cell* GetCellFromScreen(int x, int y)
{
    int new_x, new_y;
    new_x = (int)((x + 60.5 * cell_size + 60 + MyCamera.x) / (2 * (cell_size + 1)));
    //y isn't that accurate
    new_y = (int)((y + 38.5 * cell_size + 38 + MyCamera.y) / (2 * (cell_size + 1)));
    printf("calculated x = %d, calculated y = %d\n", new_x, new_y);
    if (!(in_range(new_x,0, BoardSize - 1) && in_range(new_y,0, BoardSize - 1)))
    {
        return NULL;
    }
    printf("returning cell!\n");
    Cell * target_cell = &CellBoard[new_x][new_y];
    return target_cell;
}

void DrawCell(Cell target_cell)
{
    if (! target_cell.is_alive) {return;}
    glColor3f(255,255,255); //color of the cell
    glBegin(GL_POINT);
    float x1,x2,y1,y2;
    x1 = target_cell.center.x - cell_size / 2 - MyCamera.x;
    x2 = target_cell.center.x + cell_size / 2 - MyCamera.x;
    y1 = target_cell.center.y - cell_size / 2 - MyCamera.y;
    y2 = target_cell.center.y + cell_size / 2 - MyCamera.y;
    if (x2 < - 2000 || y1 > 2000 || y2 < - 2000 || x1 > 2000) {return;}
    glRectf(x1,y1,x2,y2);
    glEnd();
}

void _AllocateMemoryToBoard()
{
    CellBoard = (Cell **)malloc(sizeof(Cell *) * BoardSize);
    if(CellBoard == NULL)
    {
       perror("Memory allocation failed");
       exit(0);
    }
    int i;
    for (i = 0; i < BoardSize; i++)
    {
        CellBoard[i] = (Cell *)malloc(sizeof(Cell) * BoardSize);
        if(CellBoard[i] == NULL)
        {
           perror("Memory allocation failed");
           exit(0);
        }
    }
}

void _SetRandomAlive()
{
    cell_counter = 0;
    int x,y;
    for (int i = 0; i < (BoardSize*BoardSize) / 3; i++)
    {
        x = Randint(0, BoardSize - 1);
        y = Randint(0, BoardSize - 1);
        if (CellBoard[x][y].is_alive)
        {
            i--;
            continue;
        }
        CellBoard[x][y].is_alive = true;
        cell_counter ++;
    }
    
}
void MakeBoard()
{
    float offset = cell_size + 2;
    float screen_offset_x = - 30;
    float screen_offset_y = -19;
    _AllocateMemoryToBoard();
    int y,x;
    for(y = 0; y < BoardSize; y++)
    {
        for(x = 0; x < BoardSize; x++)
        {
            CellBoard[x][y] = NewCell(NewVector2((x + screen_offset_x) * (cell_size + offset) , (y + screen_offset_y) * (cell_size + offset)));
        }
    }
    _SetRandomAlive();
    printf("alive cells = %d\n", cell_counter);
}

void IncrementNeighbors(int index_x, int index_y)
{
    int x,y;
    Cell* target_cell;
    for (x = index_x - 1; x < index_x + 2; x++)
    {
        if (x < 0 || x >= BoardSize) {continue;}
        for (y = index_y - 1; y < index_y + 2; y++)
        {
            if (y < 0 || y >= BoardSize || (x == index_x && y == index_y)) {continue;}
            target_cell = &CellBoard[x][y];
            target_cell->alive_neighbors ++;
        }
    }
}
void ApplyRules(int x, int y)
{
    /*
        Any live cell with fewer than two live neighbors dies, as if by underpopulation.
        Any live cell with two or three live neighbors lives on to the next generation.
        Any live cell with more than three live neighbors dies, as if by overpopulation.
        Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
    */
    int n;
    Cell* target_cell;    
    target_cell = &CellBoard[x][y];
    n = target_cell->alive_neighbors;
    if (n > 8)
    {
        printf("cell has more than 8 neighbors\n");
        printf("Has neighbors = %d at cords x=%d,y=%d\n",n,x,y);
        printf("Neighbor count directly from cell = %d and = %d",target_cell->alive_neighbors, CellBoard[x][y].alive_neighbors);
        exit(0);
    }
    switch (target_cell->is_alive){
    case true:
        //is alive
        target_cell->is_alive = n == 2 || n == 3;
        break;
    case false:
        //is dead
        target_cell->is_alive = n == 3;
        break;
    }
    target_cell->alive_neighbors = 0;
    if (target_cell->is_alive) {cell_counter ++;}
    
}

int ManuallyCheckAliveCells()
{
    int counter = 0;
    int x,y;
    for (x  = 0; x < BoardSize; x++)
    {
        for (y  = 0; y < BoardSize; y++)
        {
            if (CellBoard[x][y].is_alive)
            {
                counter ++;
            }
        }
    }
    return counter;
}

void CountNeighbors()
{
    Cell target_cell;
    int x,y;
    for (x = 0; x < BoardSize; x++)
    {
        for (y = 0; y < BoardSize; y++)
        {
            target_cell = CellBoard[x][y];
            if (target_cell.is_alive)
            {
                IncrementNeighbors(x,y);
            }
        }
    }
}

void Cleanse()
{
    int x,y;
    for (x = 0; x < BoardSize; x++)
    {
        for (y = 0; y < BoardSize; y++)
        {
            ApplyRules(x,y);
        }
    }
}
void DrawBoard()
{
    int x,y;
    cell_counter = 0;
    Cell * target_cell;
    for (x = 0; x < BoardSize; x++)
    {
        for (y = 0; y < BoardSize; y++)
        {
            target_cell = &CellBoard[x][y];
            if(target_cell->is_alive) {DrawCell(*target_cell);}
        }
    }
}
