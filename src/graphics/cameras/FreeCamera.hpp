#ifndef FREE_CAMERA_HPP
#define FREE_CAMERA_HPP

#include "../components/QuaternionObject.hpp"
#include "Camera.hpp"

class FreeCamera : public QuaternionObject, public Camera {
  public:
    FreeCamera(unsigned int width, unsigned int height, float FoV);
    ~FreeCamera();
    void updateView();
    void update();
};

#endif
