#ifndef YUKI_LIGHT_OBJECT
#define YUKI_LIGHT_OBJECT

#include "../Drawable.hpp"

class LightObject : public Drawable{
  private:

  public:
    LightObject(AssetManager *am);
    ~LightObject();

    void draw();
};

#endif
