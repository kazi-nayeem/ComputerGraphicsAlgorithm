#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

#define SIZE 250

typedef GLint point2[2];

int r, x, y;

void setAxis()
{
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    glVertex2i(SIZE,0);
    glVertex2i(-SIZE,0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(0,SIZE);
    glVertex2i(0,-SIZE);
    glEnd();
}

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SIZE, SIZE, -SIZE, SIZE);
    glMatrixMode(GL_MODELVIEW);
}

void drawPoint(int x1, int y1)
{
    glBegin(GL_POINTS);
    glVertex2i(x+x1,y+y1);
    glEnd();
}

void setCirclePoint(int x, int y)
{
    drawPoint(x,y);
    drawPoint(x,-y);
    drawPoint(-x,-y);
    drawPoint(-x,y);
    drawPoint(y,x);
    drawPoint(y,-x);
    drawPoint(-y,-x);
    drawPoint(-y,x);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    setAxis();
    glColor3f(1.0, 0.0, 0.0);

    float maxX = r/sqrt(2);
    setCirclePoint(0,r);
    //setCirclePoint(maxX+0.5,maxX+0.5);
    for(int i = 1; i <= maxX; i++)
    {
        int y = sqrt(r*r-i*i)+0.5;
        setCirclePoint(i,y);
    }
    glFlush();
}

int main(int argc, char **argv)
{
    puts("Circle center: x y");
    scanf("%d %d", &x, &y);
    puts("Circle Radius ");
    scanf("%d", &r);
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (2*SIZE, 2*SIZE);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Circle Drawing Method 1");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
