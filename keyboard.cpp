#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL\glut.h>
#include "keyboard.h"
#include "snapScreen.h"

extern float phi;
extern float angle;
extern float theta;
extern bool bAnim, fan, bWire;
extern float light_pos[4];
extern float center[3], eye[3], dir[3],c,h,r;

float eyeDeX;
float eyeDeZ;

void dir_w()  {
	dir[0] = eye[0] - center[0];
	dir[2] = eye[2] - center[2];
	eye[0] -= eyeDeX * 0.3;
	eye[2] -= eyeDeZ * 0.3;
	center[0] = eye[0] - dir[0];
	center[2] = eye[2] - dir[2];
}

void dir_s(){
		dir[0] = eye[0] - center[0];
		dir[2] = eye[2] - center[2];
		eye[0] += eyeDeX *0.3;
		eye[2] += eyeDeZ *0.3;
		center[0] = eye[0] - dir[0];
		center[2] = eye[2] - dir[2];
}
void dir_d()  {
		dir[0] = center[0] - eye[0];
		dir[2] = center[2] - eye[2];
		dir[0] = dir[0] * cos(c * 5) - dir[2] * sin(c * 5);
		dir[2] = dir[0] * sin(c * 5) + dir[2] * cos(c * 5);
		center[0] = eye[0] + dir[0];
		center[2] = eye[2] + dir[2];
}
void dir_a(){
	//   angle = angle + 5;
		dir[0] = center[0] - eye[0];
		dir[2] = center[2] - eye[2];
		//  printf("dir0=%f,dir2=%f\n", dir[0], dir[2]);
		dir[0] = dir[0] * cos(c*(-5)) - dir[2] * sin(c*(-5));
		dir[2] = dir[0] * sin(c*(-5)) + dir[2] * cos(c*(-5));
		center[0] = eye[0] + dir[0];
		center[2] = eye[2] + dir[2];
}

void keyboard(unsigned char key, int x, int y)
{
	eyeDeX = 0.5*(eye[0] - center[0]) / 3;
	eyeDeZ = 0.5*(eye[2] - center[2]) / 3;
	switch (key)
	{
	case 'o': {bWire = !bWire; break; }

	case 'q':exit(0); break;

	case ' ':bAnim = !bAnim;break;

	case 'f': fan = !fan;
	case 'a': dir_a(); break;
	case 'd': dir_d(); break;
	case 'w': dir_w(); break;
	case 's': dir_s(); break;

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
	case '0':snapScreen(640, 640,"snap/snap.bmp"); break;
		/*
	case '1':
		direction[2] += 0.1;
		break;
	case '2':{
		direction[2] -= 0.1;
		break;
	}
	case '3':{
		direction[0] -= 0.1;
		break;
	}
	case '4':{
		direction[0] += 0.1;
		break;
	}
	case '5':{
		direction[1] -= 0.1;
		break;
	}
	case '6':{
		direction[1] += 0.1;
		break;
	}
	case '7':{
		degree += 1;
		break;
	}
	case '8':{
		degree -= 1;
		break;
	}
	case '9':{
		blight = !blight;
		break;
	}
	*/
	};
}

