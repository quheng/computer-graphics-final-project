#include <GL/glew.h>
#include "GL/glut.h"
#include "glm.h"
#include <math.h>
#include "display.h"
#include "fan.h"
#include "avi.h"



extern float angle, ratio;
extern float view_x , view_y , view_z;
extern float lx, ly, lz;
extern float fRotate ;
extern float light_pos[4];
extern bool fan ;		//control the fan
extern bool bAnim;      //the flag of rotation
extern bool bWire;      //the flag of rotation

extern GLuint lamp, sofa, coffeeTable, settee;

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
}

void moveMeFlat(int i) {
	view_x = view_x + i*(lx);
	view_z = view_z + i*(lz);
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

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 0.01, 0.01, 0.01, 0.01 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glPushMatrix();
	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glPushMatrix();
	glTranslatef(0.05f, -0.002f, 0.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	glCallList(lamp);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.05f, -0.01f, -0.03f);
	glScalef(0.6f, 0.6f, 0.6f);
	glCallList(sofa);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04f, -0.012f, 0.01f);
	glScalef(0.5f, 0.5f, 0.5f);
	glCallList(coffeeTable);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.01f, 0.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glCallList(settee);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.01f, 0.0f);
	//drawAVI();
	glPopMatrix();
	glutSwapBuffers();
}
