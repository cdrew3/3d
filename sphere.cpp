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

GLint xRotated, yRotated, zRotated, iRotated;
GLdouble radius=1;
bool is_first_time = true;
float rotx, roty, rotz;
int prev_mouse_x, prev_mouse_y, dx, dy;
vector<int> xarr;
vector<int> yarr;
double theta;
int MAXARRSIZE = 5;
bool first_display = true;
int i = 0;
float CT[16];
bool MOUSE_DOWN;
GLfloat xStart, yStart;

double getAngle() {
    
    if (xarr.size() != MAXARRSIZE) return 0.0;

    int x1 = xarr.back();
    int y1 = yarr.back();

    int x2 = xarr.front();
    int y2 = yarr.front();

    double angle = atan2(y1 - y2, x1 - x2) * 180/PI;
    printf("Angle: %d\n", angle);
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

    glBegin(GL_LINES);

    // x
    glColor3f(1.0,0.0,0.0); // red x
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);

    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);

    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glVertex3f(0.0, 0.0f ,-4.0f );
    glVertex3f(0.0, 0.0f ,4.0f );

    glEnd();
}

void redisplayFunc(void) {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(0.0,0.0,-8.0);
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.0);
    glColor3f(0.2, 0.8, 0.1);
    glutSolidSphere(radius,20,20);
    glRotatef(iRotated,rotx,roty,rotz);
    drawAxes();
    //glRotatef(xRotated,rotx,0.0,0.0);
    //glRotatef(yRotated,0.0,roty,0.0);
    //glRotatef(zRotated,0.0,0.0,rotz);

    glPopMatrix();
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);
    glMatrixMode(GL_MODELVIEW);
}

void idleFunc(void)
{
    redisplayFunc();
}

void look(int x, int y) {

    if ((rotx == 0.0 and roty == 0.0 and rotz == 0.0) || ! MOUSE_DOWN) { return; }

    /*if (is_first_time) {
        prev_mouse_x = x;
        prev_mouse_y = y;
        is_first_time = false;
        return;
    }*/

    int delta_x = x - xStart;
    int delta_y = y - yStart;
    updateArr(x, y);

    int dx = abs(xarr.back() - xarr.front());
    int dy = abs(yarr.back() - yarr.front());
    if (dx - dy > 3) {
        if (rotx) iRotated = xRotated = (xRotated + delta_x) % 360;
        if (roty) iRotated = yRotated = (yRotated + delta_x) % 360;
        if (rotz) iRotated = zRotated = (zRotated + delta_x) % 360;
    } else if (dy - dx > 3) {
        if (rotx) iRotated = xRotated = (xRotated + delta_y) % 360;
        if (roty) iRotated = yRotated = (yRotated + delta_y) % 360;
        if (rotz) iRotated = zRotated = (zRotated + delta_y) % 360;
    }

    printf("%i,%i,%i\n", xRotated, yRotated, zRotated);
    xStart = x;
    yStart = y;
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON) {

        if(state == GLUT_DOWN) {
            xStart = x;
            yStart = y;
            MOUSE_DOWN = true;
        }
        else if(state == GLUT_UP) {
            MOUSE_DOWN = false;

            /*// Compute the new transformation matrix
            glMatrixMode(GL_MODELVIEW); 
            glLoadMatrixf(CT);
            glRotated(angle,uX,uY,uZ);
            glGetFloatv(GL_MODELVIEW_MATRIX,CT);
            // Draw the picture
            displayWire();
            */
        }
    }

}

void keyboardFunc(unsigned char key, int x, int y) {

    switch(key) {

        case 'r':
            xRotated = yRotated = zRotated = 0;
            rotx = roty = rotz = 0.0;
            redisplayFunc();
            break;
        case 'd': redisplayFunc(); break;
        case 'x':
            if (rotx == 0.0) {
                rotx = 1.0;
                roty = 0.0;
                rotz = 0.0;
            } else {
                rotx = 0.0;
            }
            break;
        case 'y':
            if (roty == 0.0) {
                rotx = 0.0;
                roty = 1.0;
                rotz = 0.0;
            } else {
                roty = 0.0;
            }
            break;
        case 'z':
            if (rotz == 0.0) {
                rotx = 0.0;
                roty = 0.0;
                rotz = 1.0;
            } else {
                rotz = 0.0;
            }
            break;
        break;
    };
}

int main (int argc, char **argv)
{
    rotx = roty = rotz = 0.0;
    xRotated = yRotated = zRotated = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutCreateWindow("Sphere Rotating Animation");
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0,0.0,0.0,0.0);
    glutMotionFunc(look);
    glutPassiveMotionFunc(NULL);
    glutDisplayFunc(redisplayFunc);
    glutIgnoreKeyRepeat(1);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMainLoop();

    return 0;
}
