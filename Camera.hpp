#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

enum Direction {
  UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};

class Camera {
  private:
    GLuint uView; ///< Uniform variable storing location of shader view matrix
    GLuint uProj; ///< Uniform variable storing location of shader projection matrix
    float FoV; ///< Field of view.

    glm::vec3 camera_up; ///< current up vector.
    glm::vec3 camera_position; ///< Camera position in 3D space.
    glm::vec3 camera_lookat; ///< Place we're looking at.
    float clip_near;
    float clip_far;
    unsigned int height;
    unsigned int width;

    float camera_pitch;

  public:
    Camera(GLuint uProj, GLuint uView, unsigned int width, unsigned int height, float FoV);
    ~Camera();
    void resize(unsigned int width, unsigned int height);
    void updateProjection();
    void updateView();
    void update();
    void setPosition(glm::vec3);
    void setFOV(float fov);
    void setClipping(float near, float far);

};

#endif
