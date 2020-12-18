#version 400

layout(location=0) in vec4 pos;
//layout(location=1) in vec4 norm;

uniform mat4 model;   // model transformation
uniform mat4 view;  // camera (view) matrix
uniform mat4 proj;    // projection matrix

//out vec4 cam_rel_pos cam_rel_norm;

void main() {
   //cam_rel_pos = view * trans * vec4(pos.xyz, 1.0f);
   //cam_rel_norm = view * trans * vec4(pos.xyz, 0.0f);
   gl_Position = proj * view * model * vec4(pos.xyz, 1.0f); // WARNING!!! ORDER MATTERS
}
