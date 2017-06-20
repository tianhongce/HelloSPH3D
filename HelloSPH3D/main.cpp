#include <iostream>
#include <GL\freeglut.h>

using namespace std;

void drawParticles()
{
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glLineWidth(1.0f);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	//glVertex3f(0.2f, 0.2f, 0.2f);
	//glVertex3f(0.3f, 0.3f, 0.3f);
	//glVertex3f(0.4f, 0.4f, 0.4f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	//glVertex3f(0.6f, 0.6f, 0.6f);
	//glVertex3f(0.7f, 0.7f, 0.7f);
	//glVertex3f(0.8f, 0.8f, 0.8f);
	glVertex3f(0.9f, 0.9f, 0.9f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();
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
	//gluPerspective(0,0,0,0);
	glOrtho(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}
void idle()
{
	glutPostRedisplay();
}
void reshape(GLint width, GLint height)
{
	cout << width << " " << height << endl;
	//window_width = width;
	//window_height = height;

	//glViewport(0, 0, width, height);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//gluPerspective(45.0, (float)width / height, 0.001, 100.0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -3.0f);
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		//sph->sys_running = 1 - sph->sys_running;
	}

	if (key == 'w')
	{
		cout << "w" << endl;
		//zTrans += 0.3f;
	}

	if (key == 's')
	{
		//zTrans -= 0.3f;
	}

	if (key == 'a')
	{
		//xTrans -= 0.3f;
	}

	if (key == 'd')
	{
		//xTrans += 0.3f;
	}

	if (key == 'q')
	{
		//yTrans -= 0.3f;
	}

	if (key == 'e')
	{
		//yTrans += 0.3f;
	}

	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		cout << "GLUT_DOWN" << endl;
		cout << x << " " << y << endl;
		//buttonState = 1;
	}
	else if (state == GLUT_UP)
	{
		cout << "GLUT_UP" << endl;
		//buttonState = 0;
	}

	//ox = x; oy = y;

	glutPostRedisplay();
}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100); 
	glutCreateWindow("helloSPH");
	
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;

}