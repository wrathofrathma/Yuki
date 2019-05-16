#version 420
/**
\file Grass.fs
\brief Grass fragment shader.

\author Christopher Arausa
\date 05/15/2019
\version Final

\param [in] usetexture --- Boolean for whether to apply a texture to the grass.

\param [in] texture_0 --- Texture for the grass

\param [in] texture_1 --- Another grass texture

\param [in] tex_coord --- vec2 texture coordinates for the grass.

\param [out] FragColor --- vec4 containing the final color of the grass.

*/
out vec4 FragColor;

uniform bool useTexture;
uniform sampler2D texture_0;
uniform sampler2D texture_1;

in vec2 tex_coord;

void main ()
{
  // texture_1;
  if(useTexture){
    vec4 tc = texture(texture_0, tex_coord);
    if(tc.a < 0.1)
      discard;
    if(tex_coord.y < 0.1)
      tc = mix(tc, vec4(0.07,0.678,0.1647,1.0), (tex_coord.y - 0.1));
    FragColor = tc;
  }
  else
    FragColor = vec4(0.07,0.678,0.1647,1.0);
}
