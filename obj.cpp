#include <GL/glew.h>
#include "GL/glut.h"
#include "glm.h"
#include "obj.h"
extern GLuint lamp, sofa, coffeeTable, settee;

void loadOBJ(){
	lamp = drawOBJ("obj/Lamp/Lamp.obj");
	//sofa = drawOBJ("obj/Sofa/Sofa.obj");
	//coffeeTable = drawOBJ("obj/CoffeeTable/CoffeeTable.obj");
	//settee = drawOBJ("obj/Settee/Settee.obj");
}

GLuint drawOBJ(char * filename){
	GLMmodel *glm_model;
	GLuint list;
	glm_model = glmReadOBJ(filename);
	glmUnitize(glm_model);
	glmScale(glm_model, 5);
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);

	list = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);

	glmDelete(glm_model);
	return list;
}