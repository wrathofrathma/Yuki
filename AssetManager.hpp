#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Texture.hpp"
#include "Shader.hpp"
#include "GraphicsDefinitions.hpp"
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
    std::map<std::string, Shader*> shaders;
  public:
    AssetManager();
    ~AssetManager();

    Texture* getTexture(std::string key);
    bool loadTexture(std::vector<std::string> filenames, std::string key);
    void loadTextureIndex();
    void loadShaderIndex();
    Shader* getShader(std::string key);
};

#endif
