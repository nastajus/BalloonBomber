#include "Vert.h"
/*
#include <string> 
#include <sstream>
using namespace std;
*/

Vert::Vert(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}
float Vert::getX()
{
	return _x;
}

float Vert::getY()
{
	return _y;
}

float Vert::getZ()
{
	return _z;
}

/*
string Vert::getAll(){
	stringstream ss;
	ss << _x << ":" << _y << ":" << _z;
	return ss.str();
}
*/

void Vert::setX(float x)
{
	_x = x;
}
void Vert::setY(float y)
{
	_y = y;

}
void Vert::setZ(float z)
{
	_z = z;

}


/*
void Vert::setV(float x, float y, float z){
	_x = x;
	_y = y;
	_z = z;
}
*/