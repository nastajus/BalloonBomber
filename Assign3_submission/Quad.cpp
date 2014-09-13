#include "Quad.h"

Quad::Quad(Vert* v0, Vert* v1, Vert* v2, Vert* v3)
{
	_v0 = v0;
	_v1 = v1;
	_v2 = v2;
	_v3 = v3;

}
Vert* Quad::getVert(int index)
{
	switch(index)
	{
	case 0:
		return _v0;
		break;

	case 1:
		return _v1;
		break;

	case 2:
		return _v2;
		break;

	case 3:
		return _v3;
		break;
	}
}