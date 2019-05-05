#version 330 core


struct Light
{
    bool on;             ///< Light on or off.
    vec4 position;       ///< Position of the light.
    vec3 spotDirection;  ///< Direction of the spot light.
    vec4 ambient;        ///< Ambient color of the light.
    vec4 diffuse;        ///< Diffuse color of the light.
    vec4 specular;       ///< Specular color of the light.
};

struct Material
{
    vec4 ambient;     ///< Ambient color of the material.
    vec4 diffuse;     ///< Diffuse color of the material.
    vec4 specular;    ///< Specular color of the material.
    vec4 emission;    ///< Emission color of the material.
    float shininess;  ///< Shininess exponent of the material.
};

in vec4 position;
in vec4 color;
in vec3 normal;
in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;
uniform Light light;

void main()
{
  vec3 norm = normalize(normal);
  vec3 lightdir = normalize(light.position - position).xyz;
  float diff = max(dot(norm, lightdir), 0.0);
  vec4 diffuse = diff * light.diffuse;
  if(useTexture)
    FragColor =  texture(texture1, tex_coord);
  else
    FragColor = color;
  FragColor = (light.ambient + diffuse) * min(FragColor, vec4(1.0));
}
