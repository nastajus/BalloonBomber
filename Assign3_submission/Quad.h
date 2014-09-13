#ifndef QUAD_H
#define QUAD_H

#include "Vert.h"

class Quad
{
private:
	Vert* _v0;
	Vert* _v1;
	Vert* _v2;
	Vert* _v3;

public:
	Quad(Vert*, Vert*, Vert*, Vert*);

	Vert* getVert(int);

};

#endif