#version 330 core

/**
\file PassThroughVert.glsl

\brief Simple pass through vertex shader.

This is a simple GLSL pass through vertex shader.

\param [in] icolor --- vec4 color from vertex array.

\param [in] position --- vec4 position from vertex array.

\param [out] color --- vec4 output color to the fragment shader.

*/

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 icolor;
layout(location = 2) in vec2 iTextureCoord;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix

out vec4 color;
out vec2 TexCoord;

void main(){
  color = vec4(icolor, 1.0f);
  TexCoord = iTextureCoord;
  //gl_Position = position;
  gl_Position = proj * view * model * position;
}
