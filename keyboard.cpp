#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL\glut.h>
#include "keyboard.h"

extern float phi;
extern float angle;
extern float theta;
extern bool bAnim, fan, bWire;
extern float light_pos[4];

void orientMe(float ang);
void moveMeFlat(int i);

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'o': {bWire = !bWire; break; }

	case 'q':exit(0); break;

	case ' ':bAnim = !bAnim;break;

	case 'f': fan = !fan;
	case 'a': angle -= 0.01f; orientMe(angle); break;
	case 'd': angle += 0.01f; orientMe(angle); break;
	case 'w': moveMeFlat(1); break;
	case 's': moveMeFlat(-1); break;

	//light
	//forward
	case 'i':light_pos[2] += 0.4f; break;
	//back
	case 'k':light_pos[2] -= 0.4f;break;
	//left
	case 'j':light_pos[0] -= 0.4f;break;
	//right
	case 'l':light_pos[0] += 0.4f;break;
	//up
	case 'n':light_pos[1] -= 0.4f;break;
	//down
	case 'm':light_pos[1] += 0.4f;break;
	};
}

