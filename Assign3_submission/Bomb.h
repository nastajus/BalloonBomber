#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "Vert.h"
#include <gl/glut.h>



const float bombRate = 0.2;
const float bombRadius = 0.18;


class Bomb{

private:
	static int _numBombs;

public:

	int _num;
	
	Vert* _posi;	//position
	Bomb (Vert*);
	void Draw();
	void MoveDown();

};