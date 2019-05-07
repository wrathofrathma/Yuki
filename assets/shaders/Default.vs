#version 330 core

layout(location = 0) in vec4 vpos;
layout(location = 1) in vec3 vnormal;
layout(location = 2) in vec3 vcolor;
layout(location = 3) in vec2 text_uv;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix

out vec4 frag_pos; ///< Our vertex position in model coordinates.
out vec3 normal; ///< Our vertex normal.
out vec3 icolor; ///< Our input surface color if one exists.
out vec2 tex_coord; ///< Texture coordinates.

void main(){
  normal = mat3(transpose(inverse(model))) * vnormal; ///We need to remove this soon. We'll do the update in initDraw() function of drawable.
  frag_pos = model * vpos; // Converting to world position.
  icolor = vcolor;
  tex_coord = text_uv;
  gl_Position = proj * view * model * vpos;
}
