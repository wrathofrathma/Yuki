#version 330 core

/**
\file PassThroughFrag.glsl

\brief Simple pass through fragment shader.

This is a simple GLSL pass through fragment shader.

\param [in] color --- vec4 color from vertex shader.

*/

in vec4 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;

void main()
{
  if(useTexture)
    FragColor = texture(texture1, TexCoord);
  else
    FragColor = color;
  FragColor = min(FragColor, vec4(1.0));
}
