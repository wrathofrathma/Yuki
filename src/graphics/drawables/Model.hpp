#ifndef MODEL_HPP
#define MODEL_HPP

#include "../Material.hpp"
#include "../components/Drawable.hpp"
/**
\file Model.hpp
\brief Header file for Model.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class Model
\brief Skeleton class for the future when we combine multiple meshes for one object.
*/
class Model : public Drawable {
  private:

  public:
    Model(AssetManager *asset_manager);
    Model(Model &m1);

    void draw();
};
#endif
