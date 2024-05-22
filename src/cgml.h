#ifndef __CGML_H__
#define __CGML_H__
#define cell_size 10
#define BoardSize 50
#include <stdbool.h>

typedef struct vector2
{
    float x;
    float y;
} Vector2;
typedef struct cell
{
    Vector2 center;
    bool is_alive;
} Cell;
int GetCellCounter();
int ManuallyCheckAliveCells();
void MakeBoard();
void DrawBoard();
#endif