#include <stdio.h>
#include <math.h>

#include "gl\glut.h"

#include "glm.h"

#define	G_PI 3.14159265358979323846f

void prepare_lighting();  //control the light
void display();           //control the content of display
void keyboard(unsigned char key, int x, int y);  //control the reflection of keyboard
GLuint drawOBJ(char * filename);      //load the obj model 

float theta, phi;

GLuint list_id;

void main()
{
	theta = G_PI / 2;
	phi = -G_PI / 2;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("glutTest08");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	{
		list_id = drawOBJ("plant.obj");
	}

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
	gluLookAt(
		0, 0, 1,
		0, 0, 0,
		0, 1, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glCallList(list_id);

	glutSwapBuffers();
}

void prepare_lighting()
{
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);

	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 0 };

	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
}