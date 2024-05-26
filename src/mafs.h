#ifndef __MAFS_H__
#define __MAFS_H__

#include <stdbool.h>
typedef struct vector2
{
    float x;
    float y;
} Vector2;

int Randint(int a, int b);
Vector2 NewVector2(float x, float y);
bool in_range(float n, float a, float b);
#endif