#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix

void main(){
  gl_Position = proj * view * model * position; 
}
