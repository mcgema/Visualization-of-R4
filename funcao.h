#define _USE_MATH_DEFINES
#include <cmath> 

struct Quartenion {
	float x;
	float y;
	float z;
	float w;
};

class funcao {
	float rmin, rmax, thetamin, thetamax;
	int points;
public:
	funcao(float rm = 0, float rM = 1, float tm = 0 , float tM = 2* M_PI, int p = 50) {
		rmin = rm;
		thetamin = tm;
		rmax = rM;
		thetamax = tM;
		points = p;
	}
	void plota_funcao(Quartenion f(float, float));
	void draw_eixos_funcao(Quartenion f(float, float));
};
