#version 330 core

in vec4 color;
in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;

void main()
{
  float ambientStrength = 0.10;
  if(useTexture)
    FragColor =  texture(texture1, tex_coord);
  else
    FragColor = color;
  FragColor = ambientStrength * min(FragColor, vec4(1.0));
}
