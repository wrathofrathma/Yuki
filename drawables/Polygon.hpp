#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "../Drawable.hpp"
#include "../Shader.hpp"
#include "../GraphicsDefinitions.hpp"
#include "../Texture.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value ptr
#include <vector>
#include <iostream>

using namespace std;

class Polygon : public Drawable {
  protected:

  //GLuint uModel; ///< Shader uniform position of model matrix.
  glm::mat4 modelMatrix; ///< This individual model's matrix.

  GLint vPosition; ///< Shader position of vertex data.
  GLint vColor; ///< Shader position of vertex color.
  GLint vNormal; ///< Shader position of vertex normal.
  GLint vTexture; ///< Shader position of texture
  GLfloat* vertex_data;  ///< Pointer to the vertex data.

  unsigned int vertex_count; ///< Total number of vertices in the object.
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  std::vector<float> colors; ///< Vector containing the (r,g,b) color values for each vertice.
  std::vector<float> texture_coords; ///< Vector containing our texture coordinates.

  Texture *texture;
  GLuint VAO;
  GLuint indicePtr;
  GLuint dataPtr;

  Shader *shader;

  GLuint TEX;
  bool useTexture;
  bool update;
  public:
    Polygon(AssetManager *am);
    ~Polygon();

    void draw();
    GLuint const getVAO();
    unsigned int getVertexCount();
    void setColor(float r, float g, float b);
    void setColor(std::vector<float> c);
    void loadVertices(vector<float> _vertices, vector<unsigned int> _indices);
    void updateGraphicsCard();
    void storeDataInAttributeList(int attributeNumber, float *data);
    void setTexture(Texture *tex);
    void setUseTexture(bool use);

};
#endif
