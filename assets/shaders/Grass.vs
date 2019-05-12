#version 420
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 offset;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix


void main()
{
  gl_Position = proj * view * model * (vertex_position*2);
}
