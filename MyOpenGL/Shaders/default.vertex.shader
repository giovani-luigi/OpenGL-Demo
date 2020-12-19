#version 400

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

layout(location=0) in vec4 i_pos;	// vertex position
layout(location=1) in vec4 i_norm;	// vertex normal

uniform mat4 u_model;				// model transformation
uniform mat4 u_view;				// camera (view) matrix
uniform mat4 u_proj;				// projection matrix
uniform PointLight u_light;			// point light parameters

out vec3 v_pos;						// output: vertex position in view's space
out vec3 v_norm;					// output: vertex normal in view's space

void main() {
	// apply model and view transformations, but not perspective
	v_pos =  vec3(u_view * u_model * vec4(i_pos.xyz, 1.0f));
	v_norm = normalize(vec3(u_view * u_model * vec4(i_norm.xyz, 0.0f)));
	// apply all transformations
	gl_Position = u_proj * u_view * u_model * vec4(i_pos.xyz, 1.0f); // WARNING!!! ORDER MATTERS
}
