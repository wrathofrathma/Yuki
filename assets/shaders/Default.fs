#version 330 core

//Point lights have a position in the world,
struct PointLight {
    bool on;             ///< Light on or off.
    float constant; ///< Attenuation constant
    float linear; ///< Attenuation linear term
    float quadratic; ///< Attenuation quadratic term
    vec4 position;       ///< Position of the light.
    vec4 ambient;        ///< Ambient color of the light.
    vec4 diffuse;        ///< Diffuse color of the light.
    vec4 specular;       ///< Specular color of the light.
};

//Directional lights will be things that are too far away for position to matter, so we'll only calculate direction.
//Things like sunlight.
struct DirectionalLight {
  bool on; ///< Light on or off?
  vec4 direction; ///< Direction the light is shining.
  vec4 ambient; ///< Ambient color of the light.
  vec4 diffuse; ///< Diffuse color of the light.
  vec4 specular; ///< Specular color of the light.
};

//Materials determine how our surface fragment reacts to our lighting.
struct Material {
    vec4 ambient;     ///< Ambient color of the material.
    vec4 diffuse;     ///< Diffuse color of the material.
    vec4 specular;    ///< Specular color of the material.
    vec4 emission;    ///< Emission color of the material.
    float shininess;  ///< Shininess exponent of the material.
};

in vec4 frag_pos; ///< Fragment position
in vec3 icolor; ///< Input surface color, if it exists.
in vec3 normal; ///< Vertex normal.
in vec2 tex_coord; ///< Texture coordinates.

out vec4 FragColor; ///< Our resulting color.

uniform sampler2D texture1; ///< Texture to use if we're using one.
uniform bool useTexture; ///< Boolean value that determines if we render the texture.
uniform vec3 camera_pos; ///< Camera position.
uniform Material material; ///< Material of the surface.


//Takes in a point light structure, vector normal, fragment position, view direction, and color.
vec4 CalcPointLight(PointLight light, vec3 norm, vec4 fragPos, vec3 viewDir){
  vec4 lightDirection = normalize(light.position - fragPos);
  //Diffuse
  float diff = max(dot(norm, lightDirection.xyz), 0.0);
  //Specular.
  vec3 reflectDirection = reflect(-lightDirection.xyz, norm);
  float spec = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);
  //Attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec4 ambient  = light.ambient  * material.ambient;
  vec4 diffuse  = light.diffuse  * diff * material.diffuse;
  vec4 specular = light.specular * spec * material.specular;
  ambient  *= attenuation;
  diffuse  *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}

vec4 CalcDirectionalLight(DirectionalLight light, vec3 norm, vec3 viewDir){
  vec4 lightDirection = normalize(-light.direction);
  //Diffuse
  float diff = max(dot(normal, lightDirection.xyz), 0.0);
  //Specular1
  vec3 reflectDir = reflect(-lightDirection.xyz, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec4 ambient  = light.ambient  * material.ambient;
  vec4 diffuse  = light.diffuse  * diff * material.diffuse;
  vec4 specular = light.specular * spec * material.specular;
  return (ambient + diffuse + specular);
}

#define NR_POINT_LIGHTS 10 ///< Preprocessor directive containing the total number of point lights possible in a scene.
#define NR_DIRECTIONAL_LIGHTS 10  ///< Preprocessor directive containing total number of directional lights possible in a scene.
#define NR_SPOT_LIGHTS 10 ///< Preprocessor directive containing total number of spot lights possible in a scene.
uniform PointLight pointLights[NR_POINT_LIGHTS]; ///< C style array of point lights.
uniform DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS]; ///< C style array of directional lights.

void main()
{
  vec3 norm = normalize(normal);
  vec3 viewDirection = normalize(camera_pos - frag_pos.xyz);
  vec4 result = vec4(0);
  for(int i=0; i<NR_DIRECTIONAL_LIGHTS; i++){
    result+=CalcDirectionalLight(directionalLights[i], norm, viewDirection);
  }
  for(int i=0; i<NR_POINT_LIGHTS; i++){
    result+=CalcPointLight(pointLights[i],norm,frag_pos,viewDirection);
  }
  //Initialize our color object based on whether we're using a texture or not.

  if(useTexture)
    FragColor =  texture(texture1, tex_coord);
  else
    FragColor = vec4(icolor,1);
  FragColor =  FragColor * result;
}
