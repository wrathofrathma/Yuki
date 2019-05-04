#include "LightObject.hpp"

LightObject::LightObject(AssetManager *am) : Drawable(am) {
  shader = am->getShader("Light");
}

LightObject::~LightObject(){

}

void LightObject::draw(){

}
