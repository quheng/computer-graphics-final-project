#include <windows.h>											// Header File For Windows
#include <GL/glew.h>
#include "GL/glut.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "glm.h"
#include "obj.h"
#include "display.h"
#include "keyboard.h"
#include "avi.h"

#define	G_PI 3.14159265358979323846f

using namespace std;

float direction[] = { 0, 0, 0 };//direction of spot light
float degree = 10;//degree of spot light
float pos[] = { 0, 0, 0, 1 };

float center[3] = { 0, 0, 8 }, eye[3] = { 0, 0, -7 }, dir[3] = {0,0,0};
float lx = 0, ly = 0, lz = -7;
float fRotate = 20.0f;

float oldmx = 0, oldmy = 0, h = 0, r = 1, c = G_PI / 180, du = 0;    //mouse
bool fan = true;		//control the fan
bool bAnim = false;      //the flag of rotation
bool bWire = false;

float light_pos[4] = { 0, 0, 1, 1 };   //position of light
/*obj model*/
GLuint lamp, sofa, coffeeTable, settee, sideTable1, sideTable2;

/*declaration of function*/
void initGL();   //initialization
void idle();                           //use the function to do display repeatly        
void reshape(int width, int height);
GLuint drawOBJ(char * filename);      //load the obj model 
void Mouse(int button, int state, int x, int y);
void onMouseMove(int x, int y);

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("final");
	initGL();
	//glutMouseFunc(Mouse);
	//glutMotionFunc(onMouseMove);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
}
void initGL(){
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0);  //black background
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	gluQuadricNormals(gluNewQuadric(), GLU_SMOOTH);						// Create Smooth Normals 
	gluQuadricTexture(gluNewQuadric(), GL_TRUE);						// Create Texture Coords 
	glEnable(GL_TEXTURE_2D);											// Enable Texture Mapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Set Texture Min Filter
	initAVI();
	loadOBJ();
}
void reshape(int width, int height){
	if (height == 0){
		height = 1;
	}
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	gluPerspective(20, 1, 0.1, 10);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matri
}
void idle()
{
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)  {
	// record initial coordinate when the mouse clicked fistly
	if (state == GLUT_DOWN)
		oldmx = x,
		oldmy = y;
}

void onMouseMove(int x, int y) {
	du += x - oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
	eye[0] = center[0] + r*cos(c*du);
	eye[2] = center[2] + r*sin(c*du);
	h += 0.03f*(y - oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
	if (h>1.0f) h = 1.0f; //视点y坐标作一些限制，不会使视点太奇怪
	else if (h<-1.0f) h = -1.0f;
	eye[1] = h;
	oldmx = x, oldmy = y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}