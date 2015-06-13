#include "gl\glut.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "glm.h"

#define	G_PI 3.14159265358979323846f

using namespace std;

//视角控制
float angle = 0.0, ratio;
float view_x = 0.0f, view_y = 0.0, view_z = 1.0f;
float lx = 0, ly = 0, lz = 0;

bool bAnim = false;      //the flag of rotation 
float fRotate = 20.0f;
float theta, phi;        //contral the light

/*obj model*/
GLuint monkey, plant;

/*NURBS model*/
int spin = 0;
GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
GLUnurbsObj *theNurb1;
GLUnurbsObj *theNurb2;
GLfloat ctrlpoints[5][5][3] = { { { -3, 0.5, 0 }, { -1, 1.5, 0 }, { -2, 2, 0 }, { 1, -1, 0 }, { -5, 0, 0 } },
{ { -3, 0.5, -1 }, { -1, 1.5, -1 }, { -2, 2, -1 }, { 1, -1, -1 }, { -5, 0, -1 } },
{ { -3, 0.5, -2 }, { -1, 1.5, -2 }, { -2, 2, -2 }, { 1, -1, -2 }, { -5, 0, -2 } },
{ { -3, 0.5, -3 }, { -1, 1.5, -3 }, { -2, 2, -3 }, { 1, -1, -3 }, { -5, 0, -3 } },
{ { -3, 0.5, -4 }, { -1, 1.5, -4 }, { -2, 2, -4 }, { 1, -1, -4 }, { -5, 0, -4 } } };

/*declaration of function*/

void idle();                           //use the function to do display repeatly        
void reshape(int width, int height);

void orientMe(float ang);
void moveMeFlat(int i);    //change the view 

void prepare_lighting();  //control the light
void display();           //control the content of display

void keyboard(unsigned char key, int x, int y);  //control the reflection of keyboard
GLuint drawOBJ(char * filename);      //load the obj model 
void myDisplay(void);

void main()
{
	theta = G_PI / 2;
	phi = -G_PI / 2;


	theNurb1 = gluNewNurbsRenderer();//创建NURBS对象theNurb1
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);

	theNurb2 = gluNewNurbsRenderer();//创建NURBS对象theNurb2
	gluNurbsProperty(theNurb2, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb2, GLU_DISPLAY_MODE, GLU_FILL);



	/*设置特殊效果*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("glutTest08");

	glutDisplayFunc( display);
	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
	//glutReshapeFunc(reshape);

	monkey = drawOBJ("monkey.obj");
	plant = drawOBJ("plant.obj");

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

		/* 控制NURBS曲面*/
	case '/':                        
		spin = spin + 1;
		glRotatef(spin, 1.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	
	case 'q':exit(0); break;

	case ' ':
	{
		bAnim = !bAnim;
		break;
	}

	//调整视角参数 大写
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

void myDisplay(void)
{
	GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(50.0, 1.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.0, 0.0, 0.0);
	gluBeginSurface(theNurb2);
	gluNurbsSurface(theNurb2, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb2);
	glPopMatrix();
	glutSwapBuffers();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cout << view_x << ' ' << view_y << ' ' << view_z << ' ' << endl;
	
	gluLookAt(view_x, view_y, view_z,
		view_x + lx, view_y + ly, view_z + lz,
		0.0f, 1.0f, 0.0f);
		
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glPushMatrix();
	//控制第一个obj
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glCallList(monkey);
	glPopMatrix();


	glPushMatrix();
	//控制第二个obj
	glTranslatef(0.1f, 0.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glCallList(plant);
	glPopMatrix();

	/*
	glPushMatrix();
	//控制第一个NURBS
	glTranslatef(1.0, 0.0, 0.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	//控制第二个NURBS
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
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);

	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
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
