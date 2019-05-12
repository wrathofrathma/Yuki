#version 420 core
layout (points) in; //We take in points and output line strips.
layout (triangle_strip, max_vertices = 24) out; //We'll output a 3 segment line strip with a seed, middle and top.

uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 proj; // Projection matrix
uniform float time;
out vec2 tex_coord;

const float speed = 1.0;


float random (vec2 st) {
    return fract(sin(dot(st.xy,
      vec2(12.9898,78.233)))* 43758.5453123);
}
//Generates a very basic quad with textures.
void GenerateQuad(vec4 seed) {

  //Amount we'll scale up in size.
  vec4 scale = vec4(5);
  vec4 wave = vec4(0.02,0.001,0.02,0) * sin(time * speed);
  //vec4 wave = vec4(0);
  //We need to create a quad with 12 vertices at our seed position.
  vec4 center = seed;
  vec4 b_left = seed - vec4(0.5,0,0,0) * scale;
  vec4 b_right = seed + vec4(0.5,0,0,0) * scale;
  vec4 t_left = b_left + (wave + vec4(0,3,0,0)) * scale;
  vec4 t_right = b_right + (wave+ vec4(0,3,0,0)) * scale;

  tex_coord = vec2(0,0);
  gl_Position = b_left;
  EmitVertex();
  tex_coord = vec2(1,0);
  gl_Position = b_right;
  EmitVertex();
  tex_coord = vec2(1,1);
  gl_Position = t_right;
  EmitVertex();
  tex_coord = vec2(0,1);
  gl_Position = t_left;
  EmitVertex();
  // gl_Position = seed;
  // EmitVertex();
  // vec4 mid = seed + vec4(0.0, 1.0, 0.0, 1.0);
  // vec4 tip = mid +  vec4(0.0, 1.0, 0.0, 1.0);
  // gl_Position = mid;
  // EmitVertex();
  // gl_Position = tip;
  // EmitVertex();
  EndPrimitive();
}

void main() {
  int num_blades = 8; //Power of 2 number of blades/quads geneated from a single see
  vec4 scale = vec4(5); // Our size scale.
  //Let's generate our unit square.
  // vec4 center = gl_in[0].gl_Position;
  // vec4 bl = center + vec4(-1, -1, 0, 0);
  // vec4 br = center + vec4(1, -1, 0, 0);
  // vec4 tl = bl + vec4(0, 1, 0, 0);
  // vec4 tr = br + vec4(0,1, 0, 0);
  // for(int i=0; i<sqrt(num_blades); i++){
  //   for(int j=0; j<sqrt(num_blades); j++){
  //
  //   }
  // }
  // vec4 center = gl_in[0].gl_Position;
  // vec4 bl = center + vec4(-1, -1, 0, 0)*scale;
  // vec4 br = center + vec4(1, -1, 0, 0)*scale;
  // vec4 tl = bl + vec4(0, 1, 0, 0)*scale;
  // vec4 tr = br + vec4(0,1, 0, 0)*scale;
  // GenerateQuad(center);
  // GenerateQuad(bl);
  // GenerateQuad(br);
  // GenerateQuad(tl);
  // GenerateQuad(tr);
  vec4 center = gl_in[0].gl_Position;
  vec4 bl = center + vec4(-1, -0.25, -1, 0)*scale;
  vec4 br = center + vec4(1, -0.25, -1, 0)*scale;
  vec4 tl = bl + vec4(0, -0.25, 1, 0)*scale;
  vec4 tr = br + vec4(0,-0.25, 1, 0)*scale;
  GenerateQuad(center);
  GenerateQuad(bl);
  GenerateQuad(br);
  GenerateQuad(tl);
  GenerateQuad(tr);
}
