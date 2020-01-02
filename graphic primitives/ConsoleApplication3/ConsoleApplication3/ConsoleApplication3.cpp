#include <windows.h>
#include <GL/gl.h>
#include <GLUT.h>
#include "windows.h"


void resize(int width, int height)
{
}


void  display(void)
{
    int c;

    glLineWidth(1);       // ширина сетки

    glBegin(GL_LINES); //сетка
    glColor3d(1, 1, 1);
    glVertex2d(-5, 1);
    glVertex2d(5, 1);

    glColor3d(1, 1, 1);
    glVertex2d(0, -5);
    glVertex2d(0, 6);
    glEnd();

    glPointSize(5); //круглые точки
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3d(1, 0, 1);
    glVertex2d(-2, 4);

    glColor3d(0, 1, 0);
    glVertex2d(-3, 3);

    glColor3d(0, 3, 45);
    glVertex2d(-2, 5.5);

    glColor3d(1, 1, 0);
    glVertex2d(-4, 4);
    glEnd();
    glDisable(GL_POINT_SMOOTH);

    glPointSize(10); // квадратные точки
    glEnable(GL_POINT);
    glBegin(GL_POINTS);

    glColor3d(1, 1, 0);
    glVertex3d(-4.5, 4, 0);

    glColor3d(1, 0, 0);
    glVertex3d(-2.7, 4, 0);

    glColor3d(0, 1, 1);
    glVertex3d(-3, 5, 0);

    glEnd();

    glDisable(GL_POINT_SMOOTH);


    glLineWidth(1);    //сплошные линии   
    glBegin(GL_LINES);

    glColor3d(1, 0, 1);
    glVertex3d(4.5, 2, 0);
    glVertex3d(3, 3, 0);

    glColor3d(1, 1, 0);
    glVertex3d(4, 2, 0);
    glVertex3d(1, 2, 0);

    glEnd();

    glLineWidth(5);  //прерывистая ломаная линия
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 58360);

    glBegin(GL_LINE_LOOP);

    glColor3d(0, 1, 1);
    glVertex3d(4.5, 4.5, 0);
    glVertex3d(1, 3, 0);

    glColor3d(1, 0, 1);
    glVertex3d(4.5, 5.5, 0);
    glVertex3d(1, 5.5, 0);

    glEnd();

    glDisable(GL_LINE_STIPPLE);
    glDisable(GL_LINE_SMOOTH);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // треугольник
    glBegin(GL_TRIANGLES);
    glColor3d(1, 0, 1);
    glVertex3d(-4, -1, 0);
    glVertex3d(-3, -3, 0);
    glVertex3d(-2, -1, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // прямоугольник
    glBegin(GL_QUADS);
    glColor3d(1, 0, 0);
    glVertex2f(-4.5, -0.75);
    glVertex2f(-4.5, -0.25);
    glVertex2f(-1.5, -0.25);
    glVertex2f(-1.5, -0.75);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // треугольник
    glBegin(GL_TRIANGLES);
    glColor3d(1, 0, 1);
    glVertex3d(3.2, 0.5, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(1.8, 0.5, 0);

    glColor3d(0, 0.75, 0.5);
    glVertex3d(3.2, 0.5, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(4.2, -0.5, 0);

    glColor3d(0.5, 1, 1);
    glVertex3d(4.2, -1.7, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(4.2, -0.5, 0);

    glColor3d(1, 1, 0);
    glVertex3d(4.2, -1.7, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(3.2, -2.6, 0);

    glColor3d(0, 2, 1);
    glVertex3d(3.2, -2.6, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(1.9, -2.65, 0);

    glColor3d(3, 1, 1);
    glVertex3d(0.9, -1.7, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(1.9, -2.65, 0);

    glColor3d(1, 1, 3);
    glVertex3d(0.9, -0.6, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(1.8, 0.5, 0);

    glColor3d(1, 0, 1);
    glVertex3d(0.9, -0.6, 0);
    glVertex3d(2.5, -1, 0);
    glVertex3d(0.9, -1.7, 0);
    glEnd();

    glColor3d(1, 0.6, 1);
    glRasterPos3d(2.1, 1.1, -1.7);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 76);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 65);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 66);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 65);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 50);



    glFlush();
}



void init(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 2.0, 12.0);
    gluLookAt(0, 0, 5, 0, 1, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 20);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("laba2");
    glutReshapeFunc(resize);
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
