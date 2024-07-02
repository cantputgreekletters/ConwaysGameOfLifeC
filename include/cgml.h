#ifndef __CGML_H__
#define __CGML_H__
#define cell_size 10
#define BoardSize 50
#include <stdbool.h>
#include "mafs.h"

typedef struct cell
{
    Vector2 center;
    bool is_alive;
    int alive_neighbors;
} Cell;

int GetCellCounter();
int ManuallyCheckAliveCells();
Cell* GetCellFromScreen(int x, int y);
void Cleanse();
void CountNeighbors();
void MakeBoard();
void DrawBoard();
#endif