#ifndef OBJ_MODEL_HPP
#define OBJ_MODEL_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "drawables/Mesh.hpp"
using namespace std;
/**
\file ObjModel.hpp
\brief Header file for ObjModel.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class ObjModel
\brief Class for loading in obj models.
*/

class ObjModel {
    int num_vertices;
    std::string obj_file;
    std::string mtl_file;
    bool loaded;
    Mesh mesh;
  public:
    ObjModel();
    ObjModel(std::string filepath);
    ~ObjModel();
    void loadFromFile(std::string filepath);
    bool isLoaded();
    void parseVertex(std::vector<std::string> vertex, std::vector<unsigned int> &indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<float> &texture_array, std::vector<float> &normal_array);
    Mesh getMesh();
    std::vector<std::string> splitString(std::string in, std::string delim=" ");
};

#endif
