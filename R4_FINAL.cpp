#include <gl\glut.h>
#include "funcao.h"
#include <math.h>
#include <iostream>


extern float gamma1, gamma2, gamma3, gamma4, gamma5, gamma6;
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
	glPushMatrix();
	glRotatef(alpha, 0.0, 0.0, 1.0);

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
		extern float gamma1;
		gamma1 -= 10;
		inicia_config();
		redesenha();
		break;
	case '2':
		gamma2 -= 10;
		inicia_config();
		redesenha();
		break;
	case '7':
		gamma3 -= 10;
		inicia_config();
		redesenha();
		break;
	case '4':
		gamma4 -= 10;
		inicia_config();
		redesenha();
		break;
	case '5':
		gamma5 -= 10;
		inicia_config();
		redesenha();
		break;
	case '6':
		gamma6 -= 10;
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
