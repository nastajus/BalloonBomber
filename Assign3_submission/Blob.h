#include "Vert.h"

#include <iostream>
using namespace std;

const float maxHeight = 12;
const float minHeight = -maxHeight;
const float maxWidth = 0.45;
const float minWidth = 0.05; 

const float blobHeightChange = 0.5 ;
const float blobWidthChange = 0.05 ;

const float defaultHeight = 2.5;
const float defaultWidth = (maxWidth + minWidth) / 2;

const float blobMove = 1;



class Blob{

private:
	static int _numBlobs;
	//bool _active;


public:

	Vert* _v;

	float _height;	//b
	float _width;	//a
	int _num;


	Blob(Vert*,float,float);

	float getHeight();
	float getWidth();
	Vert* getV();
	int getNum();
	//bool Active();

	void setHeight(float);
	void setWidth(float);
	void setV(Vert*);
	//void setActive(bool);

};