//class Target
#include "Targ.h"

float Target::targetRadius = 1.5;

/*
//turned out too complex with headers to <stdlib.h> conflicting in a redefinition. abandoned.
Target::Target(){
	_posi = new Vert(rand()%64, rand()%64, rand()%64);
	_axis = rand()%3;
}
*/

//file: Target.h
Target::Target(Vert* position){

	_posi = position;
	_origin = new Vert( _posi->getX(), _posi->getY(), _posi->getZ() );

	_range = rand()%10;
	_axis = rand()%4;		//some don't move
	
	//for some reason, C++ needs me to separate division onto a separate line.
	float temp = rand()%10;
	_rate = temp/10;

	int temp2 = rand()%2;
	if (temp2==1) _increasing = true; else _increasing=false;

}


void Target::Draw(){

	glPushMatrix();
		glTranslatef(_posi->getX(), _posi->getY(), _posi->getZ());
		glutSolidCube(targetRadius*2);
	glPopMatrix();


}

//void Target::GenerateStats(){
//}

void Target::Move(){

	if ( _axis == 0 ) {
		
		if ( _increasing == true )  {
			if ( _posi->getX() < _origin->getX() + _range ) _posi->setX( _posi->getX() + _rate );
			else _increasing = false; }
		else {
			if ( _posi->getX() > _origin->getX() - _range ) _posi->setX( _posi->getX() - _rate ); 
			else _increasing = true; }
	}

	else if ( _axis == 1 ) {

		if ( _increasing == true )  {
			if ( _posi->getY() < _origin->getY() + _range ) _posi->setY( _posi->getY() + _rate );
			else _increasing = false; }
		else {
			if ( _posi->getY() > _origin->getY() - _range ) _posi->setY( _posi->getY() - _rate ); 
			else _increasing = true; }
	}

	else if ( _axis == 2 ) {
		
		if ( _increasing == true )  {
			if ( _posi->getZ() < _origin->getZ() + _range ) _posi->setZ( _posi->getZ() + _rate );
			else _increasing = false; }
		else {
			if ( _posi->getZ() > _origin->getZ() - _range ) _posi->setZ( _posi->getZ() - _rate ); 
			else _increasing = true; }
	}

}