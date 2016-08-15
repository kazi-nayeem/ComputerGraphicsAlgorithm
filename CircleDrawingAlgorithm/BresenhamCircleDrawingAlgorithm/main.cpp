#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

typedef GLint point2[2];

int r, x, y;

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
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
    //setCirclePoint(0,r);

    int x = 0, y = r;
    int d = 3-2*r;
    for(;x<=y;x++)
    {
        setCirclePoint(x,y);
        if(d < 0){
            d += 4*x+6;
        }else{
            d += 4*(x-y)+10;
            y--;
        }
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
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Bresenham's Circle Drawing Algorithm");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
