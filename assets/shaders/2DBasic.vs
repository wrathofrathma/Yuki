#version 330 core

layout(location = 0) in vec4 vpos;
layout(location = 1) in vec3 vnormal;
layout(location = 2) in vec3 vcolor;
layout(location = 3) in vec2 text_uv;

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix

out vec4 position;
out vec3 normal;
out vec4 color;
out vec2 tex_coord;

void main(){
  normal = mat3(transpose(inverse(model))) * vnormal;
  position = model * vpos;
  color = vec4(vcolor, 1.0f);
  tex_coord = text_uv;
  gl_Position = proj * view * model * vpos;
}
