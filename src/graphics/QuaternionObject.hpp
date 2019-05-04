#ifndef QUATERNION_OBJECT_HPP
#define QUATERNION_OBJECT_HPP
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
\file QuaternionObject.hpp
\brief Header file for QuaternionObject.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/2/2019

*/

/**
\class QuaternionObject
\brief The QuaternionObject class repesents any object in 2D or 3D space. And a utility function for generating a model matrix.
*/

class QuaternionObject {

  protected:
    glm::vec3 orientation;
    glm::vec3 position;
    glm::vec3 current_scale;

    glm::mat4 model_matrix;
  public:
    QuaternionObject();
    ~QuaternionObject();
    void rotate(glm::vec3 rotation);
    void translate(glm::vec3 offset, bool relative=true);
    void scale(glm::vec3 delta);
    glm::mat4 getRotationMatrix();
    glm::quat getRotationQuat();
    glm::mat4 generateModelMatrix();
    glm::vec3 getXAxis();
    glm::vec3 getYAxis();
    glm::vec3 getZAxis();
    void setPosition(glm::vec3 pos);
    glm::vec3 getPosition();
};
#endif
