#version 400

layout(location = 0) in vec4 i_pos;		// vertex position

uniform mat4 u_model;				// model transformation
uniform mat4 u_view;				// camera (view) matrix
uniform mat4 u_proj;				// projection matrix

out vec3 frag_text;					// output: texture coordinate

void main() {

	vec4 v_pos = u_proj * u_view * u_model * vec4(i_pos.xyz, 1.0f); // WARNING!!! ORDER MATTERS
	
	gl_Position = v_pos.xyww; // this keeps the model behind all other vertices
	
	// we use the original position in object space as the 3D texture coordinate. 
	// This makes sense because the way sampling from the cubemap works is by shooting 
	// a vector from the origin through a point in the box or sphere. So the position 
	// of the point actually becomes the texture coordinate. The vertex shader passes 
	// the object space coordinate of each vertex as the texture coordinate (8 vertices 
	// in the case of a cube and probably much more for a sphere) and it gets interpolated 
	// by the rasterizer for each pixel. This gives us the position of the pixel which we 
	// can use for sampling.
	frag_text = normalize(i_pos.xyz);
}
