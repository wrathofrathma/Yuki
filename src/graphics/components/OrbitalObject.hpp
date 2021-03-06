#ifndef ORBITAL_OBJECT_HPP
#define ORBITAL_OBJECT_HPP

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../GraphicsDefinitions.hpp"
#include "SpacialObject.hpp"
/**
\file OrbitalObject.hpp
\brief Header file for OrbitalObject.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class OrbitalObject
\brief The OrbitalObect class is a component class for any spacial object that moves by rotating around the origin, changing its radius from the origin. It is always oriented towards the origin.
*/
class OrbitalObject : virtual public SpacialObject{
  protected:
    float r;      ///< Radius of camera to origin.
    float theta;  ///< Theta rotation on the xz plane counter clockwise from positive x axis.
    float psi;    ///< Psi rotation from the xz plane to radial.

  public:
    OrbitalObject();
    void setPosition(float R, float Theta, float Psi);

    void addR(float num);
    void addTheta(float num);
    void addPsi(float num);

    void setR(float num);
    void setTheta(float num);
    void setPsi(float num);

    float getR();
    float getTheta();
    float getPsi();

    glm::mat4 getFacing();
};

#endif
