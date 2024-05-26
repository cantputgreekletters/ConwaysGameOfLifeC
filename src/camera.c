#include "camera.h"
//#include <conio.h> //keyboard detection (?)
#include <stdio.h>
#include <GL/freeglut.h>
#define change_in_position 5
void MoveCamera(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        MyCamera.x -= change_in_position;
        break;
    case 'a':
        MyCamera.x += change_in_position;
        break;
    case 'w':
        MyCamera.y -= change_in_position;
        break;
    case 's':
        MyCamera.y += change_in_position;
        break;
    case 'f':
        glutFullScreen();
        break;
    default:
        break;
    }
}
