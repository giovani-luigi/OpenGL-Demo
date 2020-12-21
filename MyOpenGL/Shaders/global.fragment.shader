#version 400

struct Material {
    bool has_texture;   // flag the indicates when a texture is loaded.
    sampler2D texture_unit;
    vec3 specular;      // amount of specular reflection
    vec3 diffuse;       // amount of diffuse reflection
    vec3 ambient;       // amount of ambient reflection
    float shininess;    // used for specular component
};

struct PointLight {
    vec3 position;      // position must be in view space
    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;      // position must be in view space
    vec3 direction;
    float aperture;
};

in vec3 v_pos;                    // vertex position in view space
in vec3 v_norm;                   // vertex normal in view space
in vec2 v_text;                   // vertex texture coordinates

uniform mat4 u_view;              // view matrix (camera)
uniform Material u_material;      // material reflection parameters
uniform PointLight u_light;       // point light emission parameters
uniform SpotLight u_flashlight;   // spot light emission parameters


out vec4 frag_color;

// calculates the color when using a point light.
vec3 point_light(PointLight light, Material material) 
{

    // 1. ambient component
    //      simulates a light far far away, that is coming from all angles
    vec3 ambient_component = light.ambient * material.ambient;
    
    // 2. diffuse component
    //      independent from camera's position, basically is the light reflected from the light source
    //      depending on the fragment surface's angle with the light source.

    // calculate a vector coming from the fragment, going to the light
    vec3 light_direction = normalize(light.position - v_pos);
    // calculate the angle between the fragments normal, and the vector from the fragment to the light source.
    // the smaller the angle, the more orthogonal the fragment is to the light, then, the more light is reflected.
    float cos_diffuse = dot(v_norm, light_direction); // we need the cosine directly...
    // modulate the light intensity (light reflected = light source * material reflection) using the cosine from above
    vec3 diffuse_component = light.diffuse * material.diffuse * cos_diffuse;

    // 3. specular: 
    //      calculated with the angle between the camera, and the light vector that bounced in the surface 
    //      coming from the light source. This generates a highlight giving a shine to the surface depending on 
    //      how you look to it.
    
    // calculate the vector reflected by the surface, after being bounced (around the normal) from the light source:
    // flip the vector from the fragment to the light, so it is a vector coming from the light to the fragment's surface
    // then reflect that vector, around the fragment's normal
    vec3 reflected_light = reflect(-light_direction, v_norm);
    // now we need a vector coming from fragment's surface, going to the camera
    vec3 frag_to_camera_vec = normalize(-v_pos);

    // find the angle formed between the vector of the reflected light, and the vector frag--->cam
    float cos_specular = dot(reflected_light, frag_to_camera_vec);

    // optimization, skip calculation if no specular component is required (which in most of the time, its most of the fragments)
    // also, ignore negative numbers of cossine
    vec3 specular_component = vec3(0.0, 0.0, 0.0);
    if (cos_specular > 0.0) { 
        float specular_coefficient = pow(cos_specular, material.shininess);
        specular_component = light.specular * material.specular * specular_coefficient;
    }    
    
    if (u_material.has_texture) {
        vec3 text_color = vec3(texture(u_material.texture_unit, v_text));
        ambient_component *= text_color;
        diffuse_component *= text_color;
        specular_component *= text_color;
    }

    return (ambient_component + diffuse_component + specular_component);
    
}

vec3 spot_light(SpotLight light, Material material) 
{
    return vec3(0.0, 0.0, 0.0);
}

void main () 
{
    frag_color = vec4(point_light(u_light, u_material) + spot_light(u_flashlight, u_material), 1.0);   
}