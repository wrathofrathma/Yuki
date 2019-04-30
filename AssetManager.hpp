#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Texture.hpp"

/**
\file AssetManager.hpp
\brief header file for AssetManager.cpp

\author Christopher Arausa
\version 0.1
\date 4/20/2019

*/

/**
\class AssetManager

\brief The AssetManager class handles loading and distributing all shared resources.

*/

class AssetManager {
  private:
    std::map<std::string, Texture*> textures;
  public:
    AssetManager();
    ~AssetManager();

    Texture* getTexture(std::string key);
    void loadTexture(std::string filename, std::string key);


};

#endif
