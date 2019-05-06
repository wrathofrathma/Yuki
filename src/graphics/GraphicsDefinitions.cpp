#include "GraphicsDefinitions.hpp"
/**
\brief Prints all OpenGL errors to stderr.

*/
using namespace std;
void printOpenGLErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR)
    {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error: %s\n", errString);
    }
}
glm::vec3 calcSurfaceNormal(std::vector<glm::vec3> vertices){
  glm::vec3 normal = glm::vec3(0.0f);

  glm::vec3 current = glm::vec3(0.0f);
  glm::vec3 next = glm::vec3(0.0f);

  for(unsigned int i = 0; i < vertices.size() - 1; i++){
    current = vertices[i];
    next = vertices[i+1];
    normal.x+= (current.y - next.y) * (current.z + next.z);
    normal.y+= (current.z - next.z) * (current.x + next.x);
    normal.z+= (current.x - next.x) * (current.y + next.y);
  }
  return glm::normalize(normal);
}
