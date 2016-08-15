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

void setAxes()
{
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    glVertex2d(250, 0);
    glVertex2d(-250, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0, 250);
    glVertex2d(0, -250);
    glEnd();
}

void display(void)
{
    int tx1 = x1, tx2 = x2, ty1 = y1, ty2 = y2;
    glClear(GL_COLOR_BUFFER_BIT);
    setAxes();
    glColor3f(1.0, 0.0, 0.0);
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

        if((y2-y1)*(x2-x1)>=0)
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
            int x = x1, y = y1;
            int dx = x2-x1, dy = y2-y1;
            int dT = 2*(dy-dx), dS = 2*dy;
            int d = 2*dy-dx;

            drawPoint(x,y);
            while(x<x2)
            {
                x++;
                if(d < 0)
                {
                    d += dS;
                }
                else
                {
                    y++;
                    d += dT;
                }
                drawPoint(x,y);
            }
        }
        else
        {
            if(x1<x2)
            {
                int tem = x1;
                x1 = x2;
                x2 = tem;
                tem = y1;
                y1 = y2;
                y2 = tem;
            }
            x1 = -x1;
            x2 = -x2;
            int x = x1, y = y1;
            int dx = x2-x1, dy = y2-y1;
            int dT = 2*(dy-dx), dS = 2*dy;
            int d = 2*dy-dx;

            drawPoint(x,y);
            while(x<x2)
            {
                x++;
                if(d < 0)
                {
                    d += dS;
                }
                else
                {
                    y++;
                    d += dT;
                }
                drawPoint(-x,y);
            }
        }

        //printf("%d %d %d %d\n", x1, y1, x2, y2);


    }
    else
    {
        if((y2-y1)*(x2-x1)>=0)
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
            int x = x1, y = y1;
            int dx = x2-x1, dy = y2-y1;
            int dT = 2*(dx-dy), dS = 2*dx;
            int d = 2*dx-dy;
            drawPoint(x,y);
            while(y<y2)
            {
                y++;
                if(d < 0)
                {
                    d += dS;
                }
                else
                {
                    x++;
                    d += dT;
                }
                drawPoint(x,y);
            }
        }
        else
        {
            if(y1<y2)
            {
                int tem = x1;
                x1 = x2;
                x2 = tem;
                tem = y1;
                y1 = y2;
                y2 = tem;
            }
            y1 = -y1;
            y2 = -y2;
            int x = x1, y = y1;
            int dx = x2-x1, dy = y2-y1;
            int dT = 2*(dx-dy), dS = 2*dx;
            int d = 2*dx-dy;
            drawPoint(x,y);
            while(y<y2)
            {
                y++;
                if(d < 0)
                {
                    d += dS;
                }
                else
                {
                    x++;
                    d += dT;
                }
                drawPoint(x,-y);
            }
        }
    }
    glColor3f(0.0, 0.0, 0.0);
    drawPoint(tx1,ty1);
    drawPoint(tx2,ty2);
    glFlush();
    x1 = tx1;
    x2 = tx2;
    y1 = ty1;
    y2 = ty2;
}

int main(int argc, char **argv)
{
    puts("x1 y1 x2 y2");
    scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Bresenham Line Drawing Algorithm");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
