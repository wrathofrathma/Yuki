#include "AssetManager.hpp"

using namespace std;
AssetManager::AssetManager(){

  asset_dir = "assets/";
  textures_dir = asset_dir + "textures/";
  shaders_dir = asset_dir + "shaders/";
}

//Loads all textures in the texture index file in ./textures/
void AssetManager::loadTextureIndex(){
  map<std::string, std::vector<std::string>> index_map;
  //Loading our index file.
  std::string index_path = textures_dir + "texture_index";
  ifstream file(index_path.c_str(), ifstream::in);
  if(!file.is_open()){
    cout << "Unable to open texture index." << endl;
    return;
  }
  //Load into our index map before loading each texture.
  vector<string> texture_types;
  string key, path, line, type;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    stringstream ss(line);
    ss >> type;
    texture_types.push_back(type);
    ss >> key;
    index_map.insert(pair<std::string, vector<std::string>>(key,std::vector<std::string>()));
    while(ss >> path){
      index_map[key].push_back(path);
    }
  }
  file.close();

  //Loading each texture.
  key.clear();
  path.clear();
  while(index_map.size()>0){

    key = index_map.begin()->first;
    path = index_map.begin()->second[0];

    if(index_map.begin()->second.size()==1){
      cout << "Loading texture " << key << endl;
      if(!loadTexture(index_map.begin()->second, key)){
        cout << "Failed to load texture [ " << key << " , " << path << " ]" << endl;
      }
    }
    else if(index_map.begin()->second.size()>1){
      cout << "Loading CubeMap texture " << key << endl;
      if(!loadTexture(index_map.begin()->second, key)){
        cout << "Failed to load texture [ " << key << " , " << path << " ]" << endl;
      }
    }
    index_map.erase(index_map.begin());
  }
  cout << "Loaded " << textures.size() << " textures." << endl;
}

//Loads all textures in the index index file in ./shaders/
void AssetManager::loadShaderIndex(){
  map<std::string, std::string> index_map;
  //Loading our index file.
  std::string shader_index_path = shaders_dir + "shader_index";
  ifstream file(shader_index_path, ifstream::in);
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
      vs_path = shaders_dir + vs_path;
      fs_path = shaders_dir + fs_path;
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

bool AssetManager::loadTexture(std::vector<std::string> filenames, std::string key){
  //Check if already loaded.
  if(textures.count(key) > 0)
    return true;
  Texture *t;
  for(unsigned int i=0; i<filenames.size(); i++){
    filenames[i] = textures_dir + filenames[i];
  }
  if(filenames.size()==1)
    t = new Texture(filenames[0]);
  else
    t = new Texture(filenames);

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
