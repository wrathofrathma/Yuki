#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value ptr
#include "AssetManager.hpp"
#include "QuaternionObject.hpp"
/**
\file Drawable.hpp
\brief Header file for Drawable.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 4/20/2019

*/


/**
\class Drawable
\brief The Drawable class is base class for anything that wants to be drawn in our primary draw loop.
*/

class Drawable : public QuaternionObject {
  protected:
    GLint vPosition; ///< Shader position of vertex data.
    GLint vColor; ///< Shader position of vertex color.
    GLint vNormal; ///< Shader position of vertex normal.
    GLint vTexture; ///< Shader position of texture

    unsigned int vertex_count; ///< Total number of vertices in the object.
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> colors; ///< Vector containing the (r,g,b) color values for each vertice.
    std::vector<float> texture_coords; ///< Vector containing our texture coordinates.

    Shader *shader;

    Texture *texture;
    GLuint VAO;
    GLuint indicePtr;
    GLuint dataPtr;

    AssetManager *asset_manager;
    GLuint uModel; ///< Shader uniform position of model matrix.
    GLuint tex; ///< Actual texture id.
    bool useTexture;

    bool update; ///< Signals that we need to update the graphics card.
  public:
    Drawable(AssetManager *am);
    virtual ~Drawable();
    virtual void draw() = 0;
    virtual void updateGraphicsCard() = 0;
    void setUseTexture(bool);
};

#endif
