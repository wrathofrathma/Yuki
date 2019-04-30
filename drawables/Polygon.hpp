#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "../Drawable.hpp"
#include "../Shader.hpp"
#include "../GraphicsDefinitions.hpp"
#include "../Texture.hpp"
#include <vector>
#include <iostream>

using namespace std;

class Polygon : public Drawable {
private:
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

  Shader shader;
  Texture *texture;
  GLuint VAO;
  GLuint indicePtr;
  GLuint dataPtr;

  GLuint TEX;
  bool useTexture;
  bool update;
  public:
    Polygon();
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
