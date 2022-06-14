#include <gl/glut.h>
#include "funcao.h"
#include <iostream>

extern float gamma[6];


float** multiplica_matrizes(float** m1, float(*m2)[4]) {
	// matrices de tamanho 4x4
	float** m3;
	m3 = new float* [4];
	for (int i = 0; i < 4; i++)
		m3[i] = new float[4];

	float sum = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sum = 0;
			for (int k = 0; k < 4; k++)
				sum = sum + (m1[i][k] * m2[k][j]);
			m3[i][j] = sum;
		}
	}
	return m3;

}

float** multiplica_matrizes1(float(*m1)[4], float(*m2)[4]) {
	// matrices de tamanho 4x4
	float** m3;
	m3 = new float* [4];
	for (int i = 0; i < 4; i++)
		m3[i] = new float[4];

	float sum = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sum = 0;
			for (int k = 0; k < 4; k++)
				sum = sum + (m1[i][k] * m2[k][j]);
			m3[i][j] = sum;
		}
	}
	return m3;

}

float** rotaciona() {
	float Rxy_1[4][4] = { {cos(gamma[0]), -sin(gamma[0]), 0, 0},
					{sin(gamma[0]),  cos(gamma[0]), 0, 0},
					{   0,       0, 1,       0    },
					{	0,		 0, 0,		1	  }
	};

	float Ryz_2[4][4] = { {   1,       0, 0,       0    },
						{0, cos(gamma[1]), -sin(gamma[1]), 0},
						{0, sin(gamma[1]),  cos(gamma[1]), 0},
						 {0,0,0,1}
	};

	float Rzw[4][4] = { {1,  0,	   0,		  0    },
						{0,	 1,    0,         0    },
						{0,	 0, cos(gamma[2]), -sin(gamma[2])},
						{0,  0, sin(gamma[2]),  cos(gamma[2])}};

	float Rxy_4[4][4] = { {cos(gamma[3]), -sin(gamma[3]), 0, 0},
						 {sin(gamma[3]),  cos(gamma[3]), 0, 0},
						 {   0,       0, 1,       0    },
						 {	0,		 0, 0,		1	  }
	};


	float Ryz_5[4][4] = { {   1,       0, 0,       0    },
						{0, cos(gamma[4]), -sin(gamma[4]), 0},
						{0, sin(gamma[4]),  cos(gamma[4]), 0},
						 {0,0,0,1}
	};

	float Rxy_6[4][4] = { {cos(gamma[5]), -sin(gamma[5]), 0, 0},
						{sin(gamma[5]),  cos(gamma[5]), 0, 0},
						{   0,       0, 1,       0    },
						{	0,		 0, 0,		1	  }
	};

	float** res1 = multiplica_matrizes1(Rxy_1, Ryz_2);
	float** res2 = multiplica_matrizes(res1, Rzw);
	float** res3 = multiplica_matrizes(res2, Rxy_4);
	float** res4 = multiplica_matrizes(res3, Ryz_5);
	float** res5 = multiplica_matrizes(res4, Rxy_6);
	for (int i = 0; i < 4; i++) {
		delete[] res1[i];
		delete[] res2[i];
		delete[] res3[i];
		delete[] res4[i];
	}
	delete[] res1;
	delete[] res2;
	delete[] res3;
	delete[] res4;
	return res5;
}

float* avalia(Quartenion q, float** m) {
	float* v;
	v = new float[4];
	for (int i = 0; i < 2; i++)
		v[i] = 0;
	for (int i = 0; i < 2; i++)
		v[i] = m[i][0] * q.x + m[i][1] * q.y + m[i][2] * q.z + m[i][3] * q.w;
	return v;
}

void funcao::plota_funcao() {
	float x, y;
	float dx = (xmax - xmin) / points;
	float dy = (ymax - ymin) / points;
	float** rotation = rotaciona();
	float* v;
	glColor3f(1.0f, 1.0f, 1.0f);
	x = xmin;
	for (int i = 0; i < points; i++) {
		y = ymin;
		for (int j = 0; j < points; j++) {
			glBegin(GL_LINE_LOOP);
			v = avalia(f(x, y), rotation);
			glVertex2f(v[0], v[1]);
			v = avalia(f(x + dx, y), rotation);
			glVertex2f(v[0], v[1]);
			v = avalia(f(x + dx, y + dy), rotation);
			glVertex2f(v[0], v[1]);
			v = avalia(f(x, y + dy), rotation);
			glVertex2f(v[0], v[1]);
			glEnd();
			y += dy;
		}
		x += dx;
	}
}

void funcao::draw_eixos_funcao()
{
	float** rotation = rotaciona();
	float* v;
	Quartenion e1 = { 1,0,0,0 };
	Quartenion e2 = { 0,1,0,0 };
	Quartenion e3 = { 0,0,1,0 };
	Quartenion e4 = { 0,0,0,1 };
	//eixo x
	v = avalia(e1, rotation);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(v[0], v[1]);
	glVertex2f(0.0, 0.0);
	glEnd();
	//eixo y
	v = avalia(e2, rotation);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(v[0], v[1]);
	glVertex2f(0.0, 0.0);
	glEnd();
	//eixo z
	v = avalia(e3, rotation);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);

	glVertex2f(v[0], v[1]);
	glVertex2f(0.0, 0.0);
	glEnd();
	//eixo w
	v = avalia(e3, rotation);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(v[0], v[1]);
	glVertex2f(0.0, 0.0);
	glEnd();
}
