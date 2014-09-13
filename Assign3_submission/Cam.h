#pragma once
#include "Vert.h"
#include <math.h>
#include <iostream>
using namespace std;

#include <gl/glut.h>


const int _degrees = 1/72 * 2 * 3.1419;		//equivalent to 5 degrees

class Camera{

private:

public:

	Vert* _eye;
	Vert* _look;
	Vert* _up;

	float _radius;
	float _theta;		//    == up/down	== polar angle / inclination angle	
	float _phi;			// == left/right	== azimuthal angle

		 
	Camera (Vert*, Vert*, Vert*);

	void ChangeDirection (int);

};