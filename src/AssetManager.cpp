#include "AssetManager.hpp"
#include "Yuki.hpp"
#include "graphics/GraphicsEngine.hpp"

/**
\file AssetManager.cpp
\brief Implementation of AssetManager class for loading and distributing shared resources.

\author Christopher Arausa
\version 0.1
\date 5/8/2019
*/
using namespace std;

/**
\brief Constructor

Base constructor, it just sets our asset, texture, and shaders directory. Later on we'll probably load this from a config file.
*/
AssetManager::AssetManager(Yuki* yuki){
  this->yuki = yuki;
  asset_dir = "assets/";
  textures_dir = asset_dir + "textures/";
  shaders_dir = asset_dir + "shaders/";
  refr_h = 720;
  refr_w = 1280;
  refl_h = 1280;
  refl_w = 720;
}

/**
\brief Returns the yuki game engine pointer.
*/
Yuki* AssetManager::getYuki(){
  return yuki;
}

//Loads all textures in the texture index file in ./textures/
/**
\brief Loads all of the textures in our texture index file.
*/
void AssetManager::loadTextureIndex(){
  map<std::string, std::vector<std::string>> index_map;
  map<std::string, bool> alpha_map;
  //Loading our index file.
  std::string index_path = textures_dir + "texture_index";
  ifstream file(index_path.c_str(), ifstream::in);
  if(!file.is_open()){
    cout << "Unable to open texture index." << endl;
    return;
  }
  //Load into our index map before loading each texture.
  vector<string> texture_types;

  string key, path, line, type,alpha;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    stringstream ss(line);
    ss >> type;
    texture_types.push_back(type);
    ss >> alpha;
    ss >> key;

    if(alpha.compare("a")==0){
      alpha_map.insert(make_pair(key, true));
    }
    else{
      alpha_map.insert(make_pair(key, false));
    }
    index_map.insert(pair<std::string, vector<std::string>>(key,std::vector<std::string>()));
    while(ss >> path){
      index_map[key].push_back(path);
    }
  }
  file.close();

  //Loading each texture.
  key.clear();
  path.clear();
  int indice = 0;
  while(index_map.size()>0){

    key = index_map.begin()->first;
    path = index_map.begin()->second[0];

    if(index_map.begin()->second.size()==1){
      cout << "Loading texture " << key << endl;
      if(!loadTexture(index_map.begin()->second, key, alpha_map[key])){
        cout << "Failed to load texture [ " << key << " , " << path << " ]" << endl;
      }
    }
    else if(index_map.begin()->second.size()>1){
      cout << "Loading CubeMap texture " << key << endl;
      if(!loadTexture(index_map.begin()->second, key, alpha_map[key])){
        cout << "Failed to load texture [ " << key << " , " << path << " ]" << endl;
      }
    }
    index_map.erase(index_map.begin());
    indice++;
  }
  cout << "Loaded " << textures.size() << " textures." << endl;
}

/**
\brief Loads all of the shaders in our shader index file.
*/
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
  string key, vs_path, fs_path, line, gs_path;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    stringstream ss(line);
    ss >> key;
    ss >> vs_path;
    ss >> fs_path;
    if(!ss.eof())
      ss >> gs_path;
    else
      gs_path=="";
    if(shaders.count(key)==0){
      cout << "Loading shader " << key << " [ " << vs_path << " | " << fs_path << " | " << gs_path << " ]"<< endl;
      vs_path = shaders_dir + vs_path;
      fs_path = shaders_dir + fs_path;
      if(gs_path.size()>0)
        gs_path = shaders_dir + gs_path;
      Shader *shader = new Shader(vs_path, fs_path, gs_path);
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

/** Destructor

Deletes all stored textures and shaders and releases the memory used for them.
*/
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
  glDeleteFramebuffers(1,&reflection_framebuffer);
  glDeleteFramebuffers(1,&refraction_framebuffer);
  glDeleteRenderbuffers(1,&reflection_depthbuffer);

  glDeleteTextures(1,&reflection_texture);
  glDeleteTextures(1,&refraction_texture);
  glDeleteTextures(1,&refraction_depthtex);
}

/**
\brief Loads textures passed by filename and stores them based on the passed key.

\param filenames --- Vector of filenames to load and associate with this texture.
\param key --- Key string to use as a key in our map index of textures.
*/
bool AssetManager::loadTexture(std::vector<std::string> filenames, std::string key, bool alpha){
  //Check if already loaded.
  if(textures.count(key) > 0)
    return true;
  Texture *t;
  for(unsigned int i=0; i<filenames.size(); i++){
    filenames[i] = textures_dir + filenames[i];
  }

  if(filenames.size()==1)
    t = new Texture(filenames[0],alpha);
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

/**
\brief Returns the texture associated with the key passed.
\param key --- Key to lookup in our texture map.
*/
Texture* AssetManager::getTexture(std::string key){
  std::map<std::string, Texture*>::iterator it = textures.find(key);
  if(it!=textures.end())
    return (it->second);
  if(textures.size()>0)
    return textures[0];
  return nullptr;
}
/**
\brief Returns the Shader associated with the key passed.
\param key --- Key to lookup in our Shader map.
*/
Shader* AssetManager::getShader(std::string key){
  if(shaders.count(key)==0){
    return nullptr;
  }
  return shaders[key];
}

  /**
  \brief Returns the current shader map.
  */
std::map<std::string, Shader*> AssetManager::getShaders(){
  return shaders;
}

void AssetManager::init_fbs(){
  refraction_framebuffer = createFrameBuffer();
  refraction_texture = createTextureAttachment(refr_w, refr_h);
  refraction_depthtex = createDepthBufferAttachment(refr_w, refr_h);

  reflection_framebuffer = createFrameBuffer();
  reflection_texture = createTextureAttachment(refl_w, refl_h);
  reflection_depthbuffer = createDepthBufferAttachment(refl_w, refl_h);

}


GLuint AssetManager::createFrameBuffer(){
  GLuint framebuffer;
  glGenFramebuffers(1,&framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
  glDrawBuffer(GL_COLOR_ATTACHMENT0);
  return framebuffer;
}

GLuint AssetManager::createTextureAttachment(int w, int h){
  GLuint tex;
  glGenTextures(1,&tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w,h,0,GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);
  return tex;
}
GLuint AssetManager::createDepthTextureAttachment(int w, int h){
  GLuint depth_tex;
  glGenTextures(1, &depth_tex);
  glBindTexture(GL_TEXTURE_2D,depth_tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w,h,0,GL_DEPTH_COMPONENT, GL_FLOAT, (void*)0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_tex, 0);
  return depth_tex;
}
void AssetManager::unbindFB(){
  unsigned int w = yuki->ge->getSize().x;
  unsigned int h = yuki->ge->getSize().y;
  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glViewport(0,0,w,h);
}

void AssetManager::bindReflectionFB(){
  bindFramebuffer(reflection_framebuffer, refl_w, refl_h);
}
void AssetManager::bindRefractionFB(){
  bindFramebuffer(refraction_framebuffer, refr_w, refr_h);
}
GLuint AssetManager::createDepthBufferAttachment(int w, int h){
  GLuint depth_buffer;
  glGenRenderbuffers(1,&depth_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);
  return depth_buffer;
}

void AssetManager::bindFramebuffer(GLuint fb, int w, int h){
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, fb);
  glViewport(0, 0, w,h);
}
