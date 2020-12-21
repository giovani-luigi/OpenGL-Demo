#version 400

in vec3 v_text; // input: vertex texture coordinate

uniform samplerCube u_texture;

out vec4 frag_colour;

void main() {
    frag_colour = texture(u_texture, v_text);
}