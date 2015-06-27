#include "gl/glew.h"
#include "gl/glut.h"
#include "glm.h"
#include <math.h>
#include "display.h"
#include "fan.h"
#include "avi.h"
#include "room.h"


extern float direction[], pos[], degree;
extern float center[3], eye[3];
extern float fRotate ;
extern float light_pos[4];
extern bool fan ;		//control the fan
extern bool bAnim;      //the flag of rotation
extern bool bWire;      //the flag of rotation

extern GLuint lamp, sofa, coffeeTable, settee, sideTable1, sideTable2;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	{
		// gradient background
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, 640, 0.0, 640, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glBegin(GL_QUADS);
		glColor3f(0.2, 0.4, 0.8);
		glVertex2f(0.0, 0.0);
		glVertex2f(640, 0.0);
		glColor3f(0.05, 0.1, 0.2);
		glVertex2f(640, 640);
		glVertex2f(0, 640);
		glEnd();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1, 0.1f, 1000.0f);
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1,1, 0.01, 0.01 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	glPushMatrix();
	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glPushMatrix();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Set Texture Min Filter
	gluQuadricNormals(gluNewQuadric(), GLU_SMOOTH);						// Create Smooth Normals 
	gluQuadricTexture(gluNewQuadric(), GL_TRUE);						// Create Texture Coords 
	glTranslatef(0.0f, -0.01f, 4.0f);
	drawAVI();
	glPopMatrix();

	glPushMatrix();
	drawscence();//  wall
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05f, 1.0, 1.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	drawfan(fan);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05f, 0.5f, 2.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	glCallList(lamp);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05f, -0.01f, -0.03f);
	glScalef(0.6f, 0.6f, 1.5f);
	glCallList(sofa);
	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04f, -0.012f, 2.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glCallList(coffeeTable);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -0.01f, 2.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glCallList(settee);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -0.01f, -0.03f);
	glScalef(0.08f, 0.08f, 0.08f);
	glCallList(sideTable1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -0.01f, 3.5f);
	glScalef(0.08f, 0.08f, 0.08f);
	glCallList(sideTable2);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}
