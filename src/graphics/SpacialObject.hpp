#ifndef SPACIAL_OBJECT_HPP
#define SPACIAL_OBJECT_HPP
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4



class SpacialObject {
  protected:
    glm::vec3 position;
    glm::vec3 orientation;
  public:
    SpacialObject();
    glm::vec3 getPosition();
    glm::vec3 getOrientation();
    void setPosition(glm::vec3 pos);
    void setOrientation(glm::vec3 o);

};

#endif
