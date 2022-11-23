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
GLfloat fogY = 0.12;
bool fog = false;
void idle()
{
    if (fogY > 0.18)
    {
        fog = false;
    }
    if (fogY > 0.20)
    {
        fogY = 0.12;
        fog = true;
    }
    else
    {
        fogY += 0.001;
    }
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

void oneTorus(GLfloat x, GLfloat y, GLfloat z, GLfloat R, GLfloat r, GLint slices, GLint stacks)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidTorus(R, r, slices, stacks);
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

void glrgba(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    float R = r / 255.0;
    float G = g / 255.0;
    float B = b / 255.0;
    float A = a / 1.0;
    glColor4f(R, G, B, A);
}

void drawWall(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(244, 212, 178);
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
    glrgb(200, 200, 200);
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

void drawSmallDesk(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(86, 56, 50);
    oneRect(dx, 0.075 + dy, dz, 0.4, 0.05, 0.3);
    oneRect(dx, 0.225 + dy, dz, 0.4, 0.05, 0.3);
    oneRect(0.225 + dx, 0.125 + dy, dz, 0.05, 0.25, 0.3);
    oneRect(-0.225 + dx, 0.125 + dy, dz, 0.05, 0.25, 0.3);
}

void drawCup(GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(255, 255, 255);
    oneRect(dx, 0.05 + dy, dz, 0.05, 0.1, 0.05);
}

void drawFog(GLfloat dx, GLfloat dy, GLfloat dz)
{

    glrgba(255, 255, 255, 0.8);
    oneSphere(dx, fogY + dy, fogY / 10 + dz, fogY / 10, 20, 20);
    oneSphere(0.02 + dx, 0.06 + fogY / 2 + dy, fogY / 10 + dz, fogY / 20, 20, 20);
}

void drawSmallLeg( GLfloat dx, GLfloat dy, GLfloat dz)
{
    glrgb(185, 191, 205);
    oneRect(-0.05 + dx, 0.01 + dy, -0.1 + dz, 0.07, 0.02, 0.1);
    oneRect(0.05 + dx, 0.01 + dy, -0.1 + dz, 0.07, 0.02, 0.1);
    glrgb(42, 6, 2);
    oneRect(-0.05 + dx, 0.03 + dy, -0.1 + dz, 0.06, 0.02, 0.08);
    oneRect(0.05 + dx, 0.03 + dy, -0.1 + dz, 0.06, 0.02, 0.08);
    glrgb(0, 0, 0);
    oneRect(-0.05 + dx, 0.05 + dy, -0.12 + dz, 0.02, 0.02, 0.04);
    oneRect(0.05 + dx, 0.05 + dy, -0.12 + dz, 0.02, 0.02, 0.04);
    glrgb(170, 155, 134);
    oneRect(-0.05 + dx, 0.14 + dy, -0.08 + dz, 0.05, 0.2, 0.05);
    oneRect(0.05 + dx, 0.14 + dy, -0.08 + dz, 0.05, 0.2, 0.05);
}

void drawLargeLeg(GLfloat dx, GLfloat dy, GLfloat dz ) {
    glrgb(209, 188, 161);
    oneRect(-0.05 + dx, 0.025 + dy, -0.09 + dz, 0.05, 0.05, 0.04);
    oneRect(0.05 + dx, 0.025 + dy, -0.09 + dz, 0.05, 0.05, 0.04);
    glrgb(182, 195, 207);
    oneRect(-0.05 + dx, 0.035 + dy, 0.02 + dz, 0.07, 0.07, 0.16);
    oneRect(0.05 + dx, 0.035 + dy, 0.02 + dz, 0.07, 0.07, 0.16);
}

void drawBody(GLfloat dx, GLfloat dy, GLfloat dz) {
    glrgb(163, 174, 185);
    oneRect(dx, 0.15 + dy, dz, 0.14, 0.2, 0.1);
    oneRect(dx, 0.3 + dy, dz, 0.16, 0.1, 0.12);
    glrgb(209, 188, 161);
    oneRect(dx, 0.36 + dy, dz, 0.07, 0.05, 0.05);
    oneRect(dx, 0.46 + dy, dz, 0.14, 0.18, 0.1);
    oneRect(dx, 0.44 + dy, -0.06 + dz, 0.14, 0.22, 0.04);
    glrgb(0, 0, 0);
    oneRect(dx, 0.56 + dy, -0.02 + dz, 0.18, 0.04, 0.14);
}

void drawPerson(GLfloat dx, GLfloat dy, GLfloat dz)
{
    drawSmallLeg(dx, dy, dz);
    drawLargeLeg(dx, 0.2 + dy, 0.05 + dz);
    drawBody(dx, 0.2 + dy, 0.1 + dz);
}

void addSpotLight()
{
    glEnable(GL_LIGHT0);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]){0.0, 2.0, 0.0, 1});
    glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[]){0.2, 0.2, 0.2, 1});
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat[]){0.5, 0.5, 0.5, 1});
    glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat[]){1, 0.5, 1, 1});
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (GLfloat[]){0.0, -1.0, 0.0});
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, (GLfloat[]){1.0});
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (GLfloat[]){0.6});
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, (GLfloat[]){1.0});
    glPopMatrix();
}

void init(void)
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);

    addSpotLight();
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cos(theta), yLook, sin(theta), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void draw()
{
    init();
    drawWall(0, 0, 0);
    drawSofa(0, 0.05, 0);
    drawTable(-0.6, 0.4, 0.1);
    drawMonitor(-0.6, 0.45, 0.1);
    drawKeyBoard(-0.6, 0.45, 0.1);
    drawCup(-0.6, 0.45, 0.4);
    if (fog)
        drawFog(-0.6, 0.45, 0.4);
    drawSmallDesk(0.4, 0.05, 0);
    drawPerson(0.3, 0.05, 0.45);
    drawAxis();
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
