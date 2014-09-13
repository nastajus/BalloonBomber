//class Balloon
#include "Ball.h"

float Balloon::_bombDepth = 3 + 2 + 3;//== balloonRadius + basketSize + basketDistance
float Balloon::_balloonRate = 0.5;

Balloon::Balloon(Vert* positionVert){
	_posi = positionVert;
	
}


//file: Ball.h
void Balloon::Draw(){

	float balloonRadius = 3;
	float basketSize = 2;
	float basketRadius = basketSize /2;
	float basketThickness = 0.5;
	float basketDistance = 3;
	float ropeLength = 6;
	float ropeRadius = 0.25;

	//balloon
	glPushMatrix();
		glTranslatef(_posi->getX(), _posi->getY(), _posi->getZ());
		glutSolidSphere(balloonRadius, 50, 50);
	glPopMatrix();

	//

	//basket side 1
	glPushMatrix();
		glTranslatef(_posi->getX() + basketRadius, _posi->getY() - balloonRadius - basketDistance  - basketSize/2 , _posi->getZ());
		glRotatef(-15, 0,0,1);
		glScalef(basketThickness, basketSize, basketSize);
		glutSolidCube(1);
	glPopMatrix();

	//basket side 2
	glPushMatrix();
		glTranslatef(_posi->getX() - basketRadius, _posi->getY() - balloonRadius - basketDistance  - basketSize/2 , _posi->getZ());
		glRotatef(-15, 0,0,-1);
		glScalef(basketThickness, basketSize, basketSize);
		glutSolidCube(1);
	glPopMatrix();


	//basket side 3
	glPushMatrix();
		glTranslatef(_posi->getX(), _posi->getY() - balloonRadius - basketDistance  - basketSize/2 , _posi->getZ() + basketRadius);
		glRotatef(-15, -1,0,0);
		glScalef(basketSize, basketSize, basketThickness);
		glutSolidCube(1);
	glPopMatrix();

	//basket side 4
	glPushMatrix();
		glTranslatef(_posi->getX(), _posi->getY() - balloonRadius - basketDistance  - basketSize/2 , _posi->getZ() - basketRadius);
		glRotatef(-15, 1,0,0);
		glScalef(basketSize, basketSize, basketThickness);
		glutSolidCube(1);
	glPopMatrix();

	
	GLUquadricObj *quadratic;

	//rope 1
	glPushMatrix();
		glTranslatef(_posi->getX() - basketRadius, _posi->getY() , _posi->getZ() + basketRadius);
		glRotatef(90, 1,0,0);
		quadratic = gluNewQuadric();
		gluCylinder(quadratic, ropeRadius, ropeRadius, ropeLength, 32, 32);
	glPopMatrix();
	

	//rope 2
	glPushMatrix();
		glTranslatef(_posi->getX() + basketRadius, _posi->getY() , _posi->getZ() + basketRadius);
		glRotatef(90, 1,0,0);
		quadratic = gluNewQuadric();
		gluCylinder(quadratic, ropeRadius, ropeRadius, ropeLength, 32, 32);
	glPopMatrix();


	//rope 3
	glPushMatrix();
		glTranslatef(_posi->getX() + basketRadius, _posi->getY() , _posi->getZ() - basketRadius);
		glRotatef(90, 1,0,0);
		quadratic = gluNewQuadric();
		gluCylinder(quadratic, ropeRadius, ropeRadius, ropeLength, 32, 32);
	glPopMatrix();


	//rope 4
	glPushMatrix();
		glTranslatef(_posi->getX() - basketRadius, _posi->getY() , _posi->getZ() - basketRadius);
		glRotatef(90, 1,0,0);
		quadratic = gluNewQuadric();
		gluCylinder(quadratic, ropeRadius, ropeRadius, ropeLength, 32, 32);
	glPopMatrix();
	


	/*
	glPushMatrix(); 
		glTranslatef(0.0,0.0,0.0);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(0.0,3.0,3.0);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(3.0,0.0,0.0);
		glutSolidCube(1);
	glPopMatrix();
	*/

}