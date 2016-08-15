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

struct RecTangle
{
    Point p1, p2, p3, p4;
    RecTangle()
    {
        p1 = Point(20,20);
        p2 = Point(70,20);
        p3 = Point(70,70);
        p4 = Point(20,70);
    }
    void draw()
    {
        Line(p1,p2).draw();
        Line(p3,p2).draw();
        Line(p3,p4).draw();
        Line(p1,p4).draw();
    }
    void Transform(Matrix t)
    {
        p1.Transform(t);
        p2.Transform(t);
        p3.Transform(t);
        p4.Transform(t);
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

Matrix getScale(double sx,double sy)
{
    Matrix res;
    res.mat[0][0] = sx;
    res.mat[1][1] = sy;
    return res;
}
Matrix getSearing(double a,double b)
{
    Matrix res;
    res.mat[0][1] = a;
    res.mat[1][0] = b;
    return res;
}

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

RecTangle input, trans;

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
    Matrix instance = Matrix();
    while(true)
    {
        puts("Select transformation type:");
        puts(" 1. Translation");
        puts(" 2. Rotation");
        puts(" 3. Scaling");
        puts(" 4. Reflection about X-axis");
        puts(" 5. Reflection about Y-axis");
        puts(" 6. Shearing");
        puts(" 0. EXIT");
        puts("----------------------------");

        printf("Your choosen option number: ");
        int ch;
        scanf("%d", &ch);
        if(ch == 0) break;
        if(ch == 1)
        {
            Point P;
            printf("Input Point X Y: ");
            P.input();
            instance = getTranslate(P)*instance;
        }
        else if(ch == 2)
        {
            printf("Input Angle: ");
            double deg;
            scanf("%lf", &deg);
            instance = getRotation(deg)*instance;
        }
        else if(ch == 3)
        {
            printf("Input sx sy: ");
            double sx, sy;
            scanf("%lf %lf", &sx, &sy);
            instance = getScale(sx,sy)*instance;
        }
        else if(ch == 4)
        {
            instance = getReflectionX()*instance;
        }
        else if(ch == 5)
        {
            instance = getReflectionY()*instance;
        }
        else if(ch == 6)
        {
            printf("Input a b: ");
            double sx, sy;
            scanf("%lf %lf", &sx, &sy);
            instance = getSearing(sx,sy)*instance;
        }
        instance.print();
        puts("\n\n");
    }
    puts("Green is Original");
    puts("Red is Transformed");

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
    glutCreateWindow ("Transformation");
    glutDisplayFunc (display);
    myinit();
    glutMainLoop();
    return 0;
}
