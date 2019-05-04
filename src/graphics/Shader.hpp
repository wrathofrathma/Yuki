#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
/**
\file Shader.hpp
\brief header file for Shader.cpp

\author Christopher Arausa
\version 0.1
\date 4/20/2019

*/





/**
\class Shader

\brief The Shader class handles the loading, and toggling usage of a specific shader.

*/
class Shader {
  private:
    Shader(const Shader& other) {}
    void operator=(const Shader& other) {}

    static const unsigned int NUM_SHADER = 2;
    GLuint m_program; ///< Shader program ID.
    GLuint m_shaders[NUM_SHADER]; ///< Array containing our vertex & fragment shaders.

    GLuint createShader(const std::string &text, GLenum type);
    std::string getShaderString(GLenum);
    static std::string loadShader(const std::string& filename);
    bool checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    bool loaded;
  public:
    Shader();
    Shader(const std::string &filename);
    Shader(std::string &vert, std::string &frag);
    ~Shader();
    void bind();
    bool isLoaded();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    GLuint loadFromFile(std::string &vert, std::string &frag);
    void loadFromFile(std::string filename);
    GLuint getUniformLocation(const std::string &name);
};
#endif
