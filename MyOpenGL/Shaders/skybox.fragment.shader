#version 400

in vec3 frag_text; // input: texture coordinate

uniform samplerCube u_texture;

out vec4 frag_colour;

void main() {
    frag_colour = texture(u_texture, frag_text);
}