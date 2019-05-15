#version 420 core
/**
\file Default.fs

\brief Default fragment shader.

\param [in] frag_pos --- vec4 fragmentx position.

\param [in] color --- vec3 vertex color.

\param [in] normal --- vec3 normal vector.

\param [in] tex_coord --- vec3 texture coordinates.

\param [out] FragColor --- vec4 output color to the frame buffer.

\param [uniform] pointLights --- PointLight struct array, each indice containing a single point light attribute set

\param [uniform] directionalLights --- DirectionalLight struct array, each indice containing a single directional  light attribute set

\param [uniform] spotLights --- SpotLight struct array, each indice containing a single spot light attribute set

\param [uniform] material --- Material struct containing a single material attribute set.

\param [uniform] camera_pos --- vec3 position of the viewer/camera.

\param [uniform] global_ambient --- vec4 global ambient color vector.

*/

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
  bool on; ///< Light on or off?
  vec4 direction; ///< Direction the light is shining.
  vec4 position; ///< Position of the light.
  vec4 ambient; ///< Ambient color of the light.
  vec4 diffuse; ///< Diffuse color of the light.
  vec4 specular; ///< Specular color of the light.
  float cutOff; ///< Cutoff angle used to determine if our fragment is inside of our lit area.
  float outerCutOff; ///< outerCutOff angle.
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
in vec2 tex_coord;
in vec4 clipspace; ///< Texture coordinates.

out vec4 FragColor; ///< Our resulting color.

uniform sampler2D texture1; ///< Reflection texture
uniform sampler2D texture2; ///< Refraction texture
uniform sampler2D texture3; ///< dudv map
uniform sampler2D texture4; ///< Water texture
uniform bool useTexture; ///< Boolean value that determines if we render the texture.
uniform vec3 camera_pos; ///< Camera position.
uniform Material material; ///< Material of the surface.

#define NR_POINT_LIGHTS 10 ///< Preprocessor directive containing the total number of point lights possible in a scene.
#define NR_DIRECTIONAL_LIGHTS 10  ///< Preprocessor directive containing total number of directional lights possible in a scene.
#define NR_SPOT_LIGHTS 10 ///< Preprocessor directive containing total number of spot lights possible in a scene.
uniform PointLight pointLights[NR_POINT_LIGHTS]; ///< C style array of point lights.
uniform DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS]; ///< C style array of directional lights.
uniform SpotLight spotLights[NR_SPOT_LIGHTS]; ///< C style array of spot lights.
uniform vec4 global_ambient; ///< Global ambient for the scene.
uniform bool lighting_on; ///< Whether we're applying lighting calculation to the scene.
uniform float dudv_offset; ///< Dudv offset that controls where we sample.
uniform float time;
uniform bool apply_distortion; ///< Do we apply distortion to our water.

void main()
{
  // This is the strength of our distortion. By changing this we can achieve a ripple effect.
  // We want to clamp it fairly low though. Between 0.0 to 0.2 maybe. So using a sin function we can add 1 and divide by 100

  float strength = 0.1;
  //float strength = 0.1;
  vec2 normaldevice = clipspace.xy / clipspace.w;
  normaldevice /= 2.0;
  normaldevice+=0.5;

  vec2 refract_uvs = vec2(normaldevice.x, normaldevice.y);
  vec2 reflect_uvs = vec2(normaldevice.x, -normaldevice.y);


  if(apply_distortion){
  vec2 dudv_distortion = texture(texture3, vec2(tex_coord.x, tex_coord.y)).rg*2.0-1.0;
    dudv_distortion *= strength;
    refract_uvs+=dudv_distortion;
    reflect_uvs+= dudv_distortion;
  }
  refract_uvs = clamp(refract_uvs, 0.001,0.999);
  reflect_uvs.x = clamp(reflect_uvs.x, 0.001,0.999);
  reflect_uvs.y = clamp(reflect_uvs.y, -0.999,-0.001);

  vec4 reflect_color = texture(texture1, reflect_uvs);
  vec4 refract_color = texture(texture2, refract_uvs);

  FragColor = mix(reflect_color, refract_color, 0.5);
  FragColor = mix(FragColor, vec4(0,0.1,0.3,0),0.3);
  // if(useTexture)
  //   FragColor =  mix(texture(texture2, tex_coord), texture(texture1, vec2(normaldevice.x, -normaldevice.y)),0.7);
  // else
  //   FragColor = vec4(icolor,1);



  //
  // if(lighting_on){
  //   vec3 norm = normalize(normal);
  //   vec3 viewDirection = normalize(camera_pos - frag_pos.xyz);
  //   vec4 result = vec4(0.0);
  //
  //   for(int i=0; i<NR_DIRECTIONAL_LIGHTS; i++){
  //     if(directionalLights[i].on)
  //       result+=CalcDirectionalLight(directionalLights[i], norm, viewDirection);
  //   }
  //   for(int i=0; i<NR_POINT_LIGHTS; i++){
  //     if(pointLights[i].on)
  //       result+=CalcPointLight(pointLights[i],norm,frag_pos,viewDirection);
  //   }
  //   for(int i=0; i<NR_SPOT_LIGHTS; i++){
  //     if(spotLights[i].on)
  //       result+=CalcSpotLight(spotLights[i], norm,frag_pos,viewDirection);
  //   }
  //   result += material.ambient * global_ambient;
  //   result += material.emission;
  //   FragColor = FragColor * result;
  // }
}
