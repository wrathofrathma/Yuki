#include "Shader.hpp"

Shader::Shader(){
  loaded=false;
}
Shader::Shader(const std::string &filename){
  std::string vert = filename + ".vs";
  std::string frag = filename + ".fs";
  loadFromFile(vert, frag);
}
Shader::Shader(std::string &vert, std::string &frag){
  loadFromFile(vert, frag);
}
Shader::~Shader(){
  for(unsigned int i = 0; i < NUM_SHADER; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

GLuint Shader::loadFromFile(std::string &vert, std::string &frag){
  m_program = glCreateProgram();
  m_shaders[0] = createShader(loadShader(vert), GL_VERTEX_SHADER);
  m_shaders[1] = createShader(loadShader(frag), GL_FRAGMENT_SHADER);

  for(unsigned int i = 0; i < NUM_SHADER; i++){
    glAttachShader(m_program, m_shaders[i]);
  }

  glLinkProgram(m_program);
  loaded = checkShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program.");
  // m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	// m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	// m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
  return m_program;
}


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

void Shader::bind(){
  glUseProgram(m_program);
}

bool Shader::isLoaded(){
  return loaded;
}
