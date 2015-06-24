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


float angle = 0.0, ratio;
float view_x = 0.0f, view_y = 0.0, view_z = 1.0f;
float lx = 0, ly = 0, lz = 0;
float fRotate = 20.0f;
bool fan = true;		//control the fan
bool bAnim = false;      //the flag of rotation
bool bWire = false;

float light_pos[4] = { 0, 0, 1, 1 };   //position of light
/*obj model*/
GLuint lamp, sofa, coffeeTable, settee;

/*declaration of function*/
void initGL();   //initialization
void idle();                           //use the function to do display repeatly        
void reshape(int width, int height);
GLuint drawOBJ(char * filename);      //load the obj model 

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("final");
	initGL();
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

