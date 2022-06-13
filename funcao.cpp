#include <gl/glut.h>
#include "funcao.h"
void funcao::plota_funcao() {
	float x, y;
	float dx = (xmax - xmin) / points;
	float dy = (ymax - ymin) / points;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	x = xmin;
	for (int i = 0; i < points; i++) {
		y = ymin;
		for (int j = 0; j < points; j++) {
			glBegin(GL_LINE_LOOP);
			glVertex4f(x, y, f(x, y).i, f(x,y).j);
			glVertex4f(x + dx, y, f(x + dx, y).i, f(x + dx, y).j);
			glVertex4f(x + dx, y + dy, f(x + dx, y + dy).i, f(x + dx, y + dy).j);
			glVertex4f(x, y + dy, f(x, y + dy).i, f(x, y + dy).j);
			glEnd();
			y += dy;
		}
		x += dx;
	}
}
