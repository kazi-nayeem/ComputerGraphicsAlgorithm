#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 100

#define LOWX -SIZE
#define HIGHX SIZE
#define LOWY -SIZE
#define HIGHY SIZE

#define WIDTH (2*SIZE)
#define HEIGHT (2*SIZE)

#define SCALE ((double)WIDTH / (HIGHX - LOWX))

struct PNT
{
    int x, y, code;

    PNT()
    {
        code=0;
    }

    PNT operator=(const PNT& a)
    {
        x = a.x;
        y = a.y;
        code = a.code;
        return *this;
    }

    bool operator!=(PNT a)
    {
        return ((x != a. x)||(y!=a.y));
    }

    int getCode()
    {
        return code;
    }

    bool bit1()
    {
        return code&8;
    }
    bool bit2()
    {
        return code&4;
    }
    bool bit3()
    {
        return code&2;
    }
    bool bit4()
    {
        return code&1;
    }
};

struct LINE
{
    int mx, my;
    PNT point1, point2;

    void calculateM()
    {
        mx = point2.x-point1.x;
        my = point2.y-point1.y;
    }

    void print()
    {
        printf("\n%d %d %d\n%d %d %d\n", point1.x, point1.y,point1.code, point2.x, point2.y, point2.code);
    }
};


int xmin, xmax, ymin, ymax;
vector <LINE> visible;
vector <LINE> notVisible;
vector <LINE> clipCandidate;


bool sign(int a)
{
    return a>0;
}

int calculateCode(PNT& p)
{
    p.code = 0;
    if(sign(p.y-ymax))
        p.code^=8;
    if(sign(ymin-p.y))
        p.code^=4;
    if(sign(p.x-xmax))
        p.code^=2;
    if(sign(xmin-p.x))
        p.code^=1;
    return p.code;
}

int quotient(int a, int b)
{
    int sign =1;
    if(a<0)
    {
        sign = -sign;
        a = -a;
    }

    if(b<0)
    {
        sign = -sign;
        b = -b;
    }

    int ans= a/b;

    if((2*(a%b))>= b)
        ans++;
    ans*= sign;
    return ans;
}

PNT findIntersect(const LINE & l, PNT a, int mx, int my)
{
    //printf("ok");
    if(a.getCode()==0)
        return a;

    PNT temp;
    if(a.bit1())
    {
        temp.y = ymax;
        temp.x = quotient(my*a.x + (ymax-a.y) * mx, my);
        return temp;
    }

    if(a.bit2())
    {
        temp.y = ymin;
        temp.x = quotient(my*a.x + (ymin-a.y) * mx, my);
        return temp;
    }

    if(a.bit3())
    {
        temp.x = xmax;
        temp.y = quotient(mx*a.y + (xmax-a.x) * my, mx);
        return temp;
    }

    if(a.bit4())
    {
        temp.x = xmin;
        temp.y = quotient(mx*a.y + (xmin-a.x) * my, mx);
        return temp;
    }

    return temp;
}

void handleClipCand(LINE a)
{
    a.calculateM();
    PNT pseudo1 = findIntersect(a,a.point1, a.mx, a.my);


    LINE w;
    if(a.point1 != pseudo1)
    {
        w.point1 = a.point1;
        w.point2 = pseudo1;
        notVisible.push_back(w);

        w.point1 = pseudo1;
        w.point2 = a.point2;
        clipCandidate.push_back(w);
        return;
    }

    PNT pseudo2 = findIntersect(a,a.point2, a.mx, a.my);
    if(a.point2 != pseudo2)
    {
        w.point1 = a.point2;
        w.point2 = pseudo2;
        notVisible.push_back(w);

        w.point1 = a.point1;
        w.point2 = pseudo2;
        clipCandidate.push_back(w);
    }

    return;
}

void decide(LINE a)
{
    int code1, code2;
    code1 = calculateCode(a.point1);
    code2 = calculateCode(a.point2);

    if((code1+code2) == 0)
    {
        visible.push_back(a);
        return;
    }

    if(code1 & code2)
    {
        notVisible.push_back(a);
        return;
    }
    //a.print();

    //getchar();
    handleClipCand(a);
    return;
}


void BUILDER()
{
    // preliminary talks
    printf("<<<< Cohen Sutherland Algorithm >>>>\n");
    puts("Input in the following order:-");
    puts("Xmax  Xmin  Ymax  Ymin");
    puts("N = Number of line segment");
    puts("N lines having x1  y1  x2  y2 of a line segment");
    puts("-----------------------------------------------------");

    // clear values
    notVisible.clear();
    visible.clear();
    clipCandidate.clear();

    // window input
    scanf("%d %d %d %d", &xmax, &xmin, &ymax, &ymin);
    // line segment data
    int n,  x, y;
    scanf("%d", &n);
    // line segment input
    LINE temp;
    for(int i=0; i<n; i++)
    {
        scanf("%d %d", &x, &y);
        temp.point1.x = x;
        temp.point1.y = y;
        scanf("%d %d", &x, &y);
        temp.point2.x=x;
        temp.point2.y=y;
        clipCandidate.push_back(temp);
    }

    //build
    while(!clipCandidate.empty())
    {
        temp = clipCandidate.back();
        clipCandidate.pop_back();
        decide(temp);
    }

    // output description
    puts("\n\nOutput Description:");
    puts("Line inside are in BLUE");
    puts("Line outside are in RED");
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

void drawNotVisible()
{
    glColor3f(1.0, 0.0, 0.0);

    for(vector <LINE>::iterator it = notVisible.begin(); it!=notVisible.end(); it++)
    {
        glBegin(GL_LINES);
        glVertex2d(it->point1.x, it->point1.y);
        glVertex2d(it->point2.x, it->point2.y);
        glEnd();
    }
}

void drawVisible()
{
    glColor3f(0.0, 0.0, 1.0);

    for(vector <LINE>::iterator it = visible.begin(); it!=visible.end(); it++)
    {
        glBegin(GL_LINES);
        glVertex2d(it->point1.x, it->point1.y);
        glVertex2d(it->point2.x, it->point2.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void drawPolygon()
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmin, ymax);
    glVertex2i(xmin, ymin);
    glEnd();
    glFlush();
}

void drawAll()
{
    glClearColor(1.0,1.0,1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glEnable(GL_LINE_SMOOTH);
    //glLineWidth(SCALE);


    glClearColor(1.0,1.0,1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);
    setAxes();
    glutSwapBuffers();
    drawPolygon();
    drawNotVisible();
    drawVisible();

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
    glutCreateWindow("Cohen Sutherland Algorithm");

    myinit();

    glutDisplayFunc(drawAll);
    glutMainLoop();

    return 0;
}

/**
40 -60 120 20
5
-80 40
-20 140

-20 100
60 160

-40 60
20 40

20 -40
60 60

-80 140
-40 200
*/


/**
25
-25
25
-25

3
22 20
-23 -22

16 34
-36 -11

0 0
50 1
*/
