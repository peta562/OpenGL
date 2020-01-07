#include <iostream>
#include <freeglut.h>
#include <stdlib.h>

float deltaAngle = 0.0f;
int xOrigin = -1;

// цвет
float red = 1.0f, blue = 1.0f, green = 1.0f;

// угол
float angle = 0.0f;

// координаты вектора направления движения камеры
float lx = 0.0f, lz = -1.0f;
// XZ позиция камеры
float x = 0.0f, z = 5.0f;

void mouseButton(int button, int state, int x, int y) {

    // только при начале движения, если нажата левая кнопка
    if (button == GLUT_LEFT_BUTTON) {

        // когда кнопка отпущена
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y) {

    // если левая кнопка опущена
    if (xOrigin >= 0) {

        // обновить deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // Обновление направления камеры
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}
void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

    // тело снеговика
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // голова снеговика
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);
    // глаза снеговика
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    // нос снеговика
    glColor3f(1.0f, 0.5f, 0.5f);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void processSpecialKeys(int key, int x, int y) {
    float fraction = 0.1f;
    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
}
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // установка камеры
    gluLookAt(x, 1.0f, z, // положение камеры
        x + lx, 1.0f, z + lz,  // направление вектора обзора
        0.0f, 1.0f, 0.0f); // наклон камеры


    // нарисуем "землю"
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS); // полигон с коондинатами
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // Нарисуем 64 снеговика
    for (int i = -4; i < 4; i++)
        for (int j = -4; j < 4; j++) 
        {
            glPushMatrix();
            glTranslatef(i * 5.0, 0, j * 5.0);
            drawSnowMan();
            glPopMatrix();
        }


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
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // Новые функции
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glEnable(GL_DEPTH_TEST); // Инициализация OpenGL функции теста
    
    // цикл обработки событий
    glutMainLoop();


    return 0;
}