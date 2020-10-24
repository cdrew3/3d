#include <GL/gl.h>
//#include <GL/Glu.h>
#include <GL/glut.h>
#include <math.h>

float CT[16];

//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0); glVertex3d(0,0,length); // along the z-axis
    glEnd();
    glTranslated(0, 0,length -0.2); 
    glutWireCone(0.04, 0.2, 12, 9);
    glPopMatrix();
}   


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayWire(void)
{
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
    // load our precomputed rotation matrix.
    glMatrixMode(GL_MODELVIEW); 
    glLoadMatrixf(CT);
    // position and aim the camera
    gluLookAt(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glColor3d(0,0,0); // draw black lines
    axis(0.5);                   // z-axis
    glPushMatrix(); 
    glRotated(90, 0,1.0, 0);
    axis(0.5);                  // y-axis
    glRotated(-90.0, 1, 0, 0);
    axis(0.5);                  // z-axis
    glPopMatrix();  

    glPushMatrix();
    glTranslated(0.5, 0.5, 0.5); // big cube at (0.5, 0.5, 0.5)
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix(); 
    glTranslated(1.0,1.0,0);    // sphere at (1,1,0)
    glutWireSphere(0.25, 10, 8);
    glPopMatrix();  

    glPushMatrix(); 
    glTranslated(1.0,0,1.0);    // cone at (1,0,1)
    glutWireCone(0.2, 0.5, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,1,1);
    glutWireTeapot(0.2); // teapot at (1,1,1)
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0 ,0); // torus at (0,1,0)
    glRotated(90.0, 1,0,0);
    glutWireTorus(0.1, 0.3, 10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0 ,0); // dodecahedron at (1,0,0)
    glScaled(0.15, 0.15, 0.15);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.0 ,1.0); // small cube at (0,1,1)
    glutWireCube(0.25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0 ,1.0); // cylinder at (0,0,1)
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj,GLU_LINE);
    gluCylinder(qobj, 0.2, 0.2, 0.4, 8,8);
    glPopMatrix();
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    static float oldX,oldY,oldZ;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            // When the mouse first goes down we compute a point
            // on our imaginary sphere that corresponds to the point (x,y)
            oldX = x-240;
            oldY = 240 - y; // convert from window coordinates
            oldZ = sqrt(240*240-oldX*oldX-oldY*oldY);
        }
        else if(state == GLUT_UP)
        {
            // Compute the second point when the mouse goes up.
            float newX = x - 240;
            float newY = 240 - y;
            float newZ = sqrt(240*240-newX*newX-newY*newY);

            // Compute the cross product of the two vectors
            float uX = newY*oldZ-newZ*oldY;
            float uY = newZ*oldX-newX*oldZ;
            float uZ = newX*oldY-newY*oldX;

            // |new cross old| = |new| |old| sin(angle)
            float angle = asin(sqrt(uX*uX+uY*uY+uZ*uZ)/(240*240))*180/3.14159265;
            // Compute the new transformation matrix
            glMatrixMode(GL_MODELVIEW); 
            glLoadMatrixf(CT);
            glRotated(angle,uX,uY,uZ);
            glGetFloatv(GL_MODELVIEW_MATRIX,CT);
            // Draw the picture
            displayWire();
        }
    }
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation testbed - wireframes");
    glutDisplayFunc(displayWire);
    glutMouseFunc(myMouse);
    glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white
    glViewport(0, 0, 480, 480);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    // Get a copy of the base modelview matrix.
    glGetFloatv(GL_MODELVIEW_MATRIX,CT);

    glutMainLoop();
}

