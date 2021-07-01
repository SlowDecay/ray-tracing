#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Sphere.hpp"
#include "1605002_Triangle.hpp"
#include "1605002_Constants.hpp"
#include "1605002_Light.hpp"
#include "1605002_Floor.hpp"

using namespace std;

vector<Object*> objects;
vector<Light*> lights;

// Rotate fst and scn vectors around base vector by "kon" angles counter-clockwise
// All three vectors are unit vectors and mutually perpendicular 
void ghurao(const Vector3D& base, Vector3D& fst, Vector3D& scn, double kon)
{
    Vector3D afst(fst);
	Vector3D ascn(scn);		

    fst = afst*cos(kon)-ascn*sin(kon);
    scn = ascn*cos(kon)+afst*sin(kon);
}

// Global Variables declaration
Vector3D eye, up, daan, look; // Camera vectors

void drawAxes()
{

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);{
		glVertex3f( 300,0,0);
		glVertex3f(-300,0,0);

		glVertex3f(0,-800,0);
		glVertex3f(0, 800,0);

		glVertex3f(0,0, 300);
		glVertex3f(0,0,-300);
	}glEnd();
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1':
			ghurao(up, look, daan, RD);
			break;

        case '2':
            ghurao(up, look, daan, -RD);
			break;

        case '3':
			ghurao(daan, up, look, RD);
			break;

        case '4':
            ghurao(daan, up, look, -RD);
			break;

        case '5':
			ghurao(look, daan, up, RD);
			break;

        case '6':
            ghurao(look, daan, up, -RD);
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
            eye -= look*TD;
			break;
		case GLUT_KEY_UP:		// up arrow key
            eye += look*TD;
			break;

		case GLUT_KEY_RIGHT:
            eye += daan*TD;
			break;
		case GLUT_KEY_LEFT:
            eye -= daan*TD;
			break;

		case GLUT_KEY_PAGE_UP:
            eye += up*TD;
			break;
		case GLUT_KEY_PAGE_DOWN:
            eye -= up*TD;
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

    Vector3D reff(eye+look);
	gluLookAt(eye.x(),eye.y(),eye.z(),    reff.x(),reff.y(),reff.z(),    up.x(),up.y(),up.z());


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();

	for(Object* o: objects) o->draw();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization

    //Initializing pos, up, daan and look
    eye = Vector3D(100, 100, 0);
    up = Vector3D(0, 0, 1);
    daan = Vector3D(-1/sqrt(2), 1/sqrt(2), 0);
    look = Vector3D(-1/sqrt(2), -1/sqrt(2), 0);


	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void loadData()
{
	Floor* floor = new Floor(500, 20);
	objects.push_back(floor);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Ray Tracing");

	init();

	loadData(); // loading data from input

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
