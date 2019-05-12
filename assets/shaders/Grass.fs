#version 420
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
