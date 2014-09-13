#ifndef VERT_H
#define VERT_H

class Vert
{
private:
	float _x;
	float _y;
	float _z;

public:
	Vert(float, float, float);

	float getX();
	float getY();
	float getZ();
	//string getAll();

	void setX(float);
	void setY(float);
	void setZ(float);

	//void setV(float, float, float);

};

#endif