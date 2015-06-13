//作者：侯天朗
//时间：2015-6-13
//功能：方向键控制漫游
//调用方法：在main函数里输入glutKeyboardFunc(processNormalKeys);glutSpecialFunc(inputKey);
#include <glut.h>
#include <math.h>

static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
static GLint snowman_display_list;

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void moveMeFlat(int i) {
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}


void inputKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : angle -= 0.01f;orientMe(angle);break;
		case GLUT_KEY_RIGHT : angle +=0.01f;orientMe(angle);break;
		case GLUT_KEY_UP : moveMeFlat(1);break;
		case GLUT_KEY_DOWN : moveMeFlat(-1);break;
	}
}



