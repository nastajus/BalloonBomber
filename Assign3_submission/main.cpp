/**

	Accomplished:
		- Changed camera perspective succesfully


	Next: 
		- make stuff move
		- make stuff collide
		- learn how to do and apply a texture somewhere.

 */


#include "Vert.h"
#include "Quad.h"
#include "Mesh.h"
#include "GlutStuff.h"
#include <gl/glut.h>
#include <iostream>
#include <iomanip>

using namespace std;



Mesh* m;



//these are to change color as loops, but display fn() doesn't increment
double iterationRate = 1/(numQuadsSide*numQuadsSide);
double iterationPosition = 0;

float timerTime = 30;


void init(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.0, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);		//NOT SURE WHAT DOES, but *CANNOT* see without it.
	glEnable(GL_LIGHT0);		//NOT SURE WHAT DOES, but *SUPER DARK* without it.
	glEnable(GL_LIGHT1);		//meh, inconsiquential.

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);		//meh, inconsiquential.

	// Draw the ground
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, groundMat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, groundMat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, groundMat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, groundMat_shininess);
	
}



//*never* call directly, triggered via glutPostRedisplay() instead
void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity();
	//glLoadIdentity();

	


	m->SetCamera();

		

	//ba->Draw();
	//m->nBalloon->Draw();

	m->Draw();

	


	glutSwapBuffers();

}




int main(int argc, char** argv)
{

	m = new Mesh();
	
	

	m->PrintVerts();
	m->PrintQuads();
	//m->PrintBlobs();
	//m->nBlobs.push_back( new Blob( new Vert(0,0,0), 10, 10) );

	

	m->RandomlyGenerateBlobs(250);
	m->RandomlyGenerateTargets(40);

	//m->PrintTargets();
	
	//start
	m->MakeBalloon( new Vert(quarter, numQuadsSide/2, quarter) );

	//test target
	//m->MakeTarget( new Target( new Vert (quarter, numQuadsSide/2 - 12, quarter) ) );




	m->CalculateDistances();
	m->CalculateNormals();

	m->MakeCamera(

		new Vert (
			m->nBalloon->_posi->getX(), 
			m->nBalloon->_posi->getY() - m->nBalloon->_bombDepth + 1, 
			m->nBalloon->_posi->getZ()
		),

		new Vert ( 
			m->nBalloon->_posi->getX(),
			0,
			m->nBalloon->_posi->getZ()
		),

		new Vert ( 1, 0, 0 )

	);

			//hemisphere look around
			


	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(glutWindowWidth, glutWindowHeight);
	glutInitWindowPosition(700, 100);
	glutCreateWindow(argv[0]);
	init(500,500);
	glutDisplayFunc(display); 
	//glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardHandler);
	//glutSpecialFunc(arrowKeys);
	//glutMouseFunc(mouseClickHandler);
	glutSpecialFunc(funcKeyHandler);
	//glutMotionFunc(mouseMotionHandler);
	glutTimerFunc(timerTime, timerHandler, 0);

	glutMainLoop();
	return 0;



	system("pause");
}

GLdouble downScreenX, downScreenY, upScreenX, upScreenY;
GLdouble downMidScreenX, downMidScreenY;//, upMidScreenX, upMidScreenY;
GLdouble xWorld, yWorld;


////////////////////////////////////////////////////////////////////////////////////////
//
//   Convert screen coordinates to world coordinates 
//
///////////////////////////////////////////////////////////////////////////////////////
void screenToWorldCoordinates(int xScreen, int yScreen, GLdouble *xw, GLdouble *yw)
{
	GLdouble xView, yView;

	screenToCameraCoordinates(xScreen, yScreen, &xView, &yView);
	cameraToWorldCoordinates(xView, yView, xw, yw);
}
////////////////////////////////////////////////////////////////////////////////////////
//
//   Convert screen coordinates to view coordinates (also known as camera
//   or eye coordinates). Note we must invert the screen y coordinates since the screen
//   (i.e. the viewport) has its origin in the upper left corner.
//
///////////////////////////////////////////////////////////////////////////////////////
void screenToCameraCoordinates(int xScreen, int yScreen, GLdouble *xCamera, GLdouble *yCamera)
{
	*xCamera = ((wvRight-wvLeft)/glutWindowWidth)  * xScreen; 
	*yCamera = ((wvTop-wvBottom)/glutWindowHeight) * (glutWindowHeight-yScreen); 
}
////////////////////////////////////////////////////////////////////////////////////////
//
//   Convert camera coordinates to world coordinates.  
//
///////////////////////////////////////////////////////////////////////////////////////
void cameraToWorldCoordinates(GLdouble xcam, GLdouble ycam, GLdouble *xw, GLdouble *yw)
{
	*xw = xcam + wvLeft;
	*yw = ycam + wvBottom;
}

void funcKeyHandler(int key, int x, int y){

	switch (key) {

		case GLUT_KEY_UP:
			m->nBalloon->_posi->setX( m->nBalloon->_posi->getX() + m->nBalloon->_balloonRate );
			break;

		case GLUT_KEY_DOWN:
			m->nBalloon->_posi->setX( m->nBalloon->_posi->getX() - m->nBalloon->_balloonRate );
			break;

		case GLUT_KEY_LEFT:
			m->nBalloon->_posi->setZ( m->nBalloon->_posi->getZ() - m->nBalloon->_balloonRate );
			break;

		case GLUT_KEY_RIGHT:
			m->nBalloon->_posi->setZ( m->nBalloon->_posi->getZ() + m->nBalloon->_balloonRate );
			break;

		}

		// seems to be resetting back, unless i spam it. grr.
		//cout << "X:Z" << m->nBalloon->_posi->getX() << ":" << m->nBalloon->_posi->getZ() << endl;

		//m->Draw();
		glutPostRedisplay();


	switch (key) {

	//moves all the blobs
	case GLUT_KEY_F1:	
		//cout <<"blob height up" << endl;
		for (int b=0; b<m->nBlobs.size(); b++){
			m->nBlobs.at(b)->setHeight( m->nBlobs.at(b)->getHeight() + blobHeightChange ); 
			cout << "+height: " << setprecision(3) << m->nBlobs.at(b)->getHeight() << endl; 
		}
		//m->Draw();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F2:
		//cout <<"blob height down" << endl;
		for (int b=0; b<m->nBlobs.size(); b++){
			m->nBlobs.at(b)->setHeight( m->nBlobs.at(b)->getHeight() - blobHeightChange ); 
			cout << "-height: " << setprecision(3) <<  m->nBlobs.at(b)->getHeight() << endl; 
		}
		//m->Draw();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F3:
		//cout <<"blob width bigger" << endl;
		for (int b=0; b<m->nBlobs.size(); b++){
			m->nBlobs.at(b)->setWidth( m->nBlobs.at(b)->getWidth() - blobWidthChange ); 
			cout << "+width: " << setprecision(3) <<  m->nBlobs.at(b)->getWidth() << endl; 
		}
		//m->Draw();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F4:
		//cout <<"blob width smaller" << endl;
		for (int b=0; b<m->nBlobs.size(); b++){
			m->nBlobs.at(b)->setWidth( m->nBlobs.at(b)->getWidth() + blobWidthChange  ); 
			cout << "-width: " << setprecision(3) << m->nBlobs.at(b)->getWidth() << endl;
		}
		//m->Draw();
		glutPostRedisplay();
		break;


	case GLUT_KEY_F5:
		m->_drawMode = 1;
		//m->Draw();
		cout << "Faces" << endl;
		break;

	//didn't implement a lined version for cubes, spheres, or the balloon.
	case GLUT_KEY_F6:
		m->_drawMode = 2;
		//m->Draw();
		cout << "Lines" << endl;
		break;
	

	/*
	case GLUT_KEY_F7:
		m->nQuads[0][0]->getVert(0)->setY( m->nQuads[0][0]->getVert(0)->getY() + dist );
		//m->Draw();
		glutPostRedisplay();
		cout<<"faces up"<<endl;
		break;
		

	case GLUT_KEY_F8:
		m->nQuads[0][0]->getVert(0)->setY( m->nQuads[0][0]->getVert(0)->getY() - dist );
		//m->Draw();
		glutPostRedisplay();
		cout<<"faces down"<<endl;
		break;

	case GLUT_KEY_F9:	
		m->nQuads[0][0]->getVert(0)->setY( m->nQuads[0][0]->getVert(0)->getY() + dist );
		//m->Draw();
		glutPostRedisplay();
		cout<<"lines up"<<endl;
		break;

	case GLUT_KEY_F10:
		m->nQuads[0][0]->getVert(0)->setY( m->nQuads[0][0]->getVert(0)->getY() - dist );
		//m->Draw();
		glutPostRedisplay();
		cout<<"lines down"<<endl;
		break;
	*/

	case GLUT_KEY_F9:
		m->cameraPosition = 1;
		cout <<"mode 1: terrain view set." << endl;
		break;

	case GLUT_KEY_F10:
		m->cameraPosition = 2;
		cout <<"mode 2: bomb hanger view set." << endl;
		break;

	case GLUT_KEY_F11:
		m->cameraPosition = 3;
		cout <<"mode 3: hemisphere changing mode." << endl;
		break;

	case GLUT_KEY_F12:
		m->cameraPosition = 4;
		cout <<"mode 4: balloon close up view set." << endl;
		break;

		
	}


}


void keyboardHandler(unsigned char key, int a, int b)
{

	switch (key) {
	
	case ' ':
		//m->MakeBomb( new Bomb( new Vert(1,1,1) ));

		//!!! 
		//not sure why not showing first bomb... seems to only show subsequent rapid fire bombs...
		m->MakeBomb( new Bomb( new Vert(m->nBalloon->_posi->getX(), m->nBalloon->_posi->getY() - m->nBalloon->_bombDepth,  m->nBalloon->_posi->getZ()) ));
		m->Draw();
		glutPostRedisplay();

		cout << "Bombs away!!" << endl;
		//int b = m->nBombs.size() - 1;
		//cout << "Bomb: " << b << " X:Z " << m->nBombs.at( b )->_posi->getX() << ":" <<m->nBombs.at( b )->_posi->getZ()  << endl;
		break;


	case 'w':
		m->nCamera->ChangeDirection(1);
		break;

	case 's':
		m->nCamera->ChangeDirection(2);
		break;

	case 'a':
		m->nCamera->ChangeDirection(3);
		break;

	case 'd':
		m->nCamera->ChangeDirection(4);
		break;

	}

}


void timerHandler(int){

	//check the state of some logic
	//choose to conditionally update the objects
	//redraw

	//std::cout << "Stuff\n";

	
	m->MoveBombs();
	m->DetectCollisions();
	m->MoveTargets();
	

	
	glutPostRedisplay();
	glutTimerFunc(timerTime , timerHandler, 0);
}

Vector3 GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
 
    return Vector3(posX, posY, posZ);
}