#ifndef MESH_HPP
#define MESH_HPP
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value ptr
#include <vector>
class Texture;
class Shader;
class Material;
#include "../components/QuaternionObject.hpp"
/**
\file Mesh.hpp
\brief header file for Mesh.cpp

\author Christopher Arausa
\version 0.1
\date 4/20/2019

*/


struct Vertex {
  glm::vec4 position;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 texture;
};

/**
\class Mesh

\brief The Mesh class right now is a skeleton class preparing to start loading objects from file.

*/

class Mesh : public QuaternionObject {
  private:
    //GLSL stuff
    GLint vPosition; ///< Shader position of vertex data.
    GLint vNormal; ///< Shader position of vertex normal.
    GLint vColor; ///< Shader position of vertex color.
    GLint vTexture; ///< Shader position of texture
    GLuint VAO; ///< VAO
    GLuint indicePtr; ///< VBO
    GLuint dataPtr; ///< EBO
    GLuint uModel; ///< Shader uniform position of model matrix.
    bool lighting_on; ///< Determines if we apply lighting to this drawable.
    bool useTexture; ///< Tracks whether we're using textures or just colors. Is used to set a uniform in our shader to toggle texure vs color rendering.

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures; ///< Textures associated with this mesh.

    //Our game engine object and flags..
    Material material; ///< Object's material. We'll probably change this to be more dynamic soon.
    Shader* shader; ///< We definitely need a shader.
    bool update; ///< Signals that we need to update the graphics card.

    void updateMesh();

  public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
    ~Mesh();
    void draw();

    void setUseTexture(bool use);
    void setTexture(std::vector<Texture*> textures);
    void setIndices(std::vector<unsigned int> indices);
    void setVertices(std::vector<Vertex> vertices);
    void setShader(Shader* shader);
    void setLightingOn(bool l);
    unsigned int getVertexCount();
    bool getLightingOn();
    void loadMaterial();
    void cleanup();
};

#endif
