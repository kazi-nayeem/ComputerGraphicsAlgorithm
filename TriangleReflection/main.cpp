#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

#define SIZE 250

const int Xhigh = SIZE;
const int Yhigh = SIZE;
const int Xlow = -SIZE;
const int Ylow = -SIZE;

int r, x, y;

struct Matrix
{
    double mat[3][3];
    Matrix()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
                mat[i][j] = 0.0;
            mat[i][i] = 1;
        }
    }
    Matrix operator * (const Matrix p) const
    {
        Matrix res;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3;  k++)
                {
                    sum += mat[i][k] * p.mat[k][j];
                }
                res.mat[i][j] = sum;
            }
        }
        return res;
    }
    void print()
    {
        puts("\n\nMatrix\n");
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
                printf("%lf ", mat[i][j]);
            puts("");
        }
    }
};

struct Point
{
    int x, y;
    Point(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }
    void input()
    {
        scanf("%d %d", &x, &y);
    }
    void print()
    {
        printf("point : %d %d\n", x, y);
    }
    void Transform(Matrix t)
    {
        //print();
        //t.print();
        double tx = (double) t.mat[0][0]*x+t.mat[0][1]*y+t.mat[0][2];
        double ty = (double) t.mat[1][0]*x+t.mat[1][1]*y+t.mat[1][2];
        //printf("%lf %lf\n", tx, ty);
        y = floor(ty+0.5);
        x = floor(tx+0.5);
        //print();
    }
    void draw()
    {
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
    }
};

struct Line
{
    Point p1, p2;
    Line(Point a, Point b)
    {
        p1 = a;
        p2 = b;
    }
    void draw()
    {
        //glLineWidth(1);
        glBegin(GL_LINES);

        glVertex2d(p1.x, p1.y);
        glVertex2d(p2.x, p2.y);

        glEnd();
    }
};

struct Triangle
{
    Point p1, p2, p3;
    void draw()
    {
        Line(p1,p2).draw();
        Line(p3,p2).draw();
        Line(p3,p1).draw();
    }
    void Transform(Matrix t)
    {
        p1.Transform(t);
        p2.Transform(t);
        p3.Transform(t);
    }
};

Matrix getReflectionX()
{
    Matrix res;
    res.mat[1][1] = -1.0;
    return res;
}

Matrix getReflectionY()
{
    Matrix res;
    res.mat[0][0] = -1.0;
    return res;
}

Triangle input, trans;

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Xlow, Xhigh, Ylow, Yhigh);
    glMatrixMode(GL_MODELVIEW);
}

void setAxis()
{
    glColor3f(0.0, 0.0, 0.0);
    Line(Point(Xhigh,0), Point(Xlow,0)).draw();
    Line(Point(0,Yhigh), Point(0,Ylow)).draw();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    setAxis();
    glColor3f(0.0, 1.0, 0.0);
    input.draw();

    glColor3f(1.0, 0.0, 0.0);
    trans.draw();

    glFlush();
}

void inputProcess()
{
    puts("Input Triangle vertex points");
    input.p1.input();
    input.p2.input();
    input.p3.input();

    Matrix instance;
    puts("Select transformation type:");
    puts(" 1. Reflection about X-axis");
    puts(" 2. Reflection about Y-axis");
    puts("----------------------------");

    printf("Your choosen option number: ");
    int ch;
    scanf("%d", &ch);
    if(ch == 1)
    {
        instance = getReflectionX();
    }
    else if(ch == 2)
    {
        instance = getReflectionY();
    }
    puts("\n\n");
    puts("Green is Original");
    puts("Red is Transformed");

    trans = input;
    trans.Transform(instance);
}

int main(int argc, char **argv)
{
    inputProcess();
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (2*SIZE, 2*SIZE);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Triangle Reflection");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
