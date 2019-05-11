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
  protected:
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
    GLint gl_textures[10]; ///< Locations of our shader texture uniforms.

    std::vector<float> vertices; ///< Vector containing all of the vertices in our object.
    std::vector<unsigned int> indices; ///< Vector containing vertex indices.
    std::vector<float> normals; ///< Vector containing vertex normals.
    std::vector<float> colors; ///< Vector containing the (r,g,b) color values for each vertice.
    std::vector<float> texture_uvs; ///< Vector containing our texture coordinates.

    std::vector<Texture*> textures; ///< Textures associated with this mesh.

    //Our game engine object and flags..
    Material material; ///< Object's material. We'll probably change this to be more dynamic soon.
    Shader* shader; ///< We definitely need a shader.
    bool update; ///< Signals that we need to update the graphics card.

    void updateMesh();

  public:
    Mesh();
    Mesh(Mesh &m1);
    ~Mesh();
    virtual void draw();

    void loadMaterial();
    void loadTextures();

    void cleanup();

    void setTexture(std::vector<Texture*> textures);
    void setMaterial(Material mat);
    void setShader(Shader* shader);
    void setLightingOn(bool l);

    //Set methods. Either vectors or floats + count to generate vectors.
    void setVertices(std::vector<Vertex> vertices);
    void setVertices(std::vector<float> v);
    void setIndices(std::vector<unsigned int> ind);
    void setTextureUVs(std::vector<float> uvs);
    void setNormals(std::vector<float> norms);
    void setColors(std::vector<float> c);

    void setVertices(float* v, unsigned int count);
    void setIndices(unsigned int* ind, unsigned int count);
    void setTextureUVs(float* uvs, unsigned int count);
    void setNormals(float* norms, unsigned int count);
    void setColors(float* c, unsigned int count);
    void setUseTexture(bool use);
    //Get functions for our copy Constructor
    unsigned int getVertexCount();
    Shader* getShader();
    bool getLightingOn();
    std::vector<Texture*> getTextures();
    std::vector<float> getUVS();
    std::vector<float> getNormals();
    std::vector<float> getVertices();
    std::vector<float> getColors();
    std::vector<unsigned int> getIndices();


};

#endif
