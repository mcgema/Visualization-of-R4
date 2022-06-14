#include <gl\glut.h>
#include "funcao.h"
#include <math.h>
#include <iostream>


float gamma[6] = { 0,0,0,0,0,0 };
int flag = 0;

float alpha = 40, beta = 60;
float scale = 1.0;
int xb, xm, yb, ym;

funcao f;



void inicia_config()
{
	glClearColor(1, 1, 1, 1);
	/*glLoadIdentity();*/
	gluOrtho2D(0, 800, 800, 0);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glPushMatrix();
	//glRotatef(alpha, 0.0, 0.0, 1.0);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(1, 1, 1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(alpha, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);
	glScalef(scale, scale, scale);*/
}
void redesenha()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw_eixos();
	f.draw_eixos_funcao();
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
	case '1':
		flag = 0;
		break;
	case '2':
		flag = 1;
		break;
	case '3':
		flag = 2;
		break;
	case '4':
		flag = 3;
		break;
	case '5':
		flag = 4;
		break;
	case '6':
		flag = 5;
		break;
	case 'q':
	case 'Q':
		gamma[flag] -= 1;
		inicia_config();
		redesenha();
		break;
	case 'e':
	case 'E':
		gamma[flag] += 1;
		inicia_config();
		redesenha();
		break;
	case "r":
	case 'R':
		for (int i = 0; i < 6; i++) {
			gamma[i] = 0;
		}
		inicia_config();
		redesenha();
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
		}
	case GLUT_UP:
		alpha = alpha + xm - xb;
		beta = beta - ym + yb;
		break;
	}
}
void mov_mouse(int x, int y)
{
	xm = x;
	ym = y;
	alpha = alpha + xm - xb;
	beta = beta - ym + yb;
	inicia_config();
	xb = xm;
	yb = ym;
	redesenha();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D");
	inicia_config();
	glutDisplayFunc(redesenha);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(botao_mouse);
	glutMotionFunc(mov_mouse);

	glutMainLoop();
}
