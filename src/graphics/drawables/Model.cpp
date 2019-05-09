#include "Model.hpp"

/**
\file Model.cpp
\brief Implementation of the Model class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/

/**
\brief Constructor

Default constructor that just calls the superclass and passes the asset manager.
\param asset_manager --- AssetManager class pointer.
*/
Model::Model(AssetManager *asset_manager) : Drawable(asset_manager){

}
/**
\brief Copy Constructor
*/
Model::Model(Model &m1) : Drawable(m1.getAssetManager()){

}

/**
\brief Draws the model.
*/
void Model::draw(){

}
