#include "Blob.h"

int Blob::_numBlobs = 0;

Blob::Blob(Vert* v, float height, float width){
	
	_num = _numBlobs;

	//static
	_numBlobs = _numBlobs + 1;

	//_active = false;

	//normal

	_v = v;
	if (height <= maxHeight && height >= minHeight)
		_height = height;
	else {
		//cout << "Blob " << _num << " height outside bounds as " << height << ", set to default" << endl;
		_height = defaultHeight;
	}
	if (width <= maxWidth && width >= minWidth)
		_width = width;
	else {
		//cout << "Blob " << _num << " width outside bounds as " << height << " set to default" << endl;
		_width = defaultWidth;
	}
}

float Blob::getHeight(){
	return _height;
}

float Blob::getWidth(){
	return _width;	
}

Vert* Blob::getV(){
	return _v;
}

int Blob::getNum(){
	return _num;
}

/*
bool Blob::Active(){
	return _active;
}*/

void Blob::setHeight(float height){
	if (height < maxHeight && height > minHeight){
		_height = height;
		cout << "Blob " << _num << " height is " << _height << endl;
	}
	else {
		cout << "Blob " << _num << " height outside bounds, not applied" << endl;
		//cout << "numBlobs exist now: " << _numBlobs << endl;
		//PrintBlobs();
	}
}

void Blob::setWidth(float width){
	if (width < maxWidth && width > minWidth){
		_width = width;
		cout << "Blob " << _num << " height is " << _width << endl;
	}
	else {
		cout << "Blob " << _num << " width exceeded, not applied" << endl;
		//cout << "numBlobs exist now: " << _numBlobs << endl;
		//PrintBlobs();
	}
}

void Blob::setV(Vert* v){
	_v = v;
}

/*
void Blob::setActive(bool state){
	_active = state;
}*/

/*
void Blob::Move(){
	_v
}
*/

/*
void Blob::WidthMore(){

}

void Blob::WidthLess(){

}

void Blob::HeightMore(){

}

void Blob::HeightLess(){

}
*/