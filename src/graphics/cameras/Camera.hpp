#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Shader.hpp"
#include "../components/SpacialObject.hpp"

enum CAMERA_TYPE {
  FREE,
  SPHERICAL
};
class Camera : virtual public SpacialObject {
  protected:
    CAMERA_TYPE type;

    float FoV; ///< Field of view.
    float clip_near;
    float clip_far;
    unsigned int height;
    unsigned int width;
    glm::mat4 view; ///< Our view matrix. We don't want to calculate this more than once a frame.
    glm::mat4 projection; ///< Our projection matrix. We don't want to calculate this more than once a frame.
  public:
    Camera(unsigned int width, unsigned int height, float FoV);
    virtual ~Camera();
    void setFOV(float fov);
    void setClipping(float near, float far);
    void applyUpdate(Shader *shader);
    glm::mat4 getView();
    glm::mat4 getProjection();
    void resize(unsigned int width, unsigned int height);
    void updateProjection();
    virtual void updateView() = 0;
    virtual void update() = 0;
    CAMERA_TYPE getType();
};

#endif
