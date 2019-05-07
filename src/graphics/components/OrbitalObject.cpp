#include "OrbitalObject.hpp"
/**
\brief Constructor

Position is at (1, 0, 0) pointing toward the origin.

*/

OrbitalObject::OrbitalObject() {
    r = 10;
    theta = 0;
    psi = 0;
}

/**
\brief Sets the position of the object

\param R --- Radius of object to origin.
\param Theta --- Theta rotation on the xz plane counter clockwise from positive x axis.
\param Psi --- Psi rotation from the xz plane to radial.

*/

void OrbitalObject::setPosition(float R, float Theta, float Psi) {
    r = R;
    theta = Theta;
    psi = Psi;
    position = glm::vec3(r*cos(psi*deg)*cos(theta*deg),r*sin(psi*deg),r*cos(psi*deg)*sin(theta*deg));
}

/**
\brief Adds to the object radius.

\param num --- amount to add to the radius of the object.

*/

void OrbitalObject::addR(float num) {
    r += num;
    if (r < 0.000001f) r = 0.000001f;
}

/**
\brief Adds to the theta angle of the object.

\param num --- amount to add to the theta angle of the object.

*/

void OrbitalObject::addTheta(float num) {
    theta += num;
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
}

/**
\brief Adds to the psi angle of the object.

\param num --- amount to add to the psi angle of the object.

*/

void OrbitalObject::addPsi(float num) {
    psi += num;
    if (psi > 90) psi = 90;
    if (psi < -90) psi = -90;
}

/**
\brief Sets the radius of the object.

\param num --- new value of the radius.

*/

void OrbitalObject::setR(float num) {
    r = num;
    if (r < 0.000001f) r = 0.000001f;
}

/**
\brief Sets the theta angle of the object.

\param num --- New value of the theta angle.

*/

void OrbitalObject::setTheta(float num) {
    theta = num;
    while (theta > 360) theta -= 360;
    while (theta < 0) theta += 360;
}

/**
\brief Sets the psi angle of the object.

\param num --- New value of the psi angle.

*/

void OrbitalObject::setPsi(float num) {
    psi = num;
    if (psi > 90) psi = 90;
    if (psi < -90) psi = -90;
}

/**
\brief Returns the current value of the object radius.

\return The current value of the object radius.

*/

float OrbitalObject::getR() {
    return r;
}

/**
\brief Returns the current value of the theta angle of the object.

\return The current value of the theta angle of the object.

*/

float OrbitalObject::getTheta() {
    return theta;
}

/**
\brief Returns the current value of the psi angle of the object.

\return The current value of the psi angle of the object.

*/

float OrbitalObject::getPsi() {
    return psi;
}
