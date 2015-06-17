#include "GL/glut.h"
#include "fan.h"


void drawfan(bool rot){
	GLfloat light_diffuse[4] = { 1.0, 1.0, 0.45, 1.0 };
	static int fantheta = 0;
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0, 1, 0);
	glScalef(0.1,0.03,0.1);
	gluSphere(gluNewQuadric(), 2, 20, 20);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
	glPopMatrix();
	
	//fan blade
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0, 1, 0);
	glScalef(0.1, 0.005, 0.1);
	glRotated(120 + fantheta, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 1, 3, 10, 20, 20);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0, 1, 0);
	glScalef(0.1, 0.005, 0.1);
	glRotated(fantheta, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 1,3, 10,20, 20);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0, 1, 0);
	glScalef(0.1, 0.005, 0.1);
	glRotated(240 + fantheta, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 1, 3, 10, 20, 20);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.65, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotated(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 13, 10, 10);
	glPopMatrix();

	if (rot){
		fantheta += 1;
		if (fantheta > 360)
			fantheta = 0;
	}
}