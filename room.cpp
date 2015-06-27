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





/**************************** �� �� λ ͼ �� Ϊ �� �� �� �� �� �� ��
************************************/ 
#define BMP_Header_Length 54 



/****************************����һ��λͼ��Ϊ�������ص��������
��**********************************************/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLint last_texture_ID = 0;
	GLuint texture_ID = 0;
	// ���ļ������ʧ�ܣ����� 
	FILE * pFile;
	fopen_s(&pFile,file_name, "rb");
	if (pFile == 0)
		return 0;
	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�  
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ��� 
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}
	// �����������ֽ��������ڴ� 
	pixels = (GLubyte*)malloc(total_bytes);  	if (pixels == 0)
	{
		fclose(pFile);  	 	return 0;
	}
	// ��ȡ�������� 
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);   	 	
		fclose(pFile);   	 	
		return 0;
	}

	// ����һ���µ������� 
	glGenTextures(1, &texture_ID);  	 	
	if (texture_ID == 0)
	{
		free(pixels);   	 	 	
		fclose(pFile);
		return 0;
	}
	// ���µ������������������������ 
	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�   
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	// ֮ǰΪ pixels ������ڴ����ʹ�� glTexImage2D �Ժ��ͷ� 
	// ��Ϊ��ʱ���������Ѿ��� OpenGL ���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У� 
	free(pixels);
	return texture_ID;
}
/********************************** �� �� �� �� �� �� �� �� �� �� ��
************************************/
GLuint texblackboard, texwindow, texdesk, texsound;
GLuint texceiling, texdoor, texfloor, texbackwall, texpole;
GLuint texairfro, texairback, texgaodi, texsdesk, texclock;
/*******************************	��	��	��	��	��	��
**************************************************/

//���ƽ�������󳡾� 
void drawscence()
{
	//���ò�����ز��� 
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	
	//���Ƶذ� 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texbackwall);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //���ڶ��巨������  	
	glVertex3f(-10.0f, -0.0f, 6.0f);
	glVertex3f(-10.0f, -0.0f, -6.0f);
	glVertex3f(10.0f, -0.0f, -6.0f);
	glVertex3f(10.0f, -0.0f, 6.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//�����컨��
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texceiling);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //���ڶ��巨������  	
	glVertex3f(-10.0f, 5.0f, 6.0f);
	glVertex3f(-10.0f, 5.0f, -6.0f);
	glVertex3f(10.0f, 5.0f, -6.0f);
	glVertex3f(10.0f, 5.0f, 6.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//�������ǽ����ߴ��� 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texwindow);
	for (int n = 0; n <= 1; n++)
	{
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0f, 0.0f);                   //���ڶ��巨����	��
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, 0, 0 + n * 6);   	 	glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, 5, 0 + n * 6);   	 	glTexCoord2f(0.0f, 1.0f);
		glVertex3f(10, 5, -6 + n * 6);		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(10, 0, -6 + n * 6);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	//�����ұ�ǽ���� 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texdoor);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0f, 0.0f);                   //���ڶ��巨����	��
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-10, 0, 6);   	 	glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-10, 5, 6);   	 	glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10, 5, -6);		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10, 0, -6);
		glEnd();
	
	glDisable(GL_TEXTURE_2D);

	//��ǽ
	glEnable(GL_TEXTURE_2D);  	 	
	glBindTexture(GL_TEXTURE_2D, texbackwall);         
	glColor3f(0.8f, 0.8f, 0.8f);         
	glBegin(GL_QUADS);         
	glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������ 
	glTexCoord2f(0.0f, 0.0f);  	 	
	glVertex3f(-10.0f, 0.0f, 6.0f); glTexCoord2f(0.0f, 1.0f);  	 	
	glVertex3f(-10.0f, 5.0f, 6.0f);   	 	glTexCoord2f(1.0f, 1.0f);  	 	
	glVertex3f(10.0f, 5.0f, 6.0f);   	 	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 6.0f);  	 	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
}
