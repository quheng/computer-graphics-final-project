#include <GL/glew.h>
#include "GL/glut.h"
#include "glm.h"
#include <math.h>
#include "display.h"
#include "fan.h"
#include "avi.h"



extern float angle = 0.0, ratio;
extern float view_x = 0.0f, view_y = 0.0, view_z = 1.0f;
extern float lx = 0, ly = 0, lz = 0;
extern float fRotate = 20.0f;
extern bool fan = true;		//control the fan
extern bool bAnim = false;      //the flag of rotation
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
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glEnable(GL_COLOR_MATERIAL);
	drawfan(fan);
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
	Draw();
	glPopMatrix();

	glutSwapBuffers();
}
