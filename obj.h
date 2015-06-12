//
//  obj.h
//  final project
//
//  Created by quheng on 6/11/15.
//  Copyright (c) 2015 quheng. All rights reserved.
//
#include <vector>
#include <string>
#include "glm/glm.hpp"
using namespace std;
#ifndef final_project_obj_h
#define final_project_obj_h

bool loadOBJ(
             const char* path,
             vector<glm::vec3> & out_vertices,
             vector<glm::vec2> & out_uvs,
             vector<glm::vec3> & out_normals
             );

void drawOBJ(
             vector<glm::vec3> normals,
             vector<glm::vec3> vertices
             );
#endif
