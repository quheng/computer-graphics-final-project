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

/*
float angle = 0.0, ratio;
float view_x = 0.0f, view_y = 0.0, view_z = 1.0f;
float lx = 0, ly = 0, lz = 0;
float fRotate = 20.0f;
bool fan = true;		//control the fan
bool bAnim = false;      //the flag of rotation
*/

//material of light
GLfloat white_light[] = { 1.0,1.0,1.0,1.0};
GLfloat shininess[] = { 5.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat diffusion[4] = { 0.52, 0.121, 0.0547, 1.0 };

GLfloat mat_specular[] = { 0.8, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[4] = { 0.05, 0.05, 0.05, 1.0 };

GLfloat light_diffuse[4] = { 1.0, 1.0, 0.45, 1.0 };
GLfloat light_ambient[4] = { 1.0, 1.0, 0.45, 1.0 };

//contral the light
float theta = G_PI / 2;
float phi = -G_PI / 2;         

/*obj model*/
GLuint lamp, sofa, coffeeTable, settee;

/*declaration of function*/

void initGL();   //initialization
void idle();                           //use the function to do display repeatly        
void reshape(int width, int height);
void prepare_lighting();  //control the light
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
	glutReshapeFunc(reshape);

	loadOBJ();
	prepare_lighting();

	glutMainLoop();
}

void initGL(){
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0);  //black background
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,mat_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For S To Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For T To Sphere Mapping
	gluQuadricNormals(gluNewQuadric(), GLU_SMOOTH);					// Create Smooth Normals 
	gluQuadricTexture(gluNewQuadric(), GL_TRUE);						// Create Texture Coords 
	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Set Texture Min Filter
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For S To Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For T To Sphere Mapping
	initAVI();
}
void prepare_lighting()
{
	
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);
	GLfloat light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
}
void reshape(int width, int height){
	if (height == 0){
		height = 1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	glutPostRedisplay();
}

