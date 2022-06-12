#include <gl\glut.h>
#include "funcao.h"
#include <math.h>

float theta = 135;
float phi = 45;
float gamma = 90;
float alpha = 30;
float beta = 60;
float psi = 120;

float scale = 1.0;
int xb, xm, yb, ym;
funcao f;

float Rxw[4][4] = { {cos(alpha), 0, 0, -sin(alpha)},
					{   0,       1, 0,       0    },
					{	0,		 0, 1,		 0	  },
					{sin(alpha), 0, 0,  cos(alpha)} };

float Ryw[4][4] = { {1,   0,	   0,		0   },
					{0, cos(beta), 0, -sin(beta)},
					{0,	  0,	   1,		0   },
					{0, sin(beta), 0,  cos(beta)} };

float Rzw[4][4] = { {1,  0,	   0,		  0    },
					{0,	 1,    0,         0    },
					{0,	 0, cos(psi), -sin(psi)},
					{0,  0, sin(psi),  cos(psi)} };

void plota_eixos()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}
void inicia_config()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(gamma, 0.0, 0.0, 1.0); // Rxy
	glRotatef(theta, 1.0, 0.0, 0.0); //Ryz
	glMultMatrixf(*Rzw); //psi
	glRotatef(alpha, 0.0, 0.0, 1.0); // Rxy
	glRotatef(beta, 1.0, 0.0, 0.0); //Ryz
	glRotatef(phi, 0.0, 0.0, 1.0); // Rxy
	glScalef(scale, scale, scale);
}
void redesenha()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	plota_eixos();
	f.plota_funcao();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'S':
		scale += 0.2;
		inicia_config();
		redesenha();
		break;
	case 's':
		scale -= 0.2;
		inicia_config();
		redesenha();
		break;
	}
}
void botao_mouse(int b, int state, int x, int y)
{
	switch (b) {
	case GLUT_LEFT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			xb = x;
			yb = y;
			break;
		case GLUT_UP:
			theta = theta + xm - xb;
			phi = phi - ym + yb;
			break;
		}
		break;
	}
}
void mov_mouse(int x, int y)
{
	xm = x;
	ym = y;
	theta = theta + xm - xb;
	phi = phi - ym + yb;
	inicia_config();
	xb = xm;
	yb = ym;
	redesenha();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D");
	glutDisplayFunc(redesenha);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(botao_mouse);
			glutMotionFunc(mov_mouse);
	inicia_config();
	glutMainLoop();
}