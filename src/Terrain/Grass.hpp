#ifndef GRASS_HPP
#define GRASS_HPP
#include <vector>
#include "../graphics/GraphicsDefinitions.hpp"
#include "../graphics/components/QuaternionObject.hpp"
#include <SFML/System.hpp>

/**
\file Grass.hpp
\brief Implementation file for Grass.cpp

\author Christopher Arausa
\date 05/14/2019
\version Final
*/

class Shader;
class Texture;
// So in theory we're going to take all teh points in our mesh above the Y value for grass, and then send them to the graphics card as points.
//Then turn them into blades in the geometry shader....

/**
\class GrassPatch
\brief The grass patch class is responsible for drawing grass on a single chunk */
class GrassPatch : QuaternionObject {
  private:
    GLint vPosition; ///< Shader position of vertex data.
    GLint vOffset; ///< Shader position of our offset.
    GLuint texture_0; ///< Shader uniform for texture.
    GLuint texture_1; ///< Shader uniform for texture.

    GLint vColor; ///< Shader position of vertex color.
    GLint vNormal; ///< Shader position of vertex normal.
    GLint vTexture; ///< Shader position of texture

    std::vector<Texture*> textures;
    std::vector<float> normals; ///< Vector containing vertex normals.
    std::vector<float> colors; ///< Vector containing the (r,g,b) color values for each vertice.
    std::vector<float> texture_uvs; ///< Vector containing our texture coordinates.
     Material material; ///< Our object's material.
    bool ready;
    GLuint VAO; ///< VAO
    GLuint vertex_buffer; ///< Vertices
    GLuint instance_buffer; ///< instance used for opengl instancing.
    GLuint uModel; ///< Shader uniform position of model matrix.
    bool useTexture; ///< Tracks whether we're using textures or just colors. Is used to set a uniform in our shader to toggle texure vs color rendering.
    bool lighting_on; ///< Determines if we apply lighting to this drawable.
    Shader* shader; ///< Shader the class uses
    std::vector<float> points; ///< Places in the world to draw the grass.
    std::vector<float> vertices; ///< Vertices of the object we're instancing.
    sf::Clock clock; ///< The clock used to oscilate the top.
  public:
    GrassPatch();
    ~GrassPatch();
    void setPoints(std::vector<float> p);
    void setShader(Shader* shader);
    void draw();
    void init();
    void setTexture(std::vector<Texture*> texts);
    void setChunkPos(int cx, int cz, int cs);
};
#endif
