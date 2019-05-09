#ifndef ORBITAL_LIGHT_HPP
#define ORBITAL_LIGHT_HPP

#include "../components/Light.hpp"
#include "../components/OrbitalObject.hpp"
/**
\file OrbitalLight.hpp
\brief Header file for OrbitalLight.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class OrbitalLight
\brief A convenience class for combining the Light component class with OrbitalObject component class for lights that revolve/orbit the origin.
*/
class OrbitalLight : public Light, public OrbitalObject {
  public:
    OrbitalLight();
    ~OrbitalLight();
};

#endif
