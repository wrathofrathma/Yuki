#ifndef SPHERICALCAMERA_H
#define SPHERICALCAMERA_H

//#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Camera.hpp"
#include "../GraphicsDefinitions.hpp"
#include "../components/OrbitalObject.hpp"

/**
\file SphericalCamera.hpp

\brief Header file for SphericalCamera.cpp

\author    Christopher Arausa
\version   0.1
\date      05/07/2019

*/

/**
\class SphericalCamera

\brief Creates a camera that inherits the orbital object property. Meaning it sits on a sphere of radius r and always
points to the origin. 
*/

class SphericalCamera : public Camera, public OrbitalObject {
  private:

  public:
    SphericalCamera(unsigned int width, unsigned int height, float FoV);

    void update();
    void updateView();
  };

#endif
