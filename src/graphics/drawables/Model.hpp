#ifndef MODEL_HPP
#define MODEL_HPP

#include "../Material.hpp"
#include "../Drawable.hpp"

class Model : public Drawable {
  private:

  public:
    Model(AssetManager *asset_manager);
    Model(Model &m1);
    
    void draw();
    void updateGraphicsCard();
};
#endif
