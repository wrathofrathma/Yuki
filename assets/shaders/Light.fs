#version 330 core
// We need a separate light shader for the things that emit light. So they're not impacted by other lighting changes.

out vec4 FragColor;
in vec4 color;
in vec2 tex_coord;

uniform sampler2D texture1;
uniform bool useTexture;

void main(){
  if(useTexture)
    FragColor =  texture(texture1, tex_coord);
  else
    FragColor = color;
  FragColor = min(FragColor, vec4(1.0));
}
