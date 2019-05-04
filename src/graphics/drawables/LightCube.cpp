#include "LightCube.hpp"

LightCube::LightCube(AssetManager *am) : Cube(am) {
  setShader("Light");
  update = true;
}
LightCube::~LightCube(){

}
