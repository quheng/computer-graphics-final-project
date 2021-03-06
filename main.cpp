﻿#include <windows.h>											// Header File For Windows
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
#include "room.h"


#define BITMAP_ID 0x4D42
#define	G_PI 3.14159265358979323846f

using namespace std;

float direction[] = { 0, 0, 0 };//direction of spot light
float degree = 10;//degree of spot light
float pos[] = { 0, 0, 0, 1 };

float center[3] = { 0, 1.5, 9 }, eye[3] = { 0, 1.5, -6 }, dir[3] = {0,0,0};
float fRotate = 0.0f;

float oldmx = 0, oldmy = 0, h = 2, r = 15, c = G_PI / 180, du = -90;    //mouse
bool fan = true;		//control the fan
bool bAnim = false;      //the flag of rotation
bool bWire = false;
bool color = true;		//control the color of light
bool spot = false;		//control the color of spot

float light_pos[4] = { 0, 0, 6, 1 };   //position of light


int backwall = 0;
/*obj model*/
GLuint lamp, sofa, coffeeTable, settee, sideTable1, sideTable2,tv;

//room
GLuint texbackwall[5], texwindow, texdoor, texceiling, texpole,texfloor;

//nurbs
GLUnurbsObj *theNurb1;

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
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
}
void initGL(){
	//wall
	texbackwall[0] = load_texture("tex/b1.bmp");
	texbackwall[1] = load_texture("tex/b2.bmp");
	texbackwall[2] = load_texture("tex/b3.bmp");
	texbackwall[3] = load_texture("tex/b4.bmp");

	texwindow = load_texture("tex/window.bmp");
	texdoor = load_texture("tex/door.bmp");
	texceiling = load_texture("tex/ceiling.bmp");
	texfloor = load_texture("tex/floor.bmp");

	theNurb1 = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_FILL);
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
	if (h>5.5f) h = 5.5f; //视点y坐标作一些限制，不会使视点太奇怪
	else if (h<-5.5f) h = -5.5f;
	eye[1] = h;
	oldmx = x, oldmy = y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}
