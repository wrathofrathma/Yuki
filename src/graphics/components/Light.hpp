#ifndef YUKI_LIGHT_HPP
#define YUKI_LIGHT_HPP

#include "QuaternionObject.hpp"
#include "../Shader.hpp"

enum LIGHT_TYPE {
  POINT,
  DIRECTIONAL,
  SPOT
};

class Light : virtual public QuaternionObject {
  protected:
    bool on; ///< Light on or off.
    glm::vec4 ambient; ///< Ambient color of the light.
    glm::vec4 diffuse; ///< Diffuse color of the light.
    glm::vec4 specular; ///< Specular color of the light.
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
    LIGHT_TYPE type;
  public:

    Light();
    //Directional constructor
    Light(bool onoff, glm::vec4 dir, glm::vec4 a, glm::vec4 d, glm::vec4 s);
    //Point constructor
    Light(bool onoff, glm::vec4 pos, glm::vec4 a, glm::vec4 d, glm::vec4 s, float c, float l, float q);
    //Generic
    Light(LIGHT_TYPE t, bool onoff, glm::vec4 a, glm::vec4 d, glm::vec4 s);
    Light(LIGHT_TYPE t);
    ~Light();

    bool getOn();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    float getConstant();
    float getLinear();
    float getQuadratic();
    LIGHT_TYPE getType();
    void setType(LIGHT_TYPE t);
    void setConstant(float c);
    void setLinear(float l);
    void setQuadratic(float q);
    void setOn(bool onoff);
    void setAmbient(glm::vec4 a);
    void setDiffuse(glm::vec4 d);
    void setSpecular(glm::vec4 s);
    void setCutOff(float c);
    void setOuterCutOff(float oc);
    float getCutOff();
    float getOuterCutOff();
    static void setOff(Shader *s, unsigned int i, LIGHT_TYPE type);
    void loadToShader(Shader *s, unsigned int i);
};

#endif
