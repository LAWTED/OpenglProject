#include <GLUT/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

// GLfloat cloud[][2] = {{-0.1, 0.3}, {0.0, 0.3}, {0.1, 0.3}, {-0.3, 0.2}, {-0.2, 0.2}, {-0.1, 0.2}, {0.0, 0.2}, {0.1, 0.2}, {0.2, 0.2}, {-0.4, 0.1}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {0.2, 0.1}, {-0.4, 0.0}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}, {0.2, 0.0}, {0.3, 0.0}, {-0.2, -0.1}, {-0.1, -0.1}, {0.0, -0.1}, {0.1, -0.1}};

// GLfloat cloudLayer2[][2] = {{-0.1, 0.2}, {0.0, 0.2}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}};

// GLfloat cloudLayer3[][2] = {{-0.1, 0.1}, {0.0, 0.1}, {-0.1, 0.0}, {0.0, 0.0}};

GLfloat P = 0.1; // Pixel cube size
GLfloat W = 1000, H = 1000;
GLdouble theta = 45;
GLfloat x = -20;
GLfloat yLook = 1;
GLfloat CutOff = 30;
GLfloat Linear = 0.1;
GLfloat Quadratic = 0.1;
GLfloat Constant = 1.0;
void idle()
{
    glutPostRedisplay();
}

void oneCube(GLfloat x, GLfloat y, GLfloat z, GLfloat L)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidCube(L);
    glPopMatrix();
}

void oneRect(GLfloat x, GLfloat y, GLfloat z, GLfloat W, GLfloat H, GLfloat D)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glScaled(W, H, D);
    glutSolidCube(1);
    glPopMatrix();
}

void oneSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat R, GLint slices, GLint stacks)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidSphere(R, slices, stacks);
    glPopMatrix();
}

void oneCone(GLfloat x, GLfloat y, GLfloat z, GLfloat R, GLfloat H, GLint slices, GLint stacks)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(-90, 1, 0, 0);
    glutSolidCone(R, H, slices, stacks);
    glPopMatrix();
}

void drawAxis()
{
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);
    glEnd();
}

void glrgb(GLfloat r, GLfloat g, GLfloat b)
{
    float R = r / 255.0;
    float G = g / 255.0;
    float B = b / 255.0;
    glColor3f(R, G, B);
}

void drawWall(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(236, 165, 143);
    oneRect(dx, dy, dz, 1.6, 0.1, 1.6);
    glrgb(244, 212, 178);
    oneRect(-0.85 + dx, 0.65 + dy, dz, 0.1, 1.4, 1.6);
    oneRect(dx, 0.65 + dy, -0.85 + dz, 1.6, 1.4, 0.1);
    oneRect(-0.85 + dx, 0.65 + dy, -0.85 + dz, 0.1, 1.4, 0.1);
}

void drawSofa(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(55, 65, 87);
    oneRect(0.3 + dx, 0.1 + dy, 0.6 + dz, 0.8, 0.2, 0.4);
    oneRect(0.75 + dx, 0.2 + dy, 0.6 + dz, 0.1, 0.4, 0.4);
    oneRect(-0.15 + dx, 0.2 + dy, 0.6 + dz, 0.1, 0.4, 0.4);
    oneRect(0.3 + dx, 0.3 + dy, 0.7 + dz, 0.8, 0.2, 0.2);
}

void drawTable(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(86, 56, 50);
    oneRect(dx, dy, dz, 0.4, 0.1, 1.0);
    oneRect(dx, -0.2 + dy, 0.4 + dz, 0.4, 0.3, 0.1);
    oneRect(dx, -0.2 + dy, 0.4 + dz, 0.4, 0.3, 0.1);
    oneRect(dx, -0.2 + dy, -0.4 + dz, 0.4, 0.3, 0.1);
}

void drawMonitor(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(12, 12, 12);
    oneRect(-0.1 + dx, 0.015 + dy, dz, 0.1, 0.03, 0.2);
    oneRect(-0.1 + dx, 0.13 + dy, dz, 0.05, 0.2, 0.05);
    oneRect(-0.05 + dx, 0.18 + dy, dz, 0.05, 0.05, 0.05);
    oneRect(dx, 0.18 + dy, dz, 0.03, 0.3, 0.4);
}

void drawKeyBoard(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(0, 0, 0);
    oneRect(0.1 + dx, 0.005 + dy, 0.1 + dz, 0.1, 0.01, 0.2);
    oneRect(0.1 + dx, 0.005 + dy, -0.1 + dz, 0.075, 0.01, 0.075);
}

void drawLamp(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(0, 0, 0);
    oneRect(dx, 0.025 + dy, dz, 0.2, 0.05, 0.2);
    oneRect(dx, 0.35 + dy, dz, 0.05, 0.6, 0.05);
    oneCone(dx, 0.7 + dy, dz, 0.1, 0.2, 10, 10);
    // oneSphere(dx, 0.7 + dy, dz, 0.05, 10, 10);
}

void drawSmallDesk (GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(86, 56, 50);
    oneRect(dx, 0.075 + dy, dz, 0.4, 0.05, 0.3);
    oneRect(dx, 0.225 + dy, dz, 0.4, 0.05, 0.3);
    oneRect(0.225 + dx, 0.125 + dy, dz, 0.05, 0.25, 0.3);
    oneRect(-0.225 + dx, 0.125 + dy, dz, 0.05, 0.25, 0.3);
    oneSphere(dx, 0.275 + dy, dz, 0.05, 10, 10);
}

void addSpotLight() {
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]){0.0, 2.0, 0.0, 1});
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (GLfloat[]){0.0, -1.0, 0.0});
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, (GLfloat[]){2.6});
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (GLfloat[]){0.6});
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, (GLfloat[]){1.0});
    glPopMatrix();
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    addSpotLight();
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cos(theta), yLook, sin(theta), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void draw()
{
    init();
    drawWall(0, 0, 0);
    drawSofa(0, 0.05, 0);
    drawTable(-0.6, 0.4, 0.1);
    drawMonitor(-0.6, 0.45, 0.1);
    drawKeyBoard(-0.6, 0.45, 0.1);
    drawSmallDesk(0.3, 0.05, 0);
    drawAxis();
    // oneSphere(0, 0, 0, 1, 20, 20);
    // glFlush();
    glutSwapBuffers();
}
void mySpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case 'a':
        theta += 0.1;
        break;
    case 'd':
        theta -= 0.1;
        break;
    case 'w':
        yLook += 0.1;
        break;
    case 's':
        yLook -= 0.1;
        break;
    case 'o':
        CutOff += 2;
        break;
    case 'p':
        CutOff -= 2;
        break;
    case 'k':
        Linear += 0.1;
        break;
    case 'l':
        Linear -= 0.1;
        break;
    case 'u':
        Quadratic += 0.1;
        break;
    case 'i':
        Quadratic -= 0.1;
        break;
    case 'h':
        Constant += 0.1;
        break;
    case 'j':
        Constant -= 0.1;
        break;
    }
    cout << "Cutoff: " << CutOff << "Linear" << Linear << "Quadratic" << Quadratic << "Constant" << Constant << endl;
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    cout << "Hello, this is Lawted's Home" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(W, H);
    glutCreateWindow("Lawted's Home");
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    init();
    glutSpecialFunc(mySpecialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
