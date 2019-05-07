#version 330 core

//Point lights have a position in the world and radiate light in all directions.
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

//Spot lights have both a position in the world, and a direction.
struct SpotLight{
  bool on;
  vec4 direction; ///< Direction the light is shining.
  vec4 position; ///< Position of the light.
  vec4 ambient; ///< Ambient color of the light.
  vec4 diffuse; ///< Diffuse color of the light.
  vec4 specular; ///< Specular color of the light.
  float cutOff; ///< Cutoff angle used to determine if our fragment is inside of our lit area.
  float outerCutOff;
  float constant; ///< Attenuation constant
  float linear; ///< Attenuation linear term
  float quadratic; ///< Attenuation quadratic term
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
in vec3 tex_coord; ///< Texture coordinates.

out vec4 FragColor; ///< Our resulting color.

uniform samplerCube cubeMap; ///< Cubemap texture.
uniform bool useTexture; ///< Boolean value that determines if we render the texture.
uniform vec3 camera_pos; ///< Camera position.
uniform Material material; ///< Material of the surface.

#define NR_POINT_LIGHTS 10 ///< Preprocessor directive containing the total number of point lights possible in a scene.
#define NR_DIRECTIONAL_LIGHTS 10  ///< Preprocessor directive containing total number of directional lights possible in a scene.
#define NR_SPOT_LIGHTS 10 ///< Preprocessor directive containing total number of spot lights possible in a scene.
uniform PointLight pointLights[NR_POINT_LIGHTS]; ///< C style array of point lights.
uniform DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS]; ///< C style array of directional lights.
uniform SpotLight spotLights[NR_SPOT_LIGHTS]; ///< C style array of spot lights.

//Takes in a point light structure, vector normal, fragment position, view direction, and color.
vec4 CalcPointLight(PointLight light, vec3 norm, vec4 fragPos, vec3 viewDir){
  vec3 lightDirection = normalize(light.position.xyz - fragPos.xyz);
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
  vec3 lightDirection = normalize(-light.direction.xyz);
  //Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);
  //Specular1
  vec3 reflectDir = reflect(-lightDirection.xyz, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec4 ambient  = light.ambient  * material.ambient;
  vec4 diffuse  = light.diffuse  * diff * material.diffuse;
  vec4 specular = light.specular * spec * material.specular;
  return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 norm, vec4 fragPos, vec3 viewDir){
  vec3 lightDirection = normalize(light.position.xyz - fragPos.xyz);
  //Diffuse
  float diff = max(dot(norm, lightDirection.xyz), 0.0);
  //Specular.
  vec3 reflectDirection = reflect(-lightDirection.xyz, norm);
  float spec = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);
  //Attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  //Spotlight intensity
  float theta = dot(lightDirection, normalize(-light.direction.xyz));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

  vec4 ambient  = light.ambient  * material.ambient;
  vec4 diffuse  = light.diffuse  * diff * material.diffuse;
  vec4 specular = light.specular * spec * material.specular;

  ambient *= attenuation * intensity;
  diffuse *= attenuation * intensity;
  specular *= attenuation * intensity;
  return (ambient + diffuse + specular);
}

void main()
{
  vec3 norm = normalize(normal);
  vec3 viewDirection = normalize(camera_pos - frag_pos.xyz);
  vec4 result = vec4(0.0);

  for(int i=0; i<NR_DIRECTIONAL_LIGHTS; i++){
    if(directionalLights[i].on)
      result+=CalcDirectionalLight(directionalLights[i], norm, viewDirection);
  }
  for(int i=0; i<NR_POINT_LIGHTS; i++){
    if(pointLights[i].on)
      result+=CalcPointLight(pointLights[i],norm,frag_pos,viewDirection);
  }
  for(int i=0; i<NR_SPOT_LIGHTS; i++){
    if(spotLights[i].on)
      result+=CalcSpotLight(spotLights[i], norm,frag_pos,viewDirection);
  }
  FragColor = texture(cubeMap, tex_coord);
}
