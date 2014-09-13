//class: Balloon
#include "Vert.h"
#include <gl/glut.h>

//const int objectRate = 1;

//file: Ball.h
class Balloon{

public:

	//this variable is not really OO, since it's strictly relative to the many variables contained in this class' Draw method,
	//however it is the simplest way to make it externally accessible to the bomb's starting position, so it's here now.
	static float _bombDepth;
	static float _balloonRate;


	Vert* _posi;	//position
	//int rate;
	Balloon (Vert*);

	void Draw();

};