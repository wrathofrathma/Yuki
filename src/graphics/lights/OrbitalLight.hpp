#ifndef ORBITAL_LIGHT_HPP
#define ORBITAL_LIGHT_HPP

#include "../components/Light.hpp"
#include "../components/OrbitalObject.hpp"

class OrbitalLight : public Light, public OrbitalObject {
  public:
    OrbitalLight();
    ~OrbitalLight();
};

#endif
