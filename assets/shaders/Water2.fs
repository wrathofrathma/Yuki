#version 420 core


in vec4 frag_pos; ///< Fragment position
in vec3 icolor; ///< Input surface color, if it exists.
in vec3 normal; ///< Vertex normal.
in vec4 clipspace; ///< Texture coordinates.

out vec4 FragColor; ///< Our resulting color.

uniform sampler2D texture1; ///< Texture to use if we're using one.
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform bool useTexture; ///< Boolean value that determines if we render the texture.
uniform vec3 camera_pos; ///< Camera position.


uniform vec4 global_ambient; ///< Global ambient for the scene.
uniform bool lighting_on; ///< Whether we're applying lighting calculation to the scene.


// float fresnel(vec3 to_camera, float fresnel_reflection){
// 	vec3 view_vector = normalize(to_camera);
// 	vec3 norm = normalize(normal);
// 	float refraction = dot(view_vector, normal);
// 	refaction = pow(refraction, fresnel_reflection);
// 	return clamp(refraction, 0.0,1.0);
// }

vec2 clipspaceConversion(vec4 cs){
	vec2 ndc = (cs.xy  / cs.w);
	vec2 texture_coords = ndc / 2.0 + 0.5;
	return texture_coords;
}
void main()
{
	vec4 water_color = vec4(0.604, 0.867, 0.851, 1);
	float fresnel_reflection = 0.5;
	vec3 to_camera = normalize(camera_pos - frag_pos.xyz);

	vec2 text_coords = clipspaceConversion(clipspace);

	vec2 reflection_coords = vec2(text_coords.x, 1.0-text_coords.y);
	vec4 reflection_texture = texture(texture3, reflection_coords);

	// vec4 total = mix (texture2, texture3, fresnel(to_camera, fresnel_reflection));
	FragColor = reflection_texture;





}
