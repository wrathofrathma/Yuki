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
\struct ShaderInfo

\brief Structure that holds shader information.

*/

typedef struct
{
    GLenum type;  ///< Type of shader, GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...
    const char* filename;  ///< Filename of shader code file, if loading from a file. Set to "" if loading from memory.
    const std::string code; ///< Code string of shader code, if loading from memory. Set to "" (or ignore) if loading from a file.
    GLuint shader; ///< Output storage for glCreateShader function, not needed as input from user.
} ShaderInfo;

/**
\class Shader

\brief The Shader class handles the loading, and toggling usage of a specific shader.

*/
class Shader {
  private:
    Shader(const Shader& other) {}
    void operator=(const Shader& other) {}

    static const unsigned int NUM_SHADER = 2;
    static const unsigned int NUM_UNIFORM = 1;
    GLuint m_program; ///< Shader program ID.
    GLuint m_shaders[NUM_SHADER]; ///< Array containing our vertex & fragment shaders.
    GLuint m_uniforms[NUM_UNIFORM];

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

    GLuint loadFromFile(std::string &vert, std::string &frag);
};
#endif
