#include "Cam.h"

Camera::Camera(Vert* eye, Vert* look, Vert* up){

	_eye = eye;
	_look = look;
	_up = up;

	_radius = 1;
	_theta = 0;
	_phi = 0;

}


//contains OpenGL
void Camera::ChangeDirection(int direction){

	//calculation based off reference here: 
	//http://en.wikipedia.org/wiki/Spherical_coordinate_system#Coordinate_system_conversions
	//note that z and y are flipped here from wiki
	//x = r • sin (theta) • cos (phi)
	//y = r • cos (theta)
	//z = r • sin (theta) • sin (phi)
	

	// (theta) == polar angle / inclination angle	== up/down
	// (phi)   == azimuthal angle					== left/right




	

	//direction:  1=up, 2=down, 3=left, 4=right
	if ( direction == 1 ) {
		if ( _theta < 90 )  _theta += 5; 
	}
	else if ( direction == 2 ) {
		if ( _theta > -90 )  _theta -= 5; 

	}


	//direction:  1=up, 2=down, 3=left, 4=right
	if ( direction == 3 ) {
		if ( _phi < 90 )  _phi += 5; 
	}
	else if ( direction == 4 ) {
		if ( _phi > -90 )  _phi -= 5; 

	}

	float x,y,z;

	x = _radius * sin ( _theta ) * cos ( _phi );
	y = _radius * cos ( _theta );
	z = _radius * sin ( _theta ) * sin ( _phi );

	cout << "Z:theta " << z << ":" << _theta << endl;

	//gluLookAt( _eye->getX(), _eye->getY(), _eye->getZ(), x, y, z, _up->getX(), _up->getY(), _up->getZ());
	//gluLookAt( x, y, z, _look->getX(), _look->getY(), _look->getZ(), _up->getX(), _up->getY(), _up->getZ() );
	gluLookAt( x, y, z, 0,0,0,0,1,0);
	glutPostRedisplay();

}