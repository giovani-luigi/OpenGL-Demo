#version 400

layout(location = 0) in vec3 i_pos;

uniform mat4 u_lightSpaceMatrix;    // transform vertex to the light point of view
uniform mat4 u_model;               // model transformation matrix

void main() {
    gl_Position = u_lightSpaceMatrix * u_model * vec4(i_pos, 1.0);
}