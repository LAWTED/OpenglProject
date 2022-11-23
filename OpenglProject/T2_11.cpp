

#include <GLUT/glut.h>
#include <math.h>

GLfloat cloud[][2] = {{-0.1, 0.3}, {0.0, 0.3}, {0.1, 0.3}, {-0.3, 0.2}, {-0.2, 0.2}, {-0.1, 0.2}, {0.0, 0.2}, {0.1, 0.2}, {0.2, 0.2}, {-0.4, 0.1}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {0.2, 0.1}, {-0.4, 0.0}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}, {0.2, 0.0}, {0.3, 0.0}, {-0.2, -0.1}, {-0.1, -0.1}, {0.0, -0.1}, {0.1, -0.1}};

GLfloat cloudLayer2[][2] = {{-0.1, 0.2}, {0.0, 0.2}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}};

GLfloat cloudLayer3[][2] = {{-0.1, 0.1}, {0.0, 0.1}, {-0.1, 0.0}, {0.0, 0.0}};

GLfloat P = 0.1; // Pixel cube size
GLfloat W = 1000, H = 1000;
GLdouble theta = 0;
GLfloat x = -20;

void idle()
{
    theta += 0.02;
    glutPostRedisplay();
}

void oneCube(GLfloat x, GLfloat y, GLfloat z, GLfloat L)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidCube(L);
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

void drawCloud(GLfloat dx, GLfloat dy, GLfloat dz)
{

    // Draw cloud
    for (int i = 0; i < sizeof(cloud) / sizeof(cloud[0]); i++)
    {
        glColor3f(0.0, 1.0, 1.0);
        oneCube(cloud[i][0] + dx, cloud[i][1] + dy, dz, P);
        if (i < sizeof(cloudLayer2) / sizeof(cloudLayer2[0]))
            oneCube(cloudLayer2[i][0] + dx, cloudLayer2[i][1] + dy, dz - P, P);
        if (i < sizeof(cloudLayer3) / sizeof(cloudLayer3[0]))
            oneCube(cloudLayer3[i][0] + dx, cloudLayer3[i][1] + dy, dz - 2 * P, P);
    }

    // Draw eyes
    glColor3f(0.0, 0.0, 0.0);
    oneCube(-0.2 + dx, 0.12 + dy, dz + P * 0.5, P * 0.3);
    oneCube(0.1 + dx, 0.12 + dy, dz + P * 0.5, P * 0.3);
    // Draw mouth
    for (int i = 0; i < 7; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i + 9) / float(15);
        float x = 0.06 * cosf(theta);
        float y = 0.06 * sinf(theta);
        oneCube(x + dx, y + dy, dz + P * 0.5, P * 0.2);
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {5, 5, 50, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -2.0, 2.0);

    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();
    //    gluLookAt(1, 1, 1 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cos(theta), 1, sin(theta), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //    glRotatef(x, 1.0, 0.0, 0.0);
    //    glRotatef(50, 0.0, 1.0, 0.0);
    //    glRotatef(-30, 0.0, 0.0, 1.0);
}
void draw()
{
    init();
    drawCloud(0, 0, 0);
    // drawAxis();
    // glFlush();
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(W, H);
    glutCreateWindow("I'm a cloud😊");
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

