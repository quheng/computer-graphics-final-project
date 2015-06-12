#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gl/glut.h"
#include "glm/glm.hpp"
#include "obj.h"

using namespace std;

bool loadOBJ(
	const char* path,
	vector<glm::vec3> & out_vertices,
	vector<glm::vec2> & out_uvs,
	vector<glm::vec3> & out_normals
	){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	/*
	FILE *file;
	fopen_s(&file,path, "r");
	if( file == NULL ){
	printf("Impossible to open the file !\n");
	return false;
	}
	while (1){
	char lineHeader[255];
	if (!fgets(lineHeader, 255, file)) break;

	cout << lineHeader;
	}
	*/
	ifstream fin(path);
	if (!fin.eof()) {
		string sLine;
		while (fin >> sLine){ // read the first word of the line
			if (sLine == "v"){
				cout << "Get v" << endl;
				glm::vec3 vertex;
				double x, y, z;
				fin >> x >> y >> z;
				vertex.x = x;
				vertex.y = y;
				vertex.z = z;
				temp_vertices.push_back(vertex);
			}
			else if (sLine == "vt"){
				cout << "Get vt" << endl;
				glm::vec2 uv;
				double x, y;
				fin >> x >> y;
				uv.x = x;
				uv.y = y;
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				temp_uvs.push_back(uv);
			}
			else if (sLine == "vn"){
				cout << "Get vn" << endl;
				glm::vec3 normal;
				double x, y, z;
				fin >> x >> y >> z;
				normal.x = x;
				normal.y = y;
				normal.z = z;
				temp_normals.push_back(normal);
			}
			else if (sLine == "f"){
				cout << "Get f" << endl;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				/*two kinds of obj formats
				fin >> vertexIndex[0] >>
				uvIndex[0] >> normalIndex[0] >>
				vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >>
				vertexIndex[2] >> uvIndex[2] >> normalIndex[2];
				*/
				fin >> vertexIndex[0] >> normalIndex[0] >> vertexIndex[1] >> normalIndex[1] >> vertexIndex[2] >> normalIndex[2];

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	else{
		cout << "Impossible to open the file !" << endl;
	}
	fin.close();

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_normals.push_back(normal);

	}    return true;
}

void drawOBJ(
             vector<glm::vec3> normals,
             vector<glm::vec3> vertices
){
	glBegin(GL_TRIANGLES);
	for (int i = 0; i<vertices.size(); i++)
	{
		glNormal3f(normals[i].x / 4, normals[i].y / 4, normals[i].z / 4);
		glVertex3f(vertices[i].x / 4, vertices[i].y / 4, vertices[i].z / 4);
	}
	glEnd();
}