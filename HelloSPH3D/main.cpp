#include <iostream>
#include <GL\freeglut.h>

using namespace std;

void drawParticles()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(0.1f, 0.1f);
	//glVertex2f(0.2f, 0.2f);
	//glVertex2f(0.3f, 0.3f);
	//glVertex2f(0.4f, 0.4f);
	//glVertex2f(0.5f, 0.5f);
	//glVertex2f(0.6f, 0.6f);
	//glVertex2f(0.7f, 0.7f);
	//glVertex2f(0.8f, 0.8f);
	//glVertex2f(0.9f, 0.9f);
	//glVertex2f(1.0f, 1.0f);
	glEnd();

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	drawParticles();

	glutSwapBuffers();
	//glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}
void idle()
{
	glutPostRedisplay();
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);  glutIdleFunc(idle);
	glutCreateWindow("helloSPH");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}