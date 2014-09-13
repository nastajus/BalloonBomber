//class: Target
#pragma once
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Vert.h"
#include <gl/glut.h>

//file: Target.h
class Target{

public:

	static float targetRadius;

	Vert* _posi;	//position as moving around
	Vert* _origin;	//position moves around
	float _range;	//how far will travel from origin
	float _rate;	//this target's rate.
	int _axis;		//direction	1=x, 2=y, 3=z
	bool _increasing;//positive or negative direction

	Target (Vert*);

	void Move();
	void Draw();

};