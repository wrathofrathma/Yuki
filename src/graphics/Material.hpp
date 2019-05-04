#ifndef YUKI_MATERIAL_HPP
#define YUKI_MATERIAL_HPP
#include <glm/glm.hpp>

class Material {
  private:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 emission;
    float shininess;

  public:
    Material(glm::vec4 a, glm::vec4 d, glm::vec4 s, glm::vec4 e, float shininess);
    ~Material();

    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    glm::vec4 getEmission();
    float getShininess();
    void setAmbient(glm::vec4 a);
    void setDiffuse(glm::vec4 d);
    void setSpecular(glm::vec4 s);
    void setEmission(glm::vec4 e);
    void setShininess(float sh);
};

#endif
