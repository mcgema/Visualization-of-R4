#include<cmath>

class funcao {
	float xmin, xmax, ymin, ymax;
	int points;
public:
	funcao(float xm = -1, float xM = 1, float ym = -1, float yM =
		1, int p = 10) {
		xmin = xm;
		ymin = ym;
		xmax = xM;
		ymax = yM;
		points = p;
	}

	float f(float r, float theta) {
		float v[2];
		v[0] = r * r * (cos(theta) * cos(theta) - sin(theta) * sin(theta));
		v[1] = 2 * r * r * cos(theta) * sin(theta);
		return v[2];
	}

	void plota_funcao();
};