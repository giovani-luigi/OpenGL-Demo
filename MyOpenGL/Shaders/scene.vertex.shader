#version 400

struct PointLight {
    float decayConstant;    // decay constant coefficient 
    float decayLinear;      // decay linear coefficient 
    float decayQuadratic;   // decay quadratic coefficient 
    vec3 position;          // position must be in view space
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout(location=0) in vec4 i_pos;	// vertex position
layout(location=1) in vec4 i_norm;	// vertex normal
layout(location=2) in vec2 i_text;	// vertex texture's coordinate

uniform mat4 u_model;				// model transformation
uniform mat4 u_view;				// camera (view) matrix
uniform mat4 u_proj;				// projection matrix
uniform PointLight u_light;			// point light parameters

out vec3 frag_pos;					// output: position in view's space
out vec3 frag_norm;					// output: normal in view's space
out vec2 frag_text;					// output: texture coordinate

void main() {
	// apply model and view transformations, but not perspective
	frag_pos =  vec3(u_view * u_model * vec4(i_pos.xyz, 1.0f));
	frag_norm = normalize(vec3(u_view * u_model * vec4(i_norm.xyz, 0.0f)));
	// forward coordinates for texture sampler 
	frag_text = i_text;
	// transform all vertices
	gl_Position = u_proj * u_view * u_model * vec4(i_pos.xyz, 1.0f); // WARNING!!! ORDER MATTERS
}
