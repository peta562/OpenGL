#include <iostream>
#include <freeglut.h>

float angle = 0.0f;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // установка камеры
    gluLookAt(0.0f, 0.0f, 4.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
      glVertex3f(-0.5, -0.5, 0.0);
      glVertex3f(0.0, 0.5, 0.0);
      glVertex3f(0.5, -0.5, 0.0);
    glEnd();

    angle += 0.5f;

    glutSwapBuffers();
}


void changeSize(int w, int h) {

    // деление на ноль
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;

    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);

    // Reset матрицы
    glLoadIdentity();

    // определяем окно просмотра
    glViewport(0, 0, w, h);

    // установить корректную перспективу.
    gluPerspective(45, ratio, 1, 1000);

    // вернуться к модели
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    // инициализация GLUT and создание окна
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("test");

    // регистрация вызовов функций GLUT
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Новая функция 
    glutIdleFunc(renderScene);

    // цикл обработки событий
    glutMainLoop();


    return 0;
}