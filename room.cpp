#include "gl/glut.h" 
#include <windows.h> 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 

GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_diffuse1[] = { 0.1f, 0.5f, 0.8f, 1.0f };
GLfloat no_shininess[] = { 0.0f };
GLfloat sound[] = { 0.9, 0.9, 0.9, 1 };
GLint 	WinWidth;
GLint 	WinHeight;





/**************************** ÔØ Èë Î» Í¼ ×÷ Îª ÎÆ Àí µÄ Ïà ¹Ø º¯ Êý
************************************/
#define BMP_Header_Length 54 

GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLint last_texture_ID = 0;
	GLuint texture_ID = 0;
	FILE * pFile;
	fopen_s(&pFile, file_name, "rb");
	if (pFile == 0){
		printf_s("load file failed %s\n",file_name);
		return 0;
	}
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}
	pixels = (GLubyte*)malloc(total_bytes);  	if (pixels == 0)
	{
		fclose(pFile);  	 	return 0;
	}
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	free(pixels);
	return texture_ID;
}

extern GLuint texblackboard, texwindow, texdesk, texsound;
extern GLuint texceiling, texdoor, texfloor, texbackwall[5], texpole;
GLuint texairfro, texairback, texgaodi, texsdesk, texclock;
extern int backwall;

void drawscence()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	//地板
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texfloor);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //用于定义法线向量  	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-7.0f, -0.0f, 12.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-7.0f, -0.0f, -12.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, -0.0f, -12.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, -0.0f, 12.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//»æÖÆÌì»¨°å
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texceiling);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //ÓÃÓÚ¶¨Òå·¨ÏßÏòÁ¿  	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-7.0f, 7.0f, 12.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-7.0f, 7.0f, -12.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 7.0f, -12.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 7.0f, 12.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//»æÖÆ×ó±ßÇ½¼Ó×ó±ß´°»§ 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texwindow);
	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, 0.0f);
	for (int n = 0; n <= 1; n++)
	{
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0f, 0.0f);                  
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, 0, 0 + n * 12.0f);   	 			glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, 7.0f, 0 + n * 12.0f);   	 			glTexCoord2f(0.0f, 1.0f);
		glVertex3f(10, 7.0f, -12.0f + n * 12.0f);			glTexCoord2f(0.0f, 0.0f);
		glVertex3f(10, 0, -12.0f + n * 12.0f);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texdoor);
	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);                   //ÓÃÓÚ¶¨Òå·¨ÏßÏò	Á¿
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-10, 0, 12.0f);   	 	    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-10, 7.0f, 12.0f);   	 	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10, 7.0f, -12.0f);			glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10, 0, -12.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texbackwall[backwall]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); //ÓÃÓÚ¶¨Òå·¨ÏßÏòÁ¿ 
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, 12.0f);			glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-7.0f, 7.0f, 12.0f);   	 	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(7.0f, 7.0f, 12.0f);   	 	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 12.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texpole);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); //ÓÃÓÚ¶¨Òå·¨ÏßÏòÁ¿ 
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-70.0f, 0.0f, 12.0f);			glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-70.0f, 0.0f, 12.0f);  	 	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-70.0f, 0.0f, 12.0f);   	 	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-70.0f, 0.0f, 12.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}