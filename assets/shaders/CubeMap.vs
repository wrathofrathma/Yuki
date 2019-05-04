#version 330 core
layout(location = 0) in vec4 vposition;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix

out vec3 TexCoord;

void main(){
  TexCoord = vposition.xyz;
  gl_Position = proj * view * model * vposition;
}
