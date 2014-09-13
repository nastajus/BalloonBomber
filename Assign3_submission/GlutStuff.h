#ifndef GLUTSTUFF_H
#define GLUTSTUFF_H
#include <gl/glut.h>


GLfloat light_position0[] = {0.0,10.0,10.0,1.0};
GLfloat light_position1[] = {00.0,0.0,0.0,1.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[] = {0.0, 0.0, 0.0, 1.0};
GLfloat model_ambient[]  = {0.4, 0.4, 0.4, 1.0};

GLfloat groundMat_ambient[]    = {0.4, 0.4, 0.4, 1.0};
GLfloat groundMat_specular[]   = {0.01, 0.01, 0.01, 1.0};
GLfloat groundMat_diffuse[]   = {0.4, 0.4, 0.4, 1.0};
GLfloat groundMat_shininess[]  = {0.0};


void mouseMotionHandler(int x, int y);
void screenToCameraCoordinates(int xScreen, int yScreen, GLdouble *xCamera, GLdouble *yCamera);
void cameraToWorldCoordinates(GLdouble xcam, GLdouble ycam, GLdouble *xw, GLdouble *yw);
void screenToWorldCoordinates(int xScreen, int yScreen, GLdouble *xw, GLdouble *yw);

void funcKeyHandler(int key, int x, int y);
void mouseClickHandler(int button, int state, int xMouse, int yMouse);
void keyboardHandler(unsigned char key, int x, int y);
void timerHandler(int);


Vector3 GetOGLPos(int x, int y);

GLint glutWindowWidth = 800;
GLint glutWindowHeight = 800;
GLint viewportWidth = glutWindowWidth;
GLint viewportHeight = glutWindowHeight;

// Boundaries of world view (wv) window - also called the clip window or clip rectangle
// Think of it as a virtual camera. Specify this wih gluOrtho2D()
GLdouble wvLeft = -400.0, 
	wvRight = 400.0,
	wvBottom = -300.0, 
	wvTop =  300.0;

#endif