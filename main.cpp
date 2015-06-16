#include "GL/glut.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "glm.h"

#define	G_PI 3.14159265358979323846f

using namespace std;

//control the view
float angle = 0.0, ratio;
float view_x = 0.0f, view_y = 0.0, view_z = 1.0f;
float lx = 0, ly = 0, lz = 0;

bool bAnim = false;      //the flag of rotation 
float fRotate = 20.0f;


//contral the light
float theta = G_PI / 2;
float phi = -G_PI / 2;         

/*obj model*/
GLuint lamp, sofa, coffeeTable, settee;


/*declaration of function*/

void idle();                           //use the function to do display repeatly        
void reshape(int width, int height);

void orientMe(float ang);
void moveMeFlat(int i);    //change the view 

void prepare_lighting();  //control the light
void display();           //control the content of display

void keyboard(unsigned char key, int x, int y);  //control the reflection of keyboard
GLuint drawOBJ(char * filename);      //load the obj model 

void main()
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("glutTest08");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
	//glutReshapeFunc(reshape);

	lamp = drawOBJ("obj/Lamp/Lamp.obj");
	sofa = drawOBJ("obj/Sofa/Sofa.obj");
	coffeeTable = drawOBJ("obj/CoffeeTable/CoffeeTable.obj");
	settee = drawOBJ("obj/Settee/Settee.obj");
	prepare_lighting();

	glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		theta -= .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 's':
		theta += .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 'a':
		phi -= .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 'd':
		phi += .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 'q':exit(0); break;

	case ' ':
	{
		bAnim = !bAnim;
		break;
	}

	//µ÷ÕûÊÓ½Ç²ÎÊý ´óÐ´
	case 'A': angle -= 0.01f; orientMe(angle); break;
	case 'D': angle += 0.01f; orientMe(angle); break;
	case 'W': moveMeFlat(1); break;
	case 'S': moveMeFlat(-1); break;
	};
}

GLuint drawOBJ(char * filename){
	GLMmodel *glm_model;
	GLuint list;
	glm_model = glmReadOBJ(filename);
	glmUnitize(glm_model);
	glmScale(glm_model, .1);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);

	list = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);

	glmDelete(glm_model);
	return list;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(view_x, view_y, view_z,
		view_x + lx, view_y + ly, view_z + lz,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glPushMatrix();
	//¿ØÖÆµÚÒ»¸öobj
	glTranslatef(0.05f, -0.002f, 0.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	glCallList(lamp);
	glPopMatrix();


	glPushMatrix();
	//¿ØÖÆµÚ¶þ¸öobj
	glTranslatef(0.05f, -0.01f, -0.03f);
	glScalef(0.6f, 0.6f, 0.6f);
	glCallList(sofa);
	glPopMatrix();

	glPushMatrix();
	//¿ØÖÆµÚÈý¸öobj
	glTranslatef(0.04f, -0.012f, 0.01f);
	glScalef(0.5f, 0.5f, 0.5f);
	glCallList(coffeeTable);
	glPopMatrix();

	glPushMatrix();
	//¿ØÖÆµÚËÄ¸öobj
	glTranslatef(0.0f, -0.01f, 0.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glCallList(settee);
	glPopMatrix();

	/*
	glPushMatrix();
	//¿ØÖÆµÚÒ»¸öNURBS
	glTranslatef(1.0, 0.0, 0.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	//¿ØÖÆµÚ¶þ¸öNURBS
	glTranslatef(7.0, 0.0, 0.0);
	gluBeginSurface(theNurb2);
	gluNurbsSurface(theNurb2, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb2);
	glPopMatrix();
	*/

	glutSwapBuffers();
}

void prepare_lighting()
{
	/*
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);

	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	*/
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
}

void moveMeFlat(int i) {
	view_x = view_x + i*(lx)*0.1;
	view_z = view_z + i*(lz)*0.1;
}
