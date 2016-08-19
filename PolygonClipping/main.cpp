#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#define SIZE 250

#define LOWX -SIZE
#define HIGHX SIZE
#define LOWY -SIZE
#define HIGHY SIZE

#define WIDTH (2*SIZE)
#define HEIGHT (2*SIZE)


struct PNT
{
    int x, y;

    PNT()
    {
    }

    PNT operator=(const PNT& a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

    bool operator!=(const PNT & a)
    {
        return ((x != a. x)||(y!=a.y));
    }
};

struct LINE
{
    PNT point1, point2;
};

vector <PNT> clippand;
vector <PNT> clipper;

bool isLeft(PNT A, PNT B, PNT C)
{
    return ( (B.x-A.x)*(C.y-A.y) - (B.y-A.y) * (C.x-A.x) ) > 0;
}


PNT findIntersect(PNT A, PNT B, PNT C, PNT D)
{
    double dx = A.x-B.x, dy = A.y-B.y;
    double a1, b1, c1, a2, b2, c2;
    a1 = dy;
    b1 = -dx;
    c1 = dx*B.y-dy*B.x;

    dx = C.x-D.x, dy = C.y-D.y;
    a2 = dy;
    b2 = -dx;
    c2 = dx*D.y-dy*D.x;
    PNT I;
    I.x = (b1*c2-b2*c1)/(a1*b2-a2*b1);
    I.y = (c1*a2-c2*a1)/(a1*b2-a2*b1);
    return I;
}

void build()
{
    vector<PNT>::iterator clipperIt;
    for(clipperIt = clipper.begin(); clipperIt != clipper.end(); clipperIt++)
    {
        PNT A = *clipperIt, B;
        if(clipperIt+1 != clipper.end())
            B = *(clipperIt+1);
        else
            B = *(clipper.begin());

        vector<PNT> result;
        PNT F, S;
        for(vector<PNT>::iterator clippandIt = clippand.begin(); clippandIt != clippand.end(); clippandIt++)
        {
            PNT P = *clippandIt;
            if(clippandIt == clippand.begin())
            {
                F = P;
            }
            else if((isLeft(A, B, S) && (!isLeft(A, B, P))) || (isLeft(A, B, P) && (!isLeft(A, B, S))))
            {

                PNT I = findIntersect(A, B, S, P);
                result.push_back(I);
            }
            S = P;
            if(isLeft(A,B,S))
            {
                result.push_back(S);
            }
        }
        if((isLeft(A, B, S) && (!isLeft(A, B, F))) || (isLeft(A, B, F) && (!isLeft(A, B, S))))
        {

            PNT I = findIntersect(A, B, S, F);
            result.push_back(I);
        }
        clippand = result;
    }
}

void BUILDER()
{
    // preliminary talks
    printf("<<<< Cohen Sutherland Algorithm >>> \n");
    puts("Input order:");
    puts("N = Number of vertices in clipping polygon");
    puts("N lines containing vertex: x  y");
    puts("M = Number of Vertices in the Polygon to be clipped");
    puts("M lines containing vertex: x  y");
    puts("-------------------------------------------");

    // clear old values
    clippand.clear();
    clipper.clear();

    int n, m;
    PNT temp;

    scanf("%d", &n);
    for(int i = 0; i<n; i++)
    {
        scanf("%d %d", &temp.x, &temp.y);
        clipper.push_back(temp);
    }
    scanf("%d", &m);
    for(int i = 0; i<m; i++)
    {
        scanf("%d %d", &temp.x, &temp.y);
        clippand.push_back(temp);
    }

    // build
    build();

    // output description
    puts("\n\nOutput Description:");
    puts("Line inside are in BLUE");
    //puts("Line outside are in RED");
    puts("Window are in BLACK box");
}


void setAxes()
{
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    glVertex2d(LOWX, 0);
    glVertex2d(HIGHX, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0, LOWY);
    glVertex2d(0, HIGHY);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void drawClippand()
{
    glColor3f(0.0, 0.0, 1.0);

    vector<PNT>::iterator it;
    PNT  A, B;
    for(it = clippand.begin(); it != clippand.end(); it++)
    {
        A= *it;
        if( (it+1) != clippand.end())
            B = *(it+1);
        else
            B= *(clippand.begin());

        glBegin(GL_LINES);
        glVertex2i(A.x, A.y);
        glVertex2i(B.x, B.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void drawClipper()
{
    glColor3f(0.0, 0.0, 0.0);

    vector<PNT>::iterator it;
    PNT A, B;
    for(it = clipper.begin(); it != clipper.end(); it++)
    {
        A = *it;
        if( (it+1) != clipper.end())
            B = *(it+1);
        else
            B= *(clipper.begin());

        glBegin(GL_LINES);
        glVertex2d(A.x, A.y);
        glVertex2d(B.x, B.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void drawAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glEnable(GL_LINE_SMOOTH);
    //glLineWidth(SCALE);

    setAxes();
    glutSwapBuffers();
    drawClipper();
    glutSwapBuffers();
    drawClippand();
    glutSwapBuffers();

    glFlush();
    glutSwapBuffers();
}


void myinit()
{
    glClearColor(1.0,1.0,1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(LOWX, HIGHX, LOWY, HIGHY);
    glClearColor(1.0,1.0,1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
    BUILDER();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200, 80);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Sutherland-Hodgman Algorithm");

    myinit();

    glutDisplayFunc(drawAll);
    glutMainLoop();

    return 0;
}
/**
3
0 0
100 0
50 50

6
80 0
82 68
51 23
22 11
27 -23
56 -48

4
25 25
-25 25
-25 -25
25 -25

3
-16 -32
18 -33
18 33
*/


