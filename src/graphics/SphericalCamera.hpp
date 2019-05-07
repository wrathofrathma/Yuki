#ifndef SPHERICALCAMERA_H
#define SPHERICALCAMERA_H

//#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Camera.hpp"
#include "GraphicsDefinitions.hpp"

/**
\file SphericalCamera.hpp

\brief Header file for SphericalCamera.cpp

\author    Christopher Arausa
\version   1.2
\date      05/07/2019

*/

/**
\class SphericalCamera

\brief Creates a spherical camera, that is, one that sits on a sphere of radius r and always
points to the origin.

*/

class SphericalCamera : public Camera {
  private:
    float r;      ///< Radius of camera to origin.
    float theta;  ///< Theta rotation on the xz plane counter clockwise from positive x axis.
    float psi;    ///< Psi rotation from the xz plane to radial.

  public:
    SphericalCamera(unsigned int width, unsigned int height, float FoV);
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

    void update();
    void updateView();
  };

#endif
