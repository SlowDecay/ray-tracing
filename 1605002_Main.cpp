#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Vector3D.hpp"
#include "1605002_Object.hpp"
#include "1605002_Sphere.hpp"
#include "1605002_Triangle.hpp"
#include "1605002_General.hpp"
#include "1605002_Constants.hpp"
#include "1605002_Globals.hpp"
#include "1605002_Light.hpp"
#include "1605002_Floor.hpp"
#include "1605002_Bitmap_Image.hpp"
#include "1605002_Ray.hpp"

using namespace std;

// Global variables
Vector3D eye, up, daan, look; // Camera vectors
vector<Object*> &objects = Object::objects;
vector<Light*> &lights = Light::lights;
int recursionLevel;
int windowHeight = 500;
int windowWidth = 500;
int imageHeight;
int imageWidth;
double viewAngle = 80;
double aspect = 1;

// Rotate fst and scn vectors around base vector by "kon" angles counter-clockwise
// All three vectors are unit vectors and mutually perpendicular 
void ghurao(const Vector3D& base, Vector3D& fst, Vector3D& scn, double kon)
{
    Vector3D afst(fst);
	Vector3D ascn(scn);		

    fst = afst*cos(kon)-ascn*sin(kon);
    scn = ascn*cos(kon)+afst*sin(kon);
}

double radian(double angle) { return angle*PI/180; }

void capture()
{
	// Initializing bitmap image
	bitmap_image image(imageWidth,imageHeight);

	for(int i=0;i<imageWidth;i++){
        for(int j=0;j<imageHeight;j++){
            image.set_pixel(i,j,0, 0, 0);
        }
    }

	double planeDistance = windowHeight/2/tan(radian(viewAngle/2));
	Vector3D topLeft = eye + look*planeDistance - daan*windowWidth/2 + up*windowHeight/2;

	double du = 1.0*windowWidth/imageWidth;
	double dv = 1.0*windowHeight/imageHeight;

	topLeft = topLeft + daan*(0.5*du) - up*(0.5*dv);

	for(int i = 1; i <= imageWidth; i++)
	{
		for(int j = 1; j <= imageHeight; j++)
		{
			int nearest = -1;
			double tmin = INF;

			Vector3D curPixel = topLeft + daan*(i-1)*du - up*(j-1)*dv;
			Ray ray(eye, curPixel-eye);
			double *color = new double[3];

			for(int k = 0; k < objects.size(); k++)
			{
				Object* o = objects[k];

				double t = o->intersect(ray, color, 0);
				if(t > 0 && t < tmin) tmin = t, nearest = k;
			}

			if(nearest != -1)
			{
				double t = objects[nearest]->intersect(ray, color, 1); // will change the level
				for(int i = 0; i < 3; i++) if(color[i] > 1) color[i] = 1;

				image.set_pixel(i, j, round(color[0]*255), round(color[1]*255), round(color[2]*255));
			}
		}
	}

	

	image.save_image("output.bmp");
}

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
		case '0':
			capture();
			break;

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
	for(Light* l: lights) l->draw();

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
	gluPerspective(viewAngle,	aspect,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void loadData()
{
	ifstream fin("scene.txt");

	fin >> recursionLevel >> imageHeight;
	imageWidth = imageHeight;

	int n;
	fin >> n;

	for(int i = 0; i < n; i++)
	{
		string name;
		fin >> name;

		Object* o;

		if(name == "sphere")
		{
			o = new Sphere();
			fin >> *((Sphere*)o);
		}
		else if(name == "triangle")
		{
			o = new Triangle();
			fin >> *((Triangle*)o);
		}
		else if(name == "general")
		{
			o = new General();
			fin >> *((General*)o);
		}

		objects.push_back(o);
	}

	int m;
	fin >> m;

	for(int i = 0; i < m; i++)
	{
		Light *l = new Light();
		fin >> *l;

		lights.push_back(l);
	}

	Object* floor = new Floor(500, 20);
	//objects.push_back(floor);
}

int main(int argc, char **argv){
	loadData(); // loading data from input

	glutInit(&argc,argv);
	glutInitWindowSize(windowHeight, windowWidth);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Ray Tracing");

	init();	

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
