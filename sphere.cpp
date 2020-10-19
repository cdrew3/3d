#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
//#include <time>
#include <cstdlib>

#include <cmath>
#include <cstdio>
#include <vector>
#include <time.h>
#include <chrono>

#define PI 3.14159265

using namespace std;
using namespace std::chrono;

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;
bool is_first_time = true;
int prev_mouse_x, prev_mouse_y, dx, dy;
vector<int> xarr;
vector<int> yarr;
high_resolution_clock::time_point time_old;

void redisplayFunc(void) {

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-8.0);
    glColor3f(0.2, 0.8, 0.1);
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius,20,20);
    glFlush();

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
    xRotated += 0.0;
    yRotated += 0.0;
    zRotated += 0.0;
    //redisplayFunc();
}

void look(int x, int y) {

    if (is_first_time) {
        time_old = high_resolution_clock::now();
        prev_mouse_x = x;
        prev_mouse_y = y;
        is_first_time = false;
        return;
    }

    high_resolution_clock::time_point time_new = high_resolution_clock::now();
    duration<double, std::milli> dur = time_new - time_old;

    cout << dur.count() << " milliseconds diff\n";

    int delta_x = x - prev_mouse_x;
    int delta_y = y - prev_mouse_y;
    //int delta_z = x - prev_mouse_x;

    //float angle_delta = atan2(abs(y - prev_mouse_y),abs(x - prev_mouse_x)) * 180/PI; 

    prev_mouse_x = x;
    prev_mouse_y = y;
    time_old = time_new;
    redisplayFunc();
}

void keyboardFunc(unsigned char key, int x, int y) {

    switch(key) {

        case 'r': xRotated = yRotated = zRotated = 0; redisplayFunc(); break;
        break;
    };

}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutCreateWindow("Sphere Rotating Animation");
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //xRotated = yRotated = zRotated = 0.0;
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(redisplayFunc);
    glutReshapeFunc(reshapeFunc);
    glutMotionFunc(look);
    glutKeyboardFunc(keyboardFunc);
    //glutIdleFunc(idleFunc);
    glutMainLoop();
    return 0;
}


















/*
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
using namespace std;

static int win;

void disp(void);
void keyb(unsigned char key, int x, int y);

int main(int argc, char **argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
glutInitWindowSize(500,500);
win = glutCreateWindow("Here is a sphere, for some reason");
glutDisplayFunc(disp);
glutKeyboardFunc(keyb);
glClearColor(0.0,0.0,0.0,0.0);
glutMainLoop();
return 0;
}

void disp(void){
glClear(GL_COLOR_BUFFER_BIT);

glutWireSphere(0.5,50,100);
glutSwapBuffers();
}

void keyb(unsigned char key, int x, int y){
if(key == 'q'){
glutDestroyWindow(win);
exit(0);
}
}
*/
