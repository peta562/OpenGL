#include <iostream>
#include <freeglut.h>
#include <stdlib.h>


// цвет
float red = 1.0f, blue = 1.0f, green = 1.0f;

// угол
float angle = 0.0f;

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        red = 1.0;
        green = 0.0;
        blue = 0.0; 
        break;
    case GLUT_KEY_F2:
        red = 0.0;
        green = 1.0;
        blue = 0.0; 
        break;
    case GLUT_KEY_F3:
        red = 0.0;
        green = 0.0;
        blue = 1.0; 
        break;
    }
}
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // установка камеры
    gluLookAt(0.0f, 0.0f, 4.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);
    
    //поворот на заданную величину
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // установить цвет модели
    glColor3f(red, green, blue);
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
    glutIdleFunc(renderScene);

    // Новые функции
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // цикл обработки событий
    glutMainLoop();


    return 0;
}