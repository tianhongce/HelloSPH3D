//#include <GL\freeglut.h>
#include <iostream>
#include <GL/glut.h>
#include "SPH.h"
#include "Particle.h"
#include <vector>

using namespace std;

SPH *sph;

// ��¼���������¼���ȫ�ֱ���
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraDistanceX;
float cameraDistanceY;
float cameraAngleX;
float cameraAngleY;
float times = 1;

void drawParticles()
{

	vector<Particle*> ps = sph->getParticles();

	//cout << "�ܶ�: " << ps[500]->density << endl;
	//cout << "ѹ��: " << ps[500]->pressureForce << endl;
	//cout << "ճ����: " << ps[500]->viscosityForce << endl;
	//cout << "����: " << ps[500]->gravityForce << endl;
	//cout << "����: " << ps[500]->totalForce << endl;
	//cout << "���ٶ�: " << ps[500]->acceleration << endl;
	//cout << "�ٶ�: " << ps[500]->velocity << endl;
	//cout << "λ��500: " << ps[500]->position << endl;
	//cout << "λ��700: " << ps[700]->position << endl;
	//cout << "λ��900: " << ps[900]->position << endl;
	//cout << "λ��300: " << ps[300]->position << endl;
	//cout << "λ��100: " << ps[100]->position << endl;
	//cout << "λ��0: " << ps[1]->position << endl;
	//cout << "λ��1000: " << ps[999]->position << endl;


	glPointSize(10);
	glColor4f(0, 1, 0, 1);
	glBegin(GL_POINTS);
	for (Particle *p : ps)
	{
		//cout << sph->numParticles << endl;
		//cout << " λ�� " << p->position << endl;
		//cout << p->density << endl;
		//cout << p->gravityForce << endl;
		glVertex3f(p->position.x, p->position.y, p->position.z);
	}
	glEnd();

}


void display(void)
{
	glScalef(times, times, times);//����
	//glRotatef(-90, 1, 0, 0);//��ת
	glTranslatef(cameraDistanceX, cameraDistanceY, 0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(4);
	glColor4f(0.7, 0.7, 0.9, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);

	glEnd();

	glColor4d(0.3, 0.3, 0.3, 0.3);
	glBegin(GL_QUADS);//ǰ��
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();
	glBegin(GL_QUADS);//����
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);//��
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);//zuo
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);//xia
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();
	glBegin(GL_QUADS);//��
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	drawParticles();
	sph->simulation();

	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 0.0, 0.0, 1.0, -1.0, 1.0);
	//gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
	int iWinWidth = (GLint)width;
	int iWinHeight = (GLint)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//ͶӰ��ʽ��͸��ͶӰ
	gluPerspective(0, (GLfloat)iWinWidth / (GLfloat)iWinHeight, 0, 100);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}

void mouseCB(int button, int state, int x, int y)
{
	cout << "state" << state << endl;
	cout << "button" << button << endl;

	mouseX = x;
	mouseY = y;
	times = 1;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseLeftDown = false;
		}

	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseRightDown = false;
		}

	}
	/* ��ס����м��������϶�����ͼ������
	else if (button == GLUT_MIDDLE_BUTTON)
	{
	if (state == GLUT_DOWN)
	{
	mouseMiddleDown = true;
	}
	else if (state == GLUT_UP)
	mouseMiddleDown = false;
	}*/

	/*
	* �����ֿ���ͼ������
	*/
	else if (state == GLUT_UP && button == GLUT_WHEEL_UP)
	{
		times = 0.00008f + 1;
		glutPostRedisplay();
	}
	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN)
	{
		times = -0.00008f + 1;
		glutPostRedisplay();
	}
}

void mouseMotionCB(int x, int y)
{
	cameraAngleX = cameraAngleY = cameraDistanceX = cameraDistanceY = 0;
	times = 1;

	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX) * 0.001f;
		cameraAngleX += (y - mouseY) * 0.001f;
		mouseX = x;
		mouseY = y;
	}
	if (mouseRightDown)
	{
		cameraDistanceX = (x - mouseX) * 0.00002f;
		cameraDistanceY = -(y - mouseY) * 0.00002f;
		mouseY = y;
		mouseX = x;
	}/* ��ס����м��������϶�����ͼ������
	 if (mouseMiddleDown)
	 {
	 times = -(y - mouseY) * 0.002f+1;
	 mouseY = y;
	 }*/

	glutPostRedisplay();
}
/* ʵ�ּ������¼�����ͼ������
void specialKey(GLint key, GLint x, GLint y)
{
times = 1;
if (key == GLUT_KEY_UP)
{
times += 0.008f;
}
if (key == GLUT_KEY_DOWN)
{
times -= 0.008f;
}
glutPostRedisplay();
}*/


int main(int argc, char**argv)
{
	sph = new SPH();
	sph->initFluid();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("helloSPH");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;

}




















/**********************************************************************************************************************************************
#include <iostream>
#include <GL\freeglut.h>
//#include <GL\glut.h>
#include "SPH.h"
#include "Particle.h"
#include <vector>

using namespace std;
SPH *sph;


double zoom = -1.0;
double rotX = 0;
double rotY = 0;

int mouseX = 0;
int mouseY = 0;
bool isMouseDown = false;


void drawParticles()
{
	glPushMatrix();
	glTranslatef(0, 0, zoom);
	glRotatef(rotX, 0.0, 1.0, 0.0);
	glRotatef(rotY, 1.0, 0.0, 0.0);

	//vector<Particle*> ps = sph->getParticles();
	
	//cout << "�ܶ�: " << ps[500]->density << endl;
	//cout << "ѹ��: " << ps[500]->pressureForce << endl;
	//cout << "ճ����: " << ps[500]->viscosityForce << endl;
	//cout << "����: " << ps[500]->gravityForce << endl;
	//cout << "���ٶ�: " << ps[500]->acceleration << endl;
	//cout << "�ٶ�: " << ps[500]->velocity << endl;
	//cout << "λ��500: " << ps[500]->position << endl;
	//cout << "λ��700: " << ps[700]->position << endl;
	//cout << "λ��900: " << ps[900]->position << endl;
	//cout << "λ��300: " << ps[300]->position << endl;
	//cout << "λ��100: " << ps[100]->position << endl;
	//cout << "λ��0: " << ps[1]->position << endl;
	//cout << "λ��1000: " << ps[999]->position << endl;


	glBegin(GL_QUADS);
	glColor4d(0.3, 0.3, 0.3, 0.8);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 0.1f);
	//glVertex3f(0.0f, 0.0f, 0.2f);
	//glVertex3f(0.0f, 0.0f, 0.3f);
	//glVertex3f(0.0f, 0.0f, 0.4f);
	//glVertex3f(0.0f, 0.0f, 0.5f);
	//glVertex3f(0.2f, 0.2f, 0.2f);
	//glVertex3f(0.3f, 0.3f, 0.3f);
	//glVertex3f(0.4f, 0.4f, 0.4f);
	//glVertex3f(0.0f, 0.0f, 0.6f);
	//glVertex3f(0.6f, 0.6f, 0.6f);
	//glVertex3f(0.7f, 0.7f, 0.7f);
	//glVertex3f(0.8f, 0.8f, 0.8f);
	//glVertex3f(0.9f, 0.9f, 0.9f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//for (Particle *p : ps)
	{
		//cout << sph->numParticles << endl;
		//cout << " λ�� " << p->position << endl;
		//cout << p->density << endl;
		//cout << p->gravityForce << endl;
		//glVertex3f(p->position.x, p->position.y, p->position.z);
	}

	glEnd();



	glPopMatrix();
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


	//drawParticles();
	//sph->simulation();
	glutSwapBuffers();
	//glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluPerspective(0,0,0,0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 0.0);

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



	int iWinWidth = (GLint)width;
	int iWinHeight = (GLint)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//ͶӰ��ʽ��͸��ͶӰ
	gluPerspective(60, (GLfloat)iWinWidth / (GLfloat)iWinHeight, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
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
		mouseX = x;
		mouseY = y;

		isMouseDown = true;

	
	}
	else if (state == GLUT_UP)
	{
		isMouseDown = false;
	}

	//ox = x; oy = y;

	glutPostRedisplay();
	
}

void MouseMoveEvent(int x, int y)
{
	if (isMouseDown)
	{
		int deltX, deltY;
		// ��������ƶ����룬��תͼ��
		deltX = x - mouseX;
		deltY = y - mouseY;

		// ��ת��  
		rotX += deltX / 2;
		rotY += deltY / 2;
		// ��ת�ǲ�����360�� 
		rotX = fmodf(rotX, 360.0);
		rotY = fmodf(rotY, 360.0);


		//���µ�ǰ���λ�ã�ʹͼ��ʵʱ��ת
		mouseX = x;
		mouseY = y;

		glutPostRedisplay();
	}
}


int main2(int argc, char**argv)
{
	//sph = new SPH();
	//sph->initFluid();

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
	glutMotionFunc(MouseMoveEvent);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;

}

***************************************************************************************************/
