#include "AssetManager.hpp"
#include <iostream>
using namespace std;
AssetManager::AssetManager(){

}

AssetManager::~AssetManager(){
  // Clean up textures
  while(!textures.empty()){
    std::map<std::string, Texture*>::iterator it = textures.begin();
    Texture *t = it->second;
    textures.erase(it);
    delete t;
  }
}

void AssetManager::loadTexture(std::string filename, std::string key){
  //Check if already loaded.
  if(textures.count(key) > 0)
    return;
  Texture *t = new Texture(filename);

  if(t->isLoaded())
    textures.insert(std::pair<std::string, Texture*>(key, t));
  else
    delete t;
}

Texture* AssetManager::getTexture(std::string key){
  std::map<std::string, Texture*>::iterator it = textures.find(key);
  if(it!=textures.end())
    return (it->second);
  return nullptr;
}
