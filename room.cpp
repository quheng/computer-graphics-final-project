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





/**************************** 载 入 位 图 作 为 纹 理 的 相 关 函 数
************************************/ 
#define BMP_Header_Length 54 



/****************************载入一副位图作为纹理，返回的是纹理编
号**********************************************/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLint last_texture_ID = 0;
	GLuint texture_ID = 0;
	// 打开文件，如果失败，返回 
	FILE * pFile;
	fopen_s(&pFile,file_name, "rb");
	if (pFile == 0)
		return 0;
	// 读取文件中图象的宽度和高度  
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	// 计算每行像素所占字节数，并根据此数据计算总像素字节数 
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}
	// 根据总像素字节数分配内存 
	pixels = (GLubyte*)malloc(total_bytes);  	if (pixels == 0)
	{
		fclose(pFile);  	 	return 0;
	}
	// 读取像素数据 
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);   	 	
		fclose(pFile);   	 	
		return 0;
	}

	// 分配一个新的纹理编号 
	glGenTextures(1, &texture_ID);  	 	
	if (texture_ID == 0)
	{
		free(pixels);   	 	 	
		fclose(pFile);
		return 0;
	}
	// 绑定新的纹理，载入纹理并设置纹理参数 
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复   
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	// 之前为 pixels 分配的内存可在使用 glTexImage2D 以后释放 
	// 因为此时像素数据已经被 OpenGL 另行保存了一份（可能被保存到专门的图形硬件中） 
	free(pixels);
	return texture_ID;
}
/********************************** 定 义 各 个 纹 理 对 象 的 名 称
************************************/
GLuint texblackboard, texwindow, texdesk, texsound;
GLuint texceiling, texdoor, texfloor, texbackwall, texpole;
GLuint texairfro, texairback, texgaodi, texsdesk, texclock;
/*******************************	绘	制	相	关	函	数
**************************************************/

//绘制教室这个大场景 
void drawscence()
{
	//设置材质相关参数 
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	
	//绘制地板 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texbackwall);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //用于定义法线向量  	
	glVertex3f(-10.0f, -0.0f, 6.0f);
	glVertex3f(-10.0f, -0.0f, -6.0f);
	glVertex3f(10.0f, -0.0f, -6.0f);
	glVertex3f(10.0f, -0.0f, 6.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//绘制天花板
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texceiling);
	glColor3f(0.8f, 1.0f, 0.8f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);                   //用于定义法线向量  	
	glVertex3f(-10.0f, 5.0f, 6.0f);
	glVertex3f(-10.0f, 5.0f, -6.0f);
	glVertex3f(10.0f, 5.0f, -6.0f);
	glVertex3f(10.0f, 5.0f, 6.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//绘制左边墙加左边窗户 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texwindow);
	for (int n = 0; n <= 1; n++)
	{
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0f, 0.0f);                   //用于定义法线向	量
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10, 0, 0 + n * 6);   	 	glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, 5, 0 + n * 6);   	 	glTexCoord2f(0.0f, 1.0f);
		glVertex3f(10, 5, -6 + n * 6);		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(10, 0, -6 + n * 6);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	//绘制右边墙加门 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texdoor);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0f, 0.0f);                   //用于定义法线向	量
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-10, 0, 6);   	 	glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-10, 5, 6);   	 	glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10, 5, -6);		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10, 0, -6);
		glEnd();
	
	glDisable(GL_TEXTURE_2D);

	//后墙
	glEnable(GL_TEXTURE_2D);  	 	
	glBindTexture(GL_TEXTURE_2D, texbackwall);         
	glColor3f(0.8f, 0.8f, 0.8f);         
	glBegin(GL_QUADS);         
	glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量 
	glTexCoord2f(0.0f, 0.0f);  	 	
	glVertex3f(-10.0f, 0.0f, 6.0f); glTexCoord2f(0.0f, 1.0f);  	 	
	glVertex3f(-10.0f, 5.0f, 6.0f);   	 	glTexCoord2f(1.0f, 1.0f);  	 	
	glVertex3f(10.0f, 5.0f, 6.0f);   	 	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 6.0f);  	 	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
}
