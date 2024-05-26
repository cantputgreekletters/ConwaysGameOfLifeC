#include <stdio.h> 
#include <GL/glut.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mafs.h"
#include "cgml.h"
#include "camera.h"

#define Screen_Width 1366
#define Screen_Height 768

float my_square = 0;
int timer = 0;
int frame_count = 0;
float fps = 0.0;
struct timeval start_time, end_time;

void Mouse(int button, int state, int x, int y)
{
    int new_x = x - Screen_Width / 2;
    int new_y = -(y - Screen_Height / 2);
    if (button == 0)
    {
        Cell * target_cell = GetCellFromScreen(new_x, new_y);
        if (target_cell)
        {
            target_cell->is_alive = true;
        }
        
    }
    
}
void Update()
{
    //printf("timer = %d\n", timer);
    //printf("alive cells = %d\n", GetCellCounter());
    timer ++;
    CountNeighbors();
    Cleanse();
}

void Draw_My_Square()
{
    if (my_square < 100)
    {
        glBegin(GL_POINT);
        glRectf(my_square, my_square, my_square + 10, my_square + 10);
        glEnd();
    }
}

void Draw()
{
    DrawBoard();
}

void DrawFPS()
{
    char fps_str[32];
    sprintf(fps_str, "FPS: %.2f", fps);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-750, 400);  // Positioning text in the top-left corner

    for (char *c = fps_str; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// function to initialize 
void myInit (void) 
{ 
    // making background color  
    // 3 arguments all are 0.0 
    glClearColor(0.05, 0.05, 0.05, 1); 
      
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
    
    // Update frame count
    frame_count++;

    // Calculate FPS every second
    gettimeofday(&end_time, NULL);
    float elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    if (elapsed_time >= 1.0)
    {
        fps = frame_count / elapsed_time;
        frame_count = 0;
        start_time = end_time;
    }

    Draw();
    DrawFPS(); // Draw FPS on the screen
    Update();
    
    glutSwapBuffers(); // Use double buffering
    glutPostRedisplay(); // Request a new frame
} 

Vector2 MyCamera = {.x = 0, .y = 0};

int main (int argc, char** argv) 
{ 
    MakeBoard();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Use double buffering
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(Screen_Width, Screen_Height); 
    glutInitWindowPosition(0, 0); 
    // Giving name to window 
    glutCreateWindow("Conway's Game Of Life");
    myInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(MoveCamera);
    glutMouseFunc(Mouse);
    glutMainLoop();

    return(0);
}