
#include "../Drawable.hpp"
#include "../Shader.hpp"
#include "../GraphicsDefinitions.hpp"
#include <vector>
#include <iostream>

using namespace std;

class Polygon : public Drawable {
private:
  GLint vPosition; ///< Shader position of vertex data.
  GLint vColor; ///< Shader position of vertex color.
  GLint vNormal; ///< Shader position of vertex normal.

  GLfloat* vertex_data;  ///< Pointer to the vertex data.

  unsigned int vertex_count; ///< Total number of vertices in the object.
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  std::vector<float> colors; ///< Vector containing the (r,g,b) color values for each vertice.

  Shader shader;

  GLuint VAO;
  GLuint EBO;
  GLuint VBO;
  GLuint TEX;
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

};
