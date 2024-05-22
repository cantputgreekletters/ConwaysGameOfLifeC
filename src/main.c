#include <stdio.h> 
#include <GL/glut.h> 
#include <stdlib.h>
#include "cgml.h"
#include <unistd.h>

float my_square = 0;
int timer = 0;
void Update()
{
    printf("timer = %d\n", timer);
    printf("alive cells = %d\n", GetCellCounter());
    timer ++;
    printf("checked alive cells = %d\n", ManuallyCheckAliveCells());
}

void Draw_My_Square()
{
    if (my_square < 100)
    {
        glRectf(my_square, my_square, my_square + 10, my_square + 10);
    }
}

void Draw()
{
    DrawBoard();
    if (timer < 1000)
    {Draw_My_Square();}
}

// function to initialize 
void myInit (void) 
{ 
    // making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
      
    // making picture color green (in RGB mode), as middle argument is 1.0 
    glColor3f(0.0, 1.0, 0.0); 
      
    // breadth of picture boundary is 1 pixel 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-780, 780, -420, 420); 
} 

void display(void)  
{ 

    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINT); 
      
    // iterate y up to 2*pi, i.e., 360 degree 
    // with small increment in angle as 
    // glVertex2i just draws a point on specified co-ordinate
    Draw();
    Update();
    glutIdleFunc(glutPostRedisplay); // this updates the screen
    glEnd(); 
    glFlush();
} 



int main (int argc, char** argv) 
{ 
    MakeBoard();
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Conway's Game Of Life"); 
    myInit(); 
    glutDisplayFunc(display); 
    glutMainLoop();

    return(0);
} 