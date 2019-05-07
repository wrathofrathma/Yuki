#ifndef MODEL_HPP
#define MODEL_HPP

#include "../Material.hpp"
#include "../components/Drawable.hpp"

class Model : public Drawable {
  private:

  public:
    Model(AssetManager *asset_manager);
    Model(Model &m1);

    void draw();
};
#endif
