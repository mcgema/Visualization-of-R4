#include<cmath>
struct Imaginary {
	float i;
	float j;
};

class funcao {
	float xmin, xmax, ymin, ymax;
	int points;
public:
	funcao(float xm = -1, float xM = 1, float ym = -1, float yM =
		1, int p = 100) {
		xmin = xm;
		ymin = ym;
		xmax = xM;
		ymax = yM;
		points = p;
	}

	Imaginary f(float x, float y) {
		float r, theta;
		theta = atan(y / x);
		r = x * x + y * y;
		return { r * r * (cos(theta) * cos(theta) - sin(theta) * sin(theta)), 
				2 * r * r * cos(theta) * sin(theta) };
	}

	void plota_funcao();
};
