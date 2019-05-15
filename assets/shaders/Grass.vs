#version 420
/**
\file Grass.vs

\brief Grass vertex shader.

\param [in] vertex_position --- vec4 vertex position.

\param [in] model --- mat4 Model matrix.

\param [in] view --- mat4 View matrix.

\param [in] proj --- mat4 Projection matrix.

\param [in] offset --- vec4 offset
*/

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 offset;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix
uniform vec4 plane;


void main()
{
  gl_ClipDistance[0] = dot(model * vertex_position,plane);
  gl_Position = proj * view * model * (vertex_position*2);
}
