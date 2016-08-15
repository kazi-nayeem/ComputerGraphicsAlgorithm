#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>

typedef GLint point2[2];

int x1, x2, y1, y2;

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawPoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(x1 == x2)
    {
        if(y1>y2)
        {
            int tem = y1;
            y1 = y2;
            y2 = tem;
        }
        for(int i = y1; i <= y2; i++)
            drawPoint(x1,i);
    }
    else if(y1 == y2)
    {
        if(x1>x2)
        {
            int tem = x1;
            x1 = x2;
            x2 = tem;
        }
        for(int i = x1; i <= x2; i++)
            drawPoint(i,y1);
    }
    else if(abs(y1 - y2) == abs(x1 - x2))
    {
        if(x1>x2)
        {
            int tem = x1;
            x1 = x2;
            x2 = tem;
            tem = y1;
            y1 = y2;
            y2 = tem;
        }
        int ad = 1;
        if(y1>y2)
        {
            ad = -1;
        }
        for(int i = x1, j = y1; i <= x2; i++, j+=ad)
        {
            drawPoint(i,j);
            //printf("%d %d\n", i, j);
        }
    }
    else if(abs(y1 - y2) < abs(x1 - x2))
    {
        if(x1>x2)
        {
            int tem = x1;
            x1 = x2;
            x2 = tem;
            tem = y1;
            y1 = y2;
            y2 = tem;
        }
        double m = (double) (y1-y2)/(x1-x2);
        double c = y1-m*x1;
        for(int i = x1; i <= x2; i++)
        {
            int j = i*m+c;
            drawPoint(i,j);
            //printf("%d %d\n", i, j);
        }
    }
    else
    {
        if(y1>y2)
        {
            int tem = x1;
            x1 = x2;
            x2 = tem;
            tem = y1;
            y1 = y2;
            y2 = tem;
        }
        double m = (double) (x1-x2)/(y1-y2);
        double c = (m*y1-x1)*m;
        for(int i = y1; i <= y2; i++)
        {
            int j = i*m-c;
            drawPoint(j,i);
            //printf("%d %d\n", i, j);
        }
    }
    glFlush();
}

int main(int argc, char **argv)
{
    puts("x1 y1 x2 y2");
    scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
    glutInit(&argc, argv);


    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Direct Line Drawing Algorithm");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
