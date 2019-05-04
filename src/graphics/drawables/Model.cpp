#include "Model.hpp"

Model::Model(AssetManager *asset_manager) : Drawable(asset_manager){
 
}

Model::Model(Model &m1) : Drawable(m1.getAssetManager()){

}

void Model::draw(){

}
