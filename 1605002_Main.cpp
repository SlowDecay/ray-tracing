#include <GL/glut.h>
#include <windows.h>

#include<bits/stdc++.h>

using namespace std;

struct Vector3D
{
	double x,y,z;

    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(double x, double y, double z): x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& rhs) const { return Vector3D(x+rhs.x, y+rhs.y, z+rhs.z); }
    Vector3D operator+=(const Vector3D& rhs)
    {
        x += rhs.x, y += rhs.y, z += rhs.z;
        return *this;
    }

    Vector3D operator-(const Vector3D& rhs) const { return Vector3D(x-rhs.x, y-rhs.y, z-rhs.z); }
    Vector3D operator-=(const Vector3D& rhs)
    {
        x -= rhs.x, y -= rhs.y, z -= rhs.z;
        return *this;
    }

    Vector3D operator*(double d) const { return Vector3D(x*d, y*d, z*d); }
};

// Constants declaration
const double pi = (2*acos(0.0));
const int M = 200;
const double TD = 2.5; // Camera translation in one key press
const double RD = 0.03; // Camera rotation angle in one key press
const int STS = 30; // Number of stacks
const double BR = 30; // Big sphere radius
const double SR = 10; // Small sphere radius
const int SLS = 70; // Number of slices
const double CHT = 100; // Cylinder height
const double PD = 400; // Distance of curtain from origin
const double PHL = 160; // curtain half length
const double MANGLE = 40; // Maximum angle of gun rotation
const double DELTA = 1; // Gun rotation angle in one key press
const double BHL = 5; // Bullet half length
const Vector3D RED(1,0,0);
const Vector3D GREY(0.5,0.5,0.5);

ostream& operator<<(ostream& dout, Vector3D p)
{
	return dout << p.x << " " << p.y << " " << p.z;
}

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
Vector3D pos, up, daan, look; // Camera vectors
double anglez, anglex1, anglex2, angley; // Gun rotation vectors: anglex1 is the whole rotation and anglex2 is the gun tube rotation
Vector3D root, diik; // root: intersection point of big and small spheres, diik: unit vector along gun tube
Vector3D cheds[M]; // Bullets in board
int curChed; // Number of bullets
Vector3D points[M][M]; // Points to draw

void drawRing(int stacks, int slices)
{
	//draw quads using generated points
	for(int i=0;i<stacks;i++)
	{
		int red = 0, green = 0, blue = 0;

		for(int j=0;j<slices;j++)
		{
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}glEnd();

			red = 255-red, green = 255-green, blue = 255-blue;
		}
	}
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

void drawSquare(double hl, Vector3D center, Vector3D color)
{
    glColor3f(color.x,color.y,color.z);

	glBegin(GL_QUADS);{
		glVertex3f(center.x-hl, center.y,center.z+hl);
		glVertex3f(center.x+hl, center.y,center.z+hl);
		glVertex3f(center.x+hl, center.y,center.z-hl);
		glVertex3f(center.x-hl, center.y,center.z-hl);
	}glEnd();
}


// Draw a semi-sphere along the y-axis.
void drawHalfSphere(double radius,int slices,int stacks, int shamne)
{
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=h*shamne;
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
		}
	}
	
	drawRing(stacks, slices);
}

// Draw a cylinder along y axis
void drawCylinder(double radius, double height, int slices, int stacks)
{
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=(double)i/stacks*height;
		r=radius;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=h;
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
		}
	}
	
	drawRing(stacks, slices);
}

// Rotating a quarter circle
void drawHead(double innerRad, double outerRad, int slices, int stacks)
{
	int i,j;
	double h,r,angle;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		angle = (double)i/stacks*pi/2;
		h=outerRad*sin(angle);
		r=innerRad+outerRad-outerRad*cos(angle);

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=h;
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
		}
	}
	
	drawRing(stacks, slices);
}

void drawGun()
{
	drawSquare(PHL, Vector3D(0,PD,0), GREY);
	for(int i = 0; i < curChed; i++) drawSquare(BHL, cheds[i], RED);

	glRotatef(anglez, 0, 0, 1);
	drawHalfSphere(BR, SLS, STS, -1);

	glRotatef(anglex1, 1, 0, 0);
	drawHalfSphere(BR, SLS, STS, 1);

	glTranslatef(0, BR+SR, 0);

	glRotatef(anglex2, 1, 0, 0);
	glRotatef(angley, 0, 1, 0);

	drawHalfSphere(SR, SLS, STS, -1);
	drawCylinder(SR, CHT, SLS, STS);

	glTranslatef(0, CHT, 0);
	drawHead(SR, SR*2/3.0, SLS, STS*3);
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

		case 'q':
			anglez = min(anglez+DELTA, MANGLE);
			break;

		case 'w':
			anglez = max(anglez-DELTA, -MANGLE);
			break;

		case 'e':
			anglex1 = min(anglex1+DELTA, MANGLE);
			break;

		case 'r':
			anglex1 = max(anglex1-DELTA, -MANGLE);
			break;

		case 'a':
			anglex2 = min(anglex2+DELTA, MANGLE);
			break;

		case 's':
			anglex2 = max(anglex2-DELTA, -MANGLE);
			break;

		case 'd':
			angley = min(angley+DELTA, MANGLE);
			break;

		case 'f':
			angley = max(angley-DELTA, -MANGLE);
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
            pos -= look*TD;
			break;
		case GLUT_KEY_UP:		// up arrow key
            pos += look*TD;
			break;

		case GLUT_KEY_RIGHT:
            pos += daan*TD;
			break;
		case GLUT_KEY_LEFT:
            pos -= daan*TD;
			break;

		case GLUT_KEY_PAGE_UP:
            pos += up*TD;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos -= up*TD;
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				double kon1 = anglex1*pi/180; // Big sphere rotation around x axis
				double kon2 = anglez*pi/180; // Rotation around z axis
				double kon3 = (anglex1+anglex2)*pi/180; // Full rotation around x axis

				// Converting to cartesian from Polar
				root = Vector3D(-cos(kon1)*sin(kon2), cos(kon1)*cos(kon2), sin(kon1))*BR;
				diik = Vector3D(-cos(kon3)*sin(kon2), cos(kon3)*cos(kon2), sin(kon3))*BR;

				double k = (PD-root.y)/diik.y;
				Vector3D ched = root+diik*k;

				cout << ched << endl;

				ched.y--;

				// Check if bullet falls on curtain
				if(ched.x-BHL >= -PHL && ched.x+BHL <= PHL
				&& ched.z-BHL >= -PHL && ched.z+BHL <= PHL) cheds[curChed++] = ched;
			}

			break;

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

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
    Vector3D reff(pos+look);
	gluLookAt(pos.x,pos.y,pos.z,    reff.x,reff.y,reff.z,    up.x,up.y,up.z);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();

    glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);
	drawGun();



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
    pos = Vector3D(100, 100, 0);
    up = Vector3D(0, 0, 1);
    daan = Vector3D(-1/sqrt(2), 1/sqrt(2), 0);
    look = Vector3D(-1/sqrt(2), -1/sqrt(2), 0);

	//Initializing koyta, root, diik
	root = Vector3D(0, BR, 0);
	diik = Vector3D(0, 1, 0);
	curChed = 0;


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

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Gun");

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
