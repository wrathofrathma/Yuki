#include "Shader.hpp"
/**
\file Shader.cpp
\brief Implementation of the Shader class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/


/**
\brief Constructor

Default constructor. Only sets loaded to false.
*/
Shader::Shader(){
  loaded=false;
}
/**
\brief Constructor

Attempts to load the file by filename by appending .vs and .fs to the file path.
\param filename --- File path of the shader to append to and load.
*/
Shader::Shader(const std::string &filename){
  loadFromFile(filename);
}
/**
\brief Constructor

Attempts to load the file paths for both the passed vertex and fragment shader.
\param vert --- Vertex shader location
\param frag --- Fragment shader location
*/
Shader::Shader(std::string &vert, std::string &frag){
  loadFromFile(vert, frag);
}
/**
\brief Destructor

Releases shader memory on the graphics card.
*/
Shader::~Shader(){
  for(unsigned int i = 0; i < NUM_SHADER; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

/**
\brief Appends .vs and .fs to the passed file path and attempts to load them.
\param filename --- File path of the shaders to load.
*/
void Shader::loadFromFile(std::string filename){
  std::string vert = filename + ".vs";
  std::string frag = filename + ".fs";
  loadFromFile(vert, frag);
}

/**
\brief Returns the uniform location of a given id in the shader.
\param name --- ID of the uniform to find the location of.
*/
GLuint Shader::getUniformLocation(const std::string &name){
  return glGetUniformLocation(m_program, name.c_str());
}
/**
\brief Returns the uniform location of common uniforms we preload from the shader.
*/
GLuint Shader::getUniformLocation(UNIFORM_ID type){
  switch(type){
    case MODEL:
      return m_uniforms[MODEL];
    case VIEW:
      return m_uniforms[VIEW];
    case PROJECTION:
      return m_uniforms[PROJECTION];
  }
  return 0;
}

/**
\brief Loads a shader from the vertex and fragment filepaths and returns the program ID.
\param vert --- File path of the vertex shader.
\param frag --- File path of the fragment shader.
*/
GLuint Shader::loadFromFile(std::string &vert, std::string &frag){
  m_program = glCreateProgram();
  m_shaders[0] = createShader(loadShader(vert), GL_VERTEX_SHADER);
  m_shaders[1] = createShader(loadShader(frag), GL_FRAGMENT_SHADER);

  for(unsigned int i = 0; i < NUM_SHADER; i++){
    glAttachShader(m_program, m_shaders[i]);
  }

  glLinkProgram(m_program);
  loaded = checkShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program.");
  if(loaded){
    //Setup uniforms.
    m_uniforms[0] = getUniformLocation("model");
    m_uniforms[1] = getUniformLocation("view");
    m_uniforms[2] = getUniformLocation("proj");
  }
  return m_program;
}

/**
\brief Checks the shader for errors, typically called after creation to discover if there was a compilation error.

Returns true if no error exists,  false if one does exist.
\param shader --- Shader ID of the shader to check.
\param flag --- Flag to check for problems.
\param isProgram --- Marks if the shader is already a program in memory.
\param errorMessage --- The error message to display if our shader flag is false.
*/
bool Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if(isProgram)
      glGetProgramiv(shader, flag, &success);
  else
      glGetShaderiv(shader, flag, &success);
  if(success == GL_FALSE){
    if(isProgram)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);
    std::cerr << errorMessage << ": " << error << std::endl;
    return false;
  }
  return true;
}
/**
\brief Creates a shader from the passed text string and type of shader.

Returns a shader ID.
\param text --- The total file data loaded into a string.
\param type --- GLenum of the type of shader.
*/
GLuint Shader::createShader(const std::string &text, GLenum type){
  GLuint shader = glCreateShader(type);

  if(shader == 0)
    std::cerr << "Error compiling shader type " << type << std::endl;

  const GLchar* p[1];
  p[0] = text.c_str();
  GLint lengths[1];
  lengths[0] = text.length();

  glShaderSource(shader, 1, p, lengths);
  glCompileShader(shader);

  checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

  return shader;
}
/**
\brief Loads shader data from the file into a text string.

Returns the string containing all of the file data.
\param filename --- String containing the file path to load.
*/
std::string Shader::loadShader(const std::string& filename){
  std::ifstream file;
  file.open((filename).c_str());

  std::string output;
  std::string line;

  if(file.is_open()){
    while(file.good()){
      getline(file, line);
      output.append(line + "\n");
    }
  }
  else{
    std::cerr << "Unable to load shader: " << filename << std::endl;
  }
  return output;
}

/**
\brief Utility function to bind the shader.
*/
void Shader::bind(){
  glUseProgram(m_program);
}

/**
\brief Returns if the shader has loaded successfully.
*/
bool Shader::isLoaded(){
  return loaded;
}
/**
\brief Sets a boolean uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);
}
/**
\brief Sets an integer uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}
/**
\brief Sets a float uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}
/**
\brief Sets a vec3 uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setVec3(const std::string &name, glm::vec3 &value) const
{
  glUniform3f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z);
}
/**
\brief Sets a vec4 uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setVec4(const std::string &name, glm::vec4 &value) const
{
  glUniform4f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z, value.w);
}
/**
\brief Sets a mat4 uniform value in the shader.
\param name --- Name or ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setMat4(const std::string &name, glm::mat4 &value) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
/**
\brief Sets a boolean uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setBool(GLuint uniformLocation, bool value){
  glUniform1i(uniformLocation, (int)value);
}
/**
\brief Sets an integer uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setInt(GLuint uniformLocation, int value){
  glUniform1i(uniformLocation, value);
}
/**
\brief Sets a float uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setFloat(GLuint uniformLocation, float value){
  glUniform1f(uniformLocation, value);
}
/**
\brief Sets a vec3 uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setVec3(GLuint uniformLocation, glm::vec3 &value){
  glUniform3f(uniformLocation, value.x, value.y, value.z);
}
/**
\brief Sets a vec4 uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setVec4(GLuint uniformLocation, glm::vec4 &value){
  glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}
/**
\brief Sets a mat4 uniform value in the shader.
\param uniformLocation --- ID of the uniform in the shader to set.
\param value --- New value of the uniform.
*/
void Shader::setMat4(GLuint uniformLocation, glm::mat4 &value){
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}
