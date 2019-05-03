#include "AssetManager.hpp"

using namespace std;
AssetManager::AssetManager(){


}

//Loads all textures in the texture index file in ./textures/
void AssetManager::loadTextureIndex(){
  map<std::string, std::string> index_map;
  //Loading our index file.
  ifstream file("./textures/texture_index", ifstream::in);
  if(!file.is_open()){
    cout << "Unable to open texture index." << endl;
    return;
  }
  //Load into our index map before loading each texture.
  string key, path, line;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    stringstream ss(line);
    ss >> key;
    ss >> path;
    index_map.insert(pair<std::string, std::string>(key,path));
  }
  file.close();

  //Loading each texture.
  key.clear();
  path.clear();
  while(index_map.size()>0){
    key = index_map.begin()->first;
    path = index_map.begin()->second;
    cout << "Loading texture [ " << key << " , " << path << " ]" << endl;
    if(!loadTexture(path, key)){
      cout << "Failed to load texture [ " << key << " , " << path << " ]" << endl;
    }
    index_map.erase(index_map.begin());
  }
  cout << "Loaded " << textures.size() << " textures." << endl;
  cout << "|"<<textures.begin()->first << "|" << endl;
}

//Loads all textures in the index index file in ./shaders/
void AssetManager::loadShaderIndex(){
  map<std::string, std::string> index_map;
  //Loading our index file.
  ifstream file("shaders/shader_index", ifstream::in);
  if(!file.is_open()){
    cout << "Unable to open shader index." << endl;
    return;
  }
  //Load into our index map before loading each shader.
  string key, vs_path, fs_path, line;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    cout << line << endl;
    stringstream ss(line);
    ss >> key;
    ss >> vs_path;
    ss >> fs_path;
    if(shaders.count(key)==0){
      cout << "Loading shader " << key << " [ " << vs_path << " | " << fs_path << " ]"<< endl;
      Shader *shader = new Shader(vs_path, fs_path);
      if(!shader->isLoaded()){
        cout << "Couldn't load shader: " << key << endl;
        delete shader;
      }
      else{
        shaders.insert(pair<std::string, Shader*>(key, shader));
      }
    }
  }
  file.close();
  cout << "Loaded " << shaders.size() << " shaders." << endl;
}
AssetManager::~AssetManager(){
  // Clean up textures
  while(!textures.empty()){
    std::map<std::string, Texture*>::iterator it = textures.begin();
    Texture *t = it->second;
    textures.erase(it);
    delete t;
  }
  // Clean up shaders
  while(!shaders.empty()){
    std::map<std::string, Shader*>::iterator sit = shaders.begin();
    Shader *s = sit->second;
    shaders.erase(sit);
    delete s;
  }
}

bool AssetManager::loadTexture(std::string filename, std::string key){
  //Check if already loaded.
  if(textures.count(key) > 0)
    return true;
  Texture *t = new Texture(filename);

  if(t->isLoaded()){
    textures.insert(std::pair<std::string, Texture*>(key, t));
    return true;
  }
  else{
    delete t;
    return false;
  }
}

Texture* AssetManager::getTexture(std::string key){
  std::map<std::string, Texture*>::iterator it = textures.find(key);
  if(it!=textures.end())
    return (it->second);
  return nullptr;
}

Shader* AssetManager::getShader(std::string key){
  if(shaders.count(key)==0){
    Shader *s = new Shader(key);
    if(!s->isLoaded()){
      delete s;
      return nullptr;
    }
    shaders.insert(pair<std::string, Shader*>(key, s));
    return s;
  }
  return shaders[key];
}
