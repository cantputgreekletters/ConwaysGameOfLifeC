#include "cgml.h"
#include <stdbool.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Cell** CellBoard;
int cell_counter = 0;

int GetCellCounter()
{
    return cell_counter;
}

Vector2 NewVector2(float x, float y)
{
    Vector2 new_vector;
    new_vector.x = x;
    new_vector.y = y;
    return new_vector;
}

Cell NewCell(Vector2 center)
{
    Cell new_cell;
    new_cell.center = center;
    new_cell.is_alive = false;
    return new_cell;
}


void DrawCell(Cell target_cell)
{
    if (! target_cell.is_alive) {return;}
    float x1,x2,y1,y2;
    x1 = target_cell.center.x - cell_size / 2;
    x2 = target_cell.center.x + cell_size / 2;
    y1 = target_cell.center.y - cell_size / 2;
    y2 = target_cell.center.y + cell_size / 2;
    glRectf(x1,y1,x2,y2);
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
int Randint(int a, int b)
{
    return rand() % (b + 1 - a) + a;
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

int GetNeighbors(int index_x, int index_y)
{
    int counter = 0;
    int x,y;
    for (x = index_x - 1; x < index_x + 2; x++)
    {
        if (x < 0 || x >= BoardSize) {continue;}
        for (y = index_y - 1; y < index_y + 2; y++)
        {
            if (y < 0 || y >= BoardSize || (x == index_x && y == index_y)) {continue;}
            if (CellBoard[x][y].is_alive)
            {
                counter ++;
            }
        }
    }
    return counter;
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
    n = GetNeighbors(x,y);
    target_cell = &CellBoard[x][y];
    if (target_cell->is_alive)
    {
        //is alive
        target_cell->is_alive = n == 2 || n == 3;
    } else 
    {
        //is dead
        target_cell->is_alive = n == 3;
    }
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

void DrawBoard()
{
    int x,y;
    cell_counter = 0;
    Cell * target_cell;
    for (x = 0; x < BoardSize; x++)
    {
        for (y = 0; y < BoardSize; y++)
        {
            ApplyRules(x,y);
            target_cell = &CellBoard[x][y];
            if(target_cell->is_alive) {DrawCell(*target_cell);}
        }
    }
}
