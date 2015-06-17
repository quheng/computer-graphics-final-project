#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL\glut.h>
#include "keyboard.h"

extern float phi;
extern float angle;
extern float theta;
extern bool bAnim, fan;
void prepare_lighting();
void orientMe(float ang);
void moveMeFlat(int i);

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

	case 'f': fan = !fan;
	case 'A': angle -= 0.01f; orientMe(angle); break;
	case 'D': angle += 0.01f; orientMe(angle); break;
	case 'W': moveMeFlat(1); break;
	case 'S': moveMeFlat(-1); break;
	};
}

