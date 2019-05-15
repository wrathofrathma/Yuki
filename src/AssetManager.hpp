#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"
#include "graphics/GraphicsDefinitions.hpp"
#include "graphics/ObjModel.hpp"
class Yuki;
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

It handles loading shaders and textures, as well as frontloading them on startup using shader and texture index files in our asset directory.

*/

class AssetManager {
  private:
    std::map<std::string, Texture*> textures; ///< A map of our loaded textures and their key value used throughout the engine.
    std::map<std::string, Shader*> shaders; ///< A map of our loaded shaders and their key value used throughout the engine.
    std::string asset_dir; ///< Our asset directory.
    std::string shaders_dir; ///< Our shaders directory
    std::string textures_dir; ///< Our textures directory
    Yuki *yuki; ///< Yuki game engine pointer.



    GLuint reflection_framebuffer;
    GLuint refraction_framebuffer;
    GLuint reflection_depthbuffer;
    GLuint refraction_depthtex;
    GLuint createFrameBuffer();
    GLuint createTextureAttachment(int w, int h);
    GLuint createDepthTextureAttachment(int w, int h);
    GLuint createDepthBufferAttachment(int w, int h);
    void bindFramebuffer(GLuint fb, int w, int h);
    unsigned int refl_h;
    unsigned int refl_w;
    unsigned int refr_h;
    unsigned int refr_w;
  public:
    AssetManager(Yuki *yuki);
    ~AssetManager();
    Yuki* getYuki();
    Texture* getTexture(std::string key);
    bool loadTexture(std::vector<std::string> filenames, std::string key, bool alpha);
    void loadTextureIndex();
    void loadShaderIndex();
    Shader* getShader(std::string key);
    std::map<std::string, Shader*> getShaders();
    void bindReflectionFB();
    void bindRefractionFB();
    void init_fbs();
    void unbindFB();
    GLuint reflection_texture;
    GLuint refraction_texture;

};

#endif
