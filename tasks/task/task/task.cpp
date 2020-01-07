#include <freeglut.h>
#include <iostream>

float x = 1.5;
// флаг для движения туда-сюда
bool flag = true;

void changeSize(int w, int h) {
	// предупредим деление на ноль
	// если окно сильно перетянуто будет
	if (h == 0)
		h = 1;
	float ratio = 1.0 * w / h;

	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, w, h);

	glOrtho(-5.0, 5.0, -5.0, 5.0, 0.0, 10.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	// установить корректную перспективу.
	gluPerspective(45, ratio, 0.1, 100);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.3, 0.5, 0.4);
	glBegin(GL_TRIANGLES);
		glVertex3f(x + 1.0, 2.5, -3.0);
		glVertex3f(x + 0.5, 3.5, -3.0);
		glVertex3f(x, 2.5, -3.0);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	//glRotatef(-45, 0.0, 0.0, 1.0);
	glColor3f(0.4, 0.55, 0.2);
	glBegin(GL_TRIANGLES);
		glVertex3f(x + 1.0, 2.5, -3.0);
		glVertex3f(x + 0.5, 3.5, -3.0);
		glVertex3f(x, 2.5, -3.0);
	glEnd();
	glPopMatrix();

	if (flag == true)
	{
		x += 0.1;
		if(x >= 3)
			flag = false;
	}
	else
	{
		x -= 0.1;
		if (x <= 1.5)
			flag = true;
	}
	
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("task");

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	// Основной цикл GLUT
	glutMainLoop();

	return 0;
}


