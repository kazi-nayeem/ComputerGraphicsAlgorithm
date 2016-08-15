#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

const int Xhigh = 250;
const int Yhigh = 250;
const int Xlow = -250;
const int Ylow = -250;

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

Matrix getTranslate(Point p)
{
    Matrix res;
    res.mat[0][2] = p.x;
    res.mat[1][2] = p.y;
    return res;
}

Matrix getRotation(double deg)
{
    Matrix res;
    double th = acos(-1.0)*deg/180.0;
    res.mat[0][0] = cos(th);
    res.mat[0][1] = -sin(th);
    res.mat[1][0] = sin(th);
    res.mat[1][1] = cos(th);
    return res;
}

Triangle input, trans;
Point P;

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

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    P.draw();
    glFlush();
}

void inputProcess()
{
    printf("Input Triangle Vertex Coordinates\n");
    input.p1.input();
    input.p2.input();
    input.p3.input();
    printf("Input Point P Coordinate\n");
    P.input();
    //P.print();
    Matrix instance = getTranslate(Point(-1*P.x,-1*P.y));
    //instance.print();
    double deg;
    puts("Input Angle of Rotation");
    scanf("%lf", &deg);
    puts("Green is Original");
    puts("Red is Transformed");
    //instance.print();
    instance = getRotation(deg)*instance;
    //instance.print();
    instance = getTranslate(P)*instance;
    //instance.print();
    trans = input;
    instance.print();
    trans.Transform(instance);
}

int main(int argc, char **argv)
{
    inputProcess();
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (200, 150);
    glutCreateWindow ("Rotate a Triangle about an Arbitrary Point");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
