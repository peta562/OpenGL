#include <windows.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include "glut.h" 
#include <math.h>
#include <iostream>
using namespace std;

static GLfloat  x = 0, y = 0;
static float ax = 0, ay = 0;


typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char* data;
} AUX_RGBImageRec;

AUX_RGBImageRec* image;


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void test(int x, int y)
{
    ax = x * 0.1f / 8;
    ay = 10 - y * 0.1f / 8;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) // управление мышью
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        glutMotionFunc(test);
}

void display(void)
{
    int i, j;
    int a, b;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-1, -1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    for (i = 1; i <= 8; ++i) {
        for (j = 1; j <= 8; ++j) {
            // Выбор цвета клеточки
            if ((i ^ j) & 1)
                glColor3f(0.4f, 0.4f, 0.8f);
            else
                glColor3f(0.9f, 0.44f, 0.48f);
            // Отрисовка одной клеточки
            glRectf(i * 0.2f, j * 0.2f, (i + 1) * 0.2f, (j + 1) * 0.2f);
        }
    }
    a = ax;
    cout << "x = " << a;
    b = ay;
    cout << " y = " << b << endl;
    glColor3f(0.2f, 0.7f, 0.7f);
    glRectf(a * 0.2f, b * 0.2f, (a + 1) * 0.2f, (b + 1) * 0.2f);
    glPopMatrix();
    glutSwapBuffers();
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(test);

    glutMainLoop();
    return 0; /* ANSI C requires main to return int. */
}
