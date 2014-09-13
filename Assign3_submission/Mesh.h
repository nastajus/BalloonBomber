#ifndef MESH_H
#define MESH_H

#include "Vert.h"
#include "Quad.h"
#include "Blob.h"
#include "Ball.h"
#include "Targ.h"
#include "Bomb.h"
#include "Cam.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <gl/glut.h>
#include "vectors.h"
using namespace std;

const int numQuadsSide = 64;		//optimize better the gluLookAt for: 1,6, it's not centered desirably.
									//optimizations broken now..., just leave at 64
const int numVertsSide = (numQuadsSide + 1) ;//* (numQuadsSide + 1); 
const int dist = 1; 

const double temp = numVertsSide; 
const int almost  = floor(temp/1.1);
const int halfway = floor(temp/2);
const int quarter = floor(temp/4);
const int eigth   = floor(temp/8);
const int full = numVertsSide;



class Mesh
{
private:

public:
	Mesh();
	Vert* nVerts[ numVertsSide ][ numVertsSide ];
	Quad* nQuads[ numQuadsSide ][ numQuadsSide ];
	vector <Blob*> nBlobs;
	Vert* nNorms[ numVertsSide ][ numVertsSide ];
	int _drawMode; //1=faces, 2=lines
	Balloon* nBalloon;
	vector <Target*> nTargets;
	int cameraPosition;
	vector <Bomb*> nBombs;
	Camera* nCamera; 
	
	void PrintVerts();
	void PrintQuads();
	void PrintBlobs();
	void PrintTargets();
	void PrintBombs();
	void RandomlyGenerateBlobs(int);
	void RandomlyGenerateTargets(int);
	void MakeBlob(Blob*);
	void MakeBalloon(Vert*);
	void MakeTarget(Target*);
	void MoveTargets();
	void MakeBomb(Bomb*);
	void MoveBombs();
	void DestroyBomb(int);
	void DestroyTarget(int);
	void MakeCamera(Vert*, Vert*, Vert*);
	void CalculateDistances();
	void CalculateNormals();
	void DetectCollisions();
	void DetectCollisionsBombOnTarget();
	//void ApplyBlobs();

	//void Go();
	void Draw();
	void DrawLines(); //abandoned
	void DrawFaces();
	void DrawMesh();
	void DrawTargets();
	void DrawBombs();

	void SetCamera();	//1=terrain, 2=balloon floor


};

#endif