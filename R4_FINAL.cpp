#include <gl\glut.h>
#include "funcao.h"
#include <math.h>
#include <iostream>
using namespace std;

float gamma[6] = { 0,0,0,0,0,0 };
int flag = 0;
float scale = 1.0;
int xb, xm, yb, ym;

funcao f;

//lista de funcoes para serem plotadas
Quartenion f1(float r, float theta) {
	Quartenion q;
	q.x = r * cos(theta);
	q.y = r * sin(theta);
	q.z = r * r * cos(2 * theta);
	q.w = r * r * sin(2 * theta);
	return q;
}

Quartenion f2(float r, float theta) {
	return { r * cos(theta), r * sin(theta), r * cos(theta), 0 };
}

Quartenion f3(float r, float theta) {
	int n = 5;
	float p = log(n) * sin(theta);
	return { r * cos(theta), r * sin(theta), r * cos(p), r * sin(p) };
}

void inicia_config()
{
	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	gluOrtho2D(1, 1, 1, 1);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(scale, scale, scale);
}


void redesenha()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	f.draw_eixos_funcao(f1); // parametro é funcao a ser plotada
	f.plota_funcao(f1);
	glFlush();
	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		scale += 0.2;
		inicia_config();
		redesenha();
		break;
	case 'w':
	case 'W':
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
	case 'a':
	case 'A':
		gamma[flag] -= 1;
		inicia_config();
		redesenha();
		break;
	case 's':
	case 'S':
		gamma[flag] += 1;
		inicia_config();
		redesenha();
		break;
	case 'd':
	case 'D':
		for (int i = 0; i < 6; i++) {
			gamma[i] = 0;
		}
		inicia_config();
		redesenha();
		break;
	}
}


int main(int argc, char** argv)
{
	cout << "Guia para manusear o teclado:" << endl;
	cout << "Os numeros 1, 2, 3, 4, 5, 6 em cojunto com a/A e s/S alteram o valor dos 6 angulos de euler" << endl;
	cout << "a/A diminui o angulo em 1 grau e s/S aumenta o angulo em 1 grau " << endl;
	cout << "d/D zera todos os angulos e devera ver o dominio da funcao" << endl;
	cout << "q/Q aumenta o zoom no desenho e w/W diminui o zoom" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D");
	inicia_config();
	glutDisplayFunc(redesenha);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
