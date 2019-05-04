#ifndef YUKI_LIGHT_HPP
#define YUKI_LIGHT_HPP

#include "QuaternionObject.hpp"
#include "Shader.hpp"

class Light : virtual public QuaternionObject {
  protected:
    bool on; ///< Light on or off.
    glm::vec4 ambient; ///< Ambient color of the light.
    glm::vec4 diffuse; ///< Diffuse color of the light.
    glm::vec4 specular; ///< Specular color of the light.
  public:
    Light();
    Light(bool onoff, glm::vec3 pos, glm::vec3 facing, glm::vec4 a, glm::vec4 d, glm::vec4 s);
    ~Light();

    bool getOn();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    void setOn(bool onoff);
    void setAmbient(glm::vec4 a);
    void setDiffuse(glm::vec4 d);
    void setSpecular(glm::vec4 s);
    void setLight(bool onoff, glm::vec3 pos, glm::vec3 facing, glm::vec4 a, glm::vec4 d, glm::vec4 s);
    void loadToShader(Shader *shader, unsigned int i);
};

#endif
