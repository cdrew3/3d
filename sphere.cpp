#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
//#include <time>
#include <cstdlib>

#include <cmath>
#include <cstdio>
#include <vector>
#include <chrono>

#define PI 3.14159265

using namespace std;
using namespace std::chrono;

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;
bool is_first_time = true;
float rotx, roty, rotz;
int prev_mouse_x, prev_mouse_y, dx, dy;
vector<int> xarr;
vector<int> yarr;
double theta;
int MAXARRSIZE = 5;

double getAngle() {
    
    if (xarr.size() != MAXARRSIZE) return 0.0;

    int x1 = xarr.back();
    int y1 = yarr.back();

    int x2 = xarr.front();
    int y2 = yarr.front();

    double angle = atan2(y1 - y2, x1 - x2) * 180/PI;
    printf("Angle: %f\n", angle);
    return angle;
}

void printArr(std::string head, vector<int> arr) {

    printf("%s: ", head.c_str());
    for (int i = 0; i < arr.size(); i++) {
        if (i == arr.size() - 1) printf("%i\n", arr[i]);
        else {
            printf("%i,", arr[i]);
        }
    }
}

void updateArr(int x, int y) {

    if (xarr.size() < MAXARRSIZE) {
        xarr.push_back(x);
        yarr.push_back(y);
        return;
    }

    if (xarr.size() == MAXARRSIZE) {

        xarr.erase(xarr.begin());
        yarr.erase(yarr.begin());
        xarr.push_back(x);
        yarr.push_back(y);
    }
}

void drawAxes(void) {

    // x
    glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
    glEnd();
    glFlush();

    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);
    glEnd();
    glFlush();

    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-4.0f );
    glVertex3f(0.0, 0.0f ,4.0f );
    glEnd();
    glFlush();
}

void redisplayFunc(void) {

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-8.0);
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0);
    glColor3f(0.2, 0.8, 0.1);
    glRotatef(xRotated,rotx,0.0,0.0);
    glRotatef(yRotated,0.0,roty,0.0);
    glRotatef(zRotated,0.0,0.0,rotz);
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius,20,20);
    glFlush();

    drawAxes();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void idleFunc(void)
{
    //printf("---\nX: %f\nY: %f\nZ: %f\n", xRotated, yRotated, zRotated);
}

void look(int x, int y) {

    if (is_first_time) {
        prev_mouse_x = x;
        prev_mouse_y = y;
        is_first_time = false;
        return;
    }

    int delta_x = x - prev_mouse_x;
    int delta_y = y - prev_mouse_y;
    updateArr(x, y);

    int dx = abs(xarr.back() - xarr.front());
    int dy = abs(yarr.back() - yarr.front());
    if (dx - dy > 3) {
        xRotated += delta_x;
        yRotated += delta_x;
        zRotated += delta_x;
    } else if (dy - dx > 3) {
        xRotated += delta_y;
        yRotated += delta_y;
        zRotated += delta_y;
    }

    prev_mouse_x = x;
    prev_mouse_y = y;
    redisplayFunc();
}

void keyboardFunc(unsigned char key, int x, int y) {

    switch(key) {

        case 'r': xRotated = yRotated = zRotated = 0; redisplayFunc(); break;
        case 'd': redisplayFunc(); break;
        case 'x': if (rotx == 0.0) rotx = 1.0; else rotx = 0.0; break;
        case 'y': if (roty == 0.0) roty = 1.0; else roty = 0.0; break;
        case 'z': if (rotz == 0.0) rotz = 1.0; else rotz = 0.0; break;
        break;
    };

}

int main (int argc, char **argv)
{
    rotx = roty = rotz = 0.0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutCreateWindow("Sphere Rotating Animation");
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0,0.0,0.0,0.0);
    glutMotionFunc(look);
    glutDisplayFunc(redisplayFunc);
    glutIgnoreKeyRepeat(1);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMainLoop();

    return 0;
}
