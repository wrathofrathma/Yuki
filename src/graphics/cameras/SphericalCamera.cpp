#include "SphericalCamera.hpp"

/**
\file SphericalCamera.cpp

\brief Implementation file for the SphericalCamera class.

\author    Christopher Arausa
\version   1.2
\date      05/07/2019

*/

/**
\brief Constructor

Position is at (1, 0, 0) pointing toward the origin.

*/

SphericalCamera::SphericalCamera(unsigned int width, unsigned int height, float FoV) : Camera(width,height,FoV) {
    type = SPHERICAL;

    updateView();
}



/**
\brief Updates the view matrix for the current position and line of sight to the origin.
*/

void SphericalCamera::updateView() {
    glm::vec3 eye = glm::vec3(r*cos(psi*deg)*cos(theta*deg),r*sin(psi*deg),r*cos(psi*deg)*sin(theta*deg));
    glm::vec3 center = glm::vec3(0, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);
    view = glm::lookAt(eye, center, up);
}

/**
\brief Function called every draw cycle to update the camera values
*/

void SphericalCamera::update() {
  updateView();
}
