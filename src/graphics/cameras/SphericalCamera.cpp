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

*/
SphericalCamera::SphericalCamera(unsigned int width, unsigned int height, float FoV) : Camera(width,height,FoV) {
    type = SPHERICAL;
    updateView();
}

/**
\brief Updates the view matrix for the current position and line of sight to the origin.
*/
void SphericalCamera::updateView() {
    view = getFacing();
}

/**
\brief Function called every draw cycle to update the camera values
*/
void SphericalCamera::update() {
  updateView();
}
