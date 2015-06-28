#include <GL/glew.h>
#include "GL/glut.h"
#include "stdlib.h"
#include "glm.h"
#include "obj.h"

extern GLuint lamp, sofa, coffeeTable, settee, sideTable1, sideTable2, tv;

void loadOBJ(){
	lamp = drawOBJ("obj/Lamp/lamp.obj");
	//sofa = drawOBJ("obj/Sofa/Sofa.obj");
	coffeeTable = drawOBJ("obj/CoffeeTable/CoffeeTable.obj");
	//settee = drawOBJ("obj/Settee/Settee.obj");
	//sideTable1 = drawOBJ("obj/SideTable1/SideTable1.obj");
	//sideTable2 = drawOBJ("obj/SideTable1/SideTable1.obj");
	//tv = drawOBJ("obj/tv/tv.obj");
}

GLuint drawOBJ(char * filename){
	GLMmodel *glm_model;
	GLuint list;
	glm_model = glmReadOBJ(filename);
	glmUnitize(glm_model);
	glmScale(glm_model, 5);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);
	list = glmList(glm_model, GLM_TEXTURE | GLM_SMOOTH | GLM_MATERIAL );

	glmDelete(glm_model);
	return list;
}
