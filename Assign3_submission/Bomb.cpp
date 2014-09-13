#include "Bomb.h"

int Bomb::_numBombs = 0;

Bomb::Bomb(Vert* position){


	//for some reason, C++ needs me to separate division onto a separate line.
	float randomXstepA = rand()%10;
	float randomXstepB = (randomXstepA / 10) - 0.5;

	float randomZstepA = rand()%10;
	float randomZstepB = (randomZstepA / 10) - 0.5;

	position->setX( position->getX() + randomXstepB );
	position->setZ( position->getZ() + randomZstepB );


	//finally assign it
	_posi = position;
	
	_num = _numBombs;

	//static
	_numBombs = _numBombs + 1;

}



//file: Target.h
void Bomb::Draw(){

	glPushMatrix();	
		glTranslatef( _posi->getX(), _posi->getY(), _posi->getZ() );
		glutSolidSphere(bombRadius, 30, 30);
	glPopMatrix();


}


void Bomb::MoveDown(){

	_posi->setY ( _posi->getY() - bombRate );

}