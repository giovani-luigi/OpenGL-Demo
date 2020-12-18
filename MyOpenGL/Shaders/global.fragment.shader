//
// This fragment shader implements 2 light sources:
//  1. Directional (moon)
//  2. Spotlight (flashlight held at first person)
//

#version 400

struct Light {
    vec3 direction;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//in vec3 vertex_posicao_cam, vertex_normal_cam;
        
out vec4 frag_colour;

void main () {
    frag_colour = vec4(1.0, 0.8, 0.8, 1.0); // mainLight() + flashLight();
}