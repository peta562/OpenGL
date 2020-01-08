#include <freeglut.h>
#include <iostream>

using namespace std;

// размеры координатной сетки
float mx = 1.0;
float my = 1.0;


float dx = 0.0;
float dy = 0.0;

float angle = 0.0;

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 109:
		mx += 0.1;
		my += 0.1;
		break;
	case 110:
		mx -= 0.1;
		my -= 0.1;
		break;
	case 122:
		angle += 1.0;
		break;
	case 99:
		angle -= 1.0;
		break;

	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		dx -= 1.0;
		break;
	case GLUT_KEY_RIGHT:
		dx += 1.0;
		break;
	case GLUT_KEY_UP:
		dy += 1.0;
		break;
	case GLUT_KEY_DOWN:
		dy -= 1.0;
		break;
	}
	//обновить картинку
	glutPostRedisplay();
}

void changeSize(int w, int h) 
{
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, w, h);
	
	gluOrtho2D(-10, 10, -10, 10);
	//gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);
	
}

// риусем объект
void drawObject()
{
	// угол
	float t;
	// шаг
	float step = 0.01;
	glBegin(GL_LINES);
	glColor3d(0.5, 0.6, 0.2);
	for (float i = 0; i <= 360.0; i += step)
	{
		t = 20 * 3.1415 * i / 180.0;
		glVertex2d(6.2*(cos(t)-(cos(3.1*t)/3.1)), 6.2 * (sin(t) - (sin(3.1 * t) / 3.1)));
	}
	glEnd();
}

void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLineWidth(1);       // ширина сетки

    glBegin(GL_LINES); //сетка
		glColor3d(1, 1, 1);
		glVertex2d(-10, 0);
		glVertex2d(10, 0);
		glVertex2d(0, -10);
		glVertex2d(0, 10);
	glEnd();

	glPushMatrix();
	glScalef(mx, my, 1.0f);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(dx, dy, 0.0);
	drawObject();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{

	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("task");

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	// Основной цикл GLUT
	glutMainLoop();

	return 0;
}


