#include <freeglut.h>
#include <iostream>

using namespace std;


float dx = 0.0;
float dy = 0.0;


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
	
	gluOrtho2D(-100, 100, -100, 100);
	//gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);
	
}

// риусем линию алгоритмом Брезенхема
void drawLine(int x1, int x2, int y1, int y2)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;

	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2d(x2, y2);
	glEnd();
	while (x1 != x2 || y1 != y2)
	{
		glBegin(GL_POINTS);
		glVertex2d(x1, y1);
		glEnd();
		const int error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}

}

// риусем окружность алгоритмом Брезенхема
void drawCircle(int x0, int y0, int radius) {
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		glBegin(GL_POINTS);
			glVertex2d(x0 + x, y0 + y);
			glVertex2d(x0 + x, y0 - y);
			glVertex2d(x0 - x, y0 + y);
			glVertex2d(x0 - x, y0 - y);
		glEnd(); 
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			x++;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			y--;
			delta += 1 - 2 * y;
			continue;
		}
		x++;
		delta += 2 * (x - y);
		y--;
	}
}

// рисуем прямоугольник
void drawRectangle(int x1, int x2, int y1, int y2)
{
	drawLine(x1, x2, y1, y1);
	drawLine(x1, x1, y1, y2);
	drawLine(x2, x2, y1, y2);
	drawLine(x1, x2, y2, y2);
}

float countSplineCoefficient(int index, int x1, int x2, int x3, int x4)
{
	switch (index)
	{
	case 0:
		return (x1 + 4 * x2 + x3) / 6.0f; //свободный член
	case 1:
		return (-x1 + x3) / 2.0f; //коэффициент при t
	case 2:
		return (x1 - 2 * x2 + x3) / 2.0f; //коэффициент при t^2
	case 3:
		return (-x1 + 3 * x2 - 3 * x3 + x4) / 6.0f; //коэффициент при t^3
	}

	return 0;
}

void drawSpline(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	//подсчет коэффициентов сплайна
	float a0 = countSplineCoefficient(0, x1, x2, x3, x4);
	float a1 = countSplineCoefficient(1, x1, x2, x3, x4);
	float a2 = countSplineCoefficient(2, x1, x2, x3, x4);
	float a3 = countSplineCoefficient(3, x1, x2, x3, x4);

	float b0 = countSplineCoefficient(0, y1, y2, y3, y4);
	float b1 = countSplineCoefficient(1, y1, y2, y3, y4);
	float b2 = countSplineCoefficient(2, y1, y2, y3, y4);
	float b3 = countSplineCoefficient(3, y1, y2, y3, y4);

	float xPrev = a0, yPrev = b0;

	for (int i = 1; i <= 10; i++) //разбиваем кривую на 10 отрезков
	{
		float t = i / 10.0f;
		float x = ((a3 * t + a2) * t + a1) * t + a0; //x(t)
		float y = ((b3 * t + b2) * t + b1) * t + b0; //y(t)

		glBegin(GL_LINES); 
			glVertex2f(xPrev, yPrev); 
			glVertex2f(x, y);
		glEnd();//соединяем подсчитанные точки

		xPrev = x;
		yPrev = y;
	}
}

// рисуем треугольник
void drawTriangle(int x1, int x2, int x3, int y1, int y2, int y3)
{
	drawLine(x1, x2, y1, y2);
	drawLine(x3, x1, y3, y1);
	drawLine(x2, x3, y2, y3);
}

void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINES); //сетка
		glColor3d(1, 1, 1);
		glVertex2d(-100, 0);
		glVertex2d(100, 0);
		glVertex2d(0, -100);
		glVertex2d(0, 100);
	glEnd();

	glPushMatrix();
	glTranslatef(dx, dy, 0.0);
	drawLine(10, 40, 10, 20);
	drawCircle(-25, -40, 30);
	drawRectangle(-20, -40, 30, 50);
	drawTriangle(23, 33, 38, -10, -10, -30);
	drawSpline(60, 70, 65, 63, 75, -34, -54, 62);
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
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	// Основной цикл GLUT
	glutMainLoop();

	return 0;
}


