#include <iostream>
#include <GL/glew.h>
#include "GL/glut.h"
#include <stdio.h>
#include "glm.h"
#include <math.h>
#include "display.h"
#include "fan.h"
#include "avi.h"
#include "room.h"

using namespace std;

extern float direction[], pos[], degree;
extern float center[3], eye[3];
extern float fRotate ;
extern float light_pos[4];
extern bool fan ;		//control the fan
extern bool bAnim;      //the flag of rotation
extern bool bWire;      //the flag of rotation
extern bool color;      //the color of light
extern bool spot;      //the flag of spot

extern unsigned int texture[3];

extern GLuint lamp, sofa, coffeeTable, settee, sideTable1, sideTable2,tv;


GLfloat ctrlpoints[5][5][3] =
{
	{ { -3, 0.5, 0 }, { -1, 1.5, 0 }, { -2, 2, 0 }, { 1, -1, 0 }, { -5, 0, 0 } },
	{ { -3, 0.5, -1 }, { -1, 1.5, -1 }, { -2, 2, -1 }, { 1, -1, -1 }, { -5, 0, -1 } },
	{ { -3, 0.5, -2 }, { -1, 1.5, -2 }, { -2, 2, -2 }, { 1, -1, -2 }, { -5, 0, -2 } },
	{ { -3, 0.5, -3 }, { -1, 1.5, -3 }, { -2, 2, -3 }, { 1, -1, -3 }, { -5, 0, -3 } },
	{ { -3, 0.5, -4 }, { -1, 1.5, -4 }, { -2, 2, -4 }, { 1, -1, -4 }, { -5, 0, -4 } }
};

GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
int nurbs = 1;
extern GLUnurbsObj *theNurb1;

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(47.0f, 1, 0.1f, 1000.0f);
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1,1, 1, 1 };
	GLfloat yellow[] = { 0.1, 0.1, 0.4, 1 };
	if (color)
		glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	else
		glLightfv(GL_LIGHT0, GL_AMBIENT, yellow);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);


	glPushMatrix();

		if (bAnim)									//场景旋转
			fRotate += 0.5f;
		glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
		glScalef(3, 3, 3);

		glPushMatrix();								//墙壁
			glScalef(0.4f, 0.4f, 0.4f);
			glTranslatef(0.0f, -1.0, 0.0f);
			drawscence();   //wall
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0.0f, 0.0, -1.0f);		//家具整体位置

		glPushMatrix();							//nurbs曲面
			for (int i = 0; i < 5; i++)
			{
				if (nurbs){
					ctrlpoints[i][0][0] += 0.01;
					if (ctrlpoints[i][0][0] > 3.0)
						nurbs = 0;
				}
				else{
					ctrlpoints[i][0][0] -= 0.01;
					if (ctrlpoints[i][0][0] < -3.0)
						nurbs = 1;
				}
			}
			glTranslatef(0.2, 0.045, 2.0);
			glScalef(0.1, 0.1, 0.1);
			gluBeginSurface(theNurb1);
			gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
			gluEndSurface(theNurb1);
		glPopMatrix();


		glPushMatrix();
			glTranslatef(0.05f, 1.6f, 1.0f);
			glScalef(0.7f, 0.7f, 0.7f);
			drawfan(fan);
		glPopMatrix();

		glPushMatrix();    //tv and tv table
			glRotatef(180, 0, 1.0f, 0);
			glTranslatef(0.0f, 0.1f, -4.0f);
			glPushMatrix();								//电视柜
				glTranslatef(0.0f, -0.3f, 0.0f);
				glScalef(2.0f, 0.4f, 0.8f);
				glColor3f(1.0, 0.4, 0.6);
				glutSolidCube(1.0);		
				glRotatef(180, 0, 1.0f, 0);
			glPopMatrix();
			glPushMatrix();								//电视
				glTranslatef(0.2f, 0.4f, 0.0f);
				glScalef(0.18f, 0.18f, 0.18f);
				glCallList(tv);
			glPopMatrix();
			glPushMatrix();								//电视画面
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Set Texture Max Filter
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Set Texture Min Filter
				gluQuadricNormals(gluNewQuadric(), GLU_SMOOTH);						// Create Smooth Normals 
				gluQuadricTexture(gluNewQuadric(), GL_TRUE);						// Create Texture Coords 
				glTranslatef(-0.025f, 0.5f, 0.05f);
				glScalef(0.65f, 0.35f, 0.0f);
				drawAVI();
			glPopMatrix();
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(-0.1f, 0.0f, 0.0f);
			glPushMatrix();
				glTranslatef(-1.5f, 0.45f, -0.05f);
				glScalef(0.18f, 0.18f, 0.18f);
				glCallList(lamp);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.5f, -0.12f, -0.03f);
				glScalef(0.08f, 0.08f, 0.08f);
				glCallList(sideTable1);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.05f, -0.01f, -0.03f);
			glScalef(0.6f, 0.6f, 1.5f);
			glCallList(sofa);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0.04f, -0.19f, 2.0f);
			glScalef(0.5f, 0.5f, 0.5f);
			glCallList(coffeeTable);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, -0.01f, 2.0f);
			glScalef(0.3f, 0.3f, 0.3f);
			glCallList(settee);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, -0.12f, 3.5f);
			glScalef(0.08f, 0.08f, 0.08f);
			glCallList(sideTable2);
		glPopMatrix();

		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
