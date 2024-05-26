#include "mafs.h"
#include <stdlib.h>


Vector2 NewVector2(float x, float y)
{
    Vector2 new_vector;
    new_vector.x = x;
    new_vector.y = y;
    return new_vector;
}
int Randint(int a, int b)
{
    return rand() % (b + 1 - a) + a;
}

bool in_range(float n, float a, float b)
{
    return n >= a && n <= b;
}