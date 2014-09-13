#include "Mesh.h"


Mesh::Mesh()
{

	//Setup Vertices

	//create
	
	for (int z=0; z<numVertsSide; z++){
		for (int x=0; x<numVertsSide; x++){
			nVerts[x][z] = new Vert(x*dist, 0.0f, z*dist);
		}
	}


	//Setup Quads

	//create
	
	for (int z=0; z<numQuadsSide; z++){
		for (int x=0; x<numQuadsSide; x++){
			nQuads[x][z] = new Quad(
				nVerts[x][z],
				nVerts[x][z+1],
				nVerts[x+1][z+1],
				nVerts[x+1][z]
			);
		}
	}


	_drawMode = 1;
	cameraPosition = 1;


}


void Mesh::PrintVerts()
{
	if (numQuadsSide<4) {
		//show
		cout << "vertices" << endl << endl;
		for (int z=0; z<numVertsSide; z++){
			for (int x=0; x<numVertsSide; x++){
				cout << nVerts[x][z]->getX() << ":" << nVerts[x][z]->getY() << ":" << nVerts[x][z]->getZ() << "   ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}

}

void Mesh::PrintQuads()
{

	if (numQuadsSide<4) {
		//show
		cout << "quads" << endl << endl;
		for (int y=0; y<numQuadsSide; y++){
			for (int x=0; x<numQuadsSide; x++){
				for (int i=0; i<=3; i++){
					cout << nQuads[x][y]->getVert(i)->getX() << ":" << nQuads[x][y]->getVert(i)->getY()  << ":" << nQuads[x][y]->getVert(i)->getZ() << "   ";
				}
				cout << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	//else
	//	cout << "too many quads, not printing" << endl;

}


//shows array of Blobs

/*

B..B..B
......B
B......
.......

*/
void Mesh::PrintBlobs(){
	cout << "amt Blobs: " << nBlobs.size() << endl;
	for (int i=0; i<nBlobs.size(); i++){
		//cout << nBlobs.at(i)->getV() << "   " << nBlobs.at(i)->getHeight() << "   " << nBlobs.at(i)->getWidth()  << endl;
		cout << "i: " << i << "   " << nBlobs.at(i)->getV()->getX() << endl;
		//cout << "i:" << i << endl;	
	}


	cout<< "amt Quads on a Side: " << numQuadsSide << endl;
	cout<< "amt Quads          : " << numQuadsSide*numQuadsSide  << endl;

	//cout << setw(2) << x;

	for (int x=0; x<numVertsSide; x++){
		for (int z=0; z<numVertsSide; z++){
			bool found = false;
			for (int b=0; b<nBlobs.size(); b++){

				if (nBlobs.at(b)->getV()->getX()==x && nBlobs.at(b)->getV()->getZ()==z){
					found = true;
					cout << "B";
				}

			}
			if (found == false) cout << ".";
		}
		cout << endl;
	}
}

void Mesh::PrintTargets(){

	cout<< "Targets:" <<endl;

	//if ( nTargets.empty() == false) {
	
		for ( int t=0; t<nTargets.size(); t++ ) {
			
			cout << "X:Y:Z " << nTargets.at(t)->_posi->getX()  << nTargets.at(t)->_posi->getY()  << nTargets.at(t)->_posi->getZ() << endl;
					
		}

	//}
	//else {
	//	cout << "No targets." << endl;
	//}
}

void Mesh::PrintBombs(){

	cout<< "Bombs:" <<endl;

	//if ( nBombs.empty() == false) {
	
		for ( int t=0; t<nBombs.size()-1; t++ ) {
			
			cout << "X:Y:Z " << nBombs.at(t)->_posi->getX()  << nBombs.at(t)->_posi->getY()  << nBombs.at(t)->_posi->getZ() << endl;
					
		}

	//}
	//else {
	//	cout << "No targets." << endl;
	//}
}


//randomly generate some blobs within the boundaries
//please note: The boundary logic isn't perfect, so I just let the blob construcutor push it to within boundaries
void Mesh::RandomlyGenerateBlobs(int amt){

	double rangeWidth = maxWidth+abs(minWidth);
	int tempRangeWidth = floor ( rangeWidth*100 );
	double tempW;
	
	double rangeHeight = maxHeight+abs(minHeight);
	int tempRangeHeight = floor ( rangeHeight*100 );
	double tempH;

	for (int a=0; a<amt; a++){

		tempH = rand()%tempRangeHeight;
		tempW = rand()%tempRangeWidth;
		nBlobs.push_back( new Blob( nVerts[rand()%numQuadsSide][rand()%numQuadsSide], tempH - rangeHeight/2, tempW )  );
	}	

}


void Mesh::RandomlyGenerateTargets(int amt){

	for (int a=0; a<amt; a++){
		nTargets.push_back( new Target ( new Vert(rand()%64, rand()%5, rand()%64) ) );
	}

}

void Mesh::MakeBlob(Blob* b){

	nBlobs.push_back( b );
	
}

void Mesh::MakeBalloon(Vert* v){

	nBalloon = new Balloon( v );

}


void Mesh::MakeTarget(Target* t){
	
	nTargets.push_back( t );

}


void Mesh::MakeBomb(Bomb* b){

	nBombs.push_back( b );
	
}

void Mesh::MoveBombs(){

	if ( nBombs.empty() == false ){ 

		for (int a=0; a<nBombs.size(); a++){
			nBombs.at( a )->MoveDown();
		}

	}
	//else 
	//	cout << "BOMB SIZE IS: " << nBombs.size() << endl;

		//nTargets.push_back( new Target ( new Vert(rand()%64, rand()%64, rand()%64) ) );
		//cout << "BOMBS IS: " << nBombs.size() << endl;

}


void Mesh::MoveTargets(){

	if ( nTargets.empty() == false ){ 

		for (int a=0; a<nTargets.size(); a++){
			nTargets.at( a )->Move();
		}

	}

}


void Mesh::CalculateNormals()
{

	//initialize nNorms
	for(int x=0; x<numQuadsSide; x++){
		for(int z=0; z<numQuadsSide; z++){
			nNorms[x][z] = new Vert (0,1,0);
		}
	}

	Vector3 nVertNormals[4];
	Vector3 vert1, vert2, currentVert;

	for(int x=1; x<numQuadsSide-1; x++){
		for(int z=1; z<numQuadsSide-1; z++){
				currentVert = Vector3 (nVerts[x][z]->getX(),nVerts[x][z]->getY(),nVerts[x][z]->getZ());

				vert1 = Vector3(nVerts[x-1][z]->getX(),nVerts[x-1][z]->getY(),nVerts[x-1][z]->getZ());
				vert2 = Vector3(nVerts[x][z+1]->getX(),nVerts[x][z+1]->getY(),nVerts[x][z+1]->getZ());
				nVertNormals[0] = (vert1-currentVert)*(vert2-currentVert);
				nVertNormals[0].normalize();

				vert1 = Vector3(nVerts[x][z+1]->getX(),nVerts[x][z+1]->getY(),nVerts[x][z+1]->getZ());
				vert2 = Vector3(nVerts[x+1][z]->getX(),nVerts[x+1][z]->getY(),nVerts[x+1][z]->getZ());
				nVertNormals[1] = (vert1-currentVert)*(vert2-currentVert);
				nVertNormals[1].normalize();

				vert1 = Vector3(nVerts[x+1][z]->getX(),nVerts[x+1][z]->getY(),nVerts[x+1][z]->getZ());
				vert2 = Vector3(nVerts[x][z-1]->getX(),nVerts[x][z-1]->getY(),nVerts[x][z-1]->getZ());
				nVertNormals[2] = (vert1-currentVert)*(vert2-currentVert);
				nVertNormals[2].normalize();

				vert1 = Vector3(nVerts[x][z-1]->getX(),nVerts[x][z-1]->getY(),nVerts[x][z-1]->getZ());
				vert2 = Vector3(nVerts[x-1][z]->getX(),nVerts[x-1][z]->getY(),nVerts[x-1][z]->getZ());
				nVertNormals[3] = (vert1-currentVert)*(vert2-currentVert);
				nVertNormals[3].normalize();

				Vector3 finalNormal;
				finalNormal =(nVertNormals[0] + nVertNormals[1] + nVertNormals[2] + nVertNormals[3]);
				finalNormal.normalize();

				nNorms[x][z] = new Vert(finalNormal.x,finalNormal.y,finalNormal.z);
				//nNorms[x][z]->setX()
				//nNorms[x][z]->setY()
				//nNorms[x][z]->setZ()
		}
	}	
}


//uses the Gaussian functions to calculates distances and apply the heights to blobs.
void Mesh::CalculateDistances(){

	//reset's Y height per instructions
	for(int x=0;x<numQuadsSide;x++){
		for(int z=0;z<numQuadsSide;z++){
			nVerts[x][z]->setY(0);
		}
	}

	//not advisable when exceeds DOS prompt window size
	if (numQuadsSide < 15)
		PrintBlobs();


	double delX;
	double delZ;
	double delta; //note, another dist exists, but is different type, so it's fine...

	//assigns new heights per instructions
	for(int bl=0; bl<nBlobs.size(); bl++){
		for(int x=0;x<numVertsSide;x++){
			for(int z=0;z<numVertsSide;z++){

				//Compute a single vertice's dist from a single blob
				delX = nVerts[x][z]->getX() - nBlobs.at(bl)->getV()->getX();
				delZ = nVerts[x][z]->getZ() - nBlobs.at(bl)->getV()->getZ();

				//Pythagoras' Theorem
				delta = sqrt ( pow ( abs (delX), 2) + pow(abs(delZ), 2) );
				//cout << setprecision(2) << setw(3) << left << delta << " ";

				//nVerts[x][z]->setY( nVerts[x][z]->getY() + delta*nBlobs.at(b)->getWidth() );

				//Gausssian summation
				double a = nBlobs.at(bl)->getWidth();
				double b = nBlobs.at(bl)->getHeight();
				double r = delta;
				
				double gaussianSum = b * exp (-a * r * r );
				nVerts[x][z]->setY( nVerts[x][z]->getY() + gaussianSum );
				//cout << gaussianSum << " ";

			}
			//cout << endl;
		}
		//cout<<endl;

	}

}


/*
//just calls other methods
void Mesh::Go(){
	
	//CalculateDistances();
	//CalculateNormals();
	Draw();

}
*/

void Mesh::Draw(){
	if (_drawMode == 1) DrawFaces();
	else if (_drawMode == 2) DrawLines();
}

//includes operations that modify opengl state
void Mesh::DrawLines()
{

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	
	glPushMatrix();

	for (int z=0; z<numQuadsSide; z++){
		for (int x=0; x<numQuadsSide; x++){

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
				glLineWidth(5);
				for (int i=0; i<=3; i++){
					glVertex3f( nQuads[x][z]->getVert(i)->getX(), nQuads[x][z]->getVert(i)->getY(), nQuads[x][z]->getVert(i)->getZ() );
				}
			glEnd();
			//glFlush();	// don't know what this does.

		}
	}

	glPopMatrix();



	//glutSwapBuffers();
	//glPushMatrix();
}


//includes operations that modify opengl state
void Mesh::DrawFaces(){

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();


	DrawMesh();	

	nBalloon->Draw();

	DrawTargets();

	DrawBombs();
	

	//glPushMatrix();

}


void Mesh::DrawTargets(){

	for (int a=0; a<nTargets.size(); a++){
		nTargets.at(a)->Draw();
	}

}


void Mesh::DrawBombs(){

	if ( nBombs.empty() == false ){
		for (int a=0; a<nBombs.size()-1; a++){
			nBombs.at(a)->Draw();
		}
	}
}


void Mesh::DrawMesh(){

	glPushMatrix();

	for (int z=1; z<numQuadsSide-1; z++){
		for (int x=1; x<numQuadsSide-1; x++){

			//this block: creates  the faces
			glBegin(GL_QUADS);
				
				for (int i=0; i<=3; i++){

					switch(i){
						case 0:glNormal3f( nNorms[x][z]->getX(), nNorms[x][z]->getY(), nNorms[x][z]->getZ() ); break;
						case 1:glNormal3f( nNorms[x][z+1]->getX(), nNorms[x][z+1]->getY(), nNorms[x][z+1]->getZ() ); break;
						case 2:glNormal3f( nNorms[x+1][z+1]->getX(), nNorms[x+1][z+1]->getY(), nNorms[x+1][z+1]->getZ() ); break;
						case 3:glNormal3f( nNorms[x+1][z]->getX(), nNorms[x+1][z]->getY(), nNorms[x+1][z]->getZ() ); break;
					}

					glVertex3f( nQuads[x][z]->getVert(i)->getX(), nQuads[x][z]->getVert(i)->getY(), nQuads[x][z]->getVert(i)->getZ() );
				}

			glEnd();
			
		}
	}
	glPopMatrix();

}



//decided to use member variable instead of parameter to simply because of how OpenGL behaves with display this is simpler.
void Mesh::SetCamera(){

	// Set up the Viewing Transformation (V matrix)
	//eye, lookat, up
	//gluLookAt( numQuadsSide*numQuadsSide/2, numQuadsSide*numQuadsSide/2, 0, lookHere,0,lookHere, 0.0,1.0,0.0);
	//gluLookAt( numQuadsSide*numQuadsSide/2, numQuadsSide*numQuadsSide/2, 0, 0,0,0, 0.0,1.0,0.0);
	//gluLookAt( 0, numQuadsSide*numQuadsSide/2, 0, lookHere,0,lookHere, 0.0,1.0,0.0);



	//these following automatic terrain-posititioning optimizations are broken now... just leave as numQuadsSide = 64
	//camera positioning optimization for various quad sizes.
	float division;
	division = 1;

	if (numQuadsSide>2) division =3;
	if (numQuadsSide>5) division = numQuadsSide*0.7;
	if (numQuadsSide==64) division = numQuadsSide;



	//critically the eye must be especially high above the ground
	GLdouble eye_x ;
	GLdouble eye_y ;
	GLdouble eye_z ;
				   
	//look at center of the checkerboard of quads  (center of x/z)
	GLdouble look_x;
	GLdouble look_y;
	GLdouble look_z;

	//only important due to change when looking straight down, since cross product won't work on parallel vectors
	GLdouble up_x;
	GLdouble up_y;
	GLdouble up_z;


	//gluLookAt(20,20,20, 0,0,0, 0,1,0);


	if (cameraPosition == 1 || cameraPosition == 2 || cameraPosition == 3 || cameraPosition == 4){

		if (cameraPosition == 1){

			//terrain focus
			eye_x = numQuadsSide*numQuadsSide*dist/division;
			eye_y = numQuadsSide*numQuadsSide*dist/division;
			eye_z = numQuadsSide*numQuadsSide*dist/division;

			look_x = (numQuadsSide/3);
			look_y = -33;
			look_z = (numQuadsSide/3);

			up_x = 0;
			up_y = 1;
			up_z = 0;

		
	
		}
		else if (cameraPosition == 2){

			//bomb hanger
			eye_x = nBalloon->_posi->getX();
			eye_y = nBalloon->_posi->getY() - nBalloon->_bombDepth + 1;
			eye_z = nBalloon->_posi->getZ();

			look_x = nBalloon->_posi->getX(); 
			look_y = 0; 
			look_z = nBalloon->_posi->getZ(); 

			up_x = 1;
			up_y = 0;
			up_z = 0;

			

		}

		else if (cameraPosition == 3){

			//hemisphere look around
			
			eye_x = nCamera->_eye->getX();
			eye_y = nCamera->_eye->getY();
			eye_z = nCamera->_eye->getZ();
			
			look_x = nCamera->_look->getX(); 
			look_y = nCamera->_look->getY(); 
			look_z = nCamera->_look->getZ(); 
			
			up_x =  nCamera->_up->getX(); 
			up_y =  nCamera->_up->getY(); 
			up_z =  nCamera->_up->getZ(); 
			
		}

		else if (cameraPosition == 4){

			//balloon closeup
			eye_x = nBalloon->_posi->getX() + 8;
			eye_y = nBalloon->_posi->getY() - 8;
			eye_z = nBalloon->_posi->getZ() + 8;

			look_x = nBalloon->_posi->getX();
			look_y = nBalloon->_posi->getY() - 8;
			look_z = nBalloon->_posi->getZ();

			up_x = 0;
			up_y = 1;
			up_z = 0;

			
		}

		gluLookAt( eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x, up_y, up_z);

	}




}



void Mesh::DetectCollisions(){
	
	DetectCollisionsBombOnTarget();

}


void Mesh::DetectCollisionsBombOnTarget(){

	if ( nBombs.empty() == false && nTargets.empty() == false) {
	
		for ( int b=0; b<nBombs.size()-1; b++ ){
			for ( int t=0; t<nTargets.size(); t++ ) {
			
				if 
				( 
					//bomb radius excluded
					//references target 0 but retrieves static variable so it doesn't matter
					nBombs.at(b)->_posi->getX() > nTargets.at(t)->_posi->getX() - nTargets.at(0)->targetRadius &&
					nBombs.at(b)->_posi->getX() < nTargets.at(t)->_posi->getX() + nTargets.at(0)->targetRadius &&

					nBombs.at(b)->_posi->getY() > nTargets.at(t)->_posi->getY() - nTargets.at(0)->targetRadius &&
					nBombs.at(b)->_posi->getY() < nTargets.at(t)->_posi->getY() + nTargets.at(0)->targetRadius &&
					
					nBombs.at(b)->_posi->getZ() > nTargets.at(t)->_posi->getZ() - nTargets.at(0)->targetRadius &&
					nBombs.at(b)->_posi->getZ() < nTargets.at(t)->_posi->getZ() + nTargets.at(0)->targetRadius 
				){

					//collision
					cout << "COLLISION!!" << endl;
					DestroyBomb(b);
					DestroyTarget(t);
					glutPostRedisplay();
					
				}

			}
		}

	}
	

}


void Mesh::DestroyBomb( int bombIndex ){

	cout << "bomb removed" << endl;
	nBombs.erase( nBombs.begin() + bombIndex );

}



void Mesh::DestroyTarget( int targetIndex ){

	cout << "TARGET DESTROYED" << endl;
	nTargets.erase( nTargets.begin() + targetIndex );

}


void Mesh::MakeCamera(Vert* eye, Vert* look, Vert* up){

	nCamera = new Camera( eye, look, up );

}