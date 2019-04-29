#version 330 core

/**
\file PassThroughVert.glsl

\brief Simple pass through vertex shader.

This is a simple GLSL pass through vertex shader.

\param [in] icolor --- vec4 color from vertex array.

\param [in] position --- vec4 position from vertex array.

\param [out] color --- vec4 output color to the fragment shader.

*/

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 icolor;

out vec4 color;

void main(){
  color = vec4(icolor, 1.0f);

  gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
