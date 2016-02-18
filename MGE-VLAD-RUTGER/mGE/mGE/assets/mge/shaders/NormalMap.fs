//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

//could maybe add 2 kinds of specular .. as a vector and a texture (for more flexibility)????
struct Material {

    vec3 specular;
    float shininess;
};
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float quadratic;
    float constant;
    float linear;
};

struct SpotLight{
    vec3 position;
    vec3 direction;


    float cutoff;
};

vec3 getDirectionalLight(DirLight light, vec3 n, vec3 view);
vec3 getPointLight(PointLight light, vec3 n, vec3 vertpos, vec3 view);
#define lightNumber 15

uniform PointLight pointLight[lightNumber];
uniform DirLight dirLight;
uniform Material material;

uniform sampler2D matDiffuse;
uniform sampler2D normalMap;


in vec3 vertices;
in vec2 uvs;
in vec3 verticesTangent;
in vec3 camPosTangent;
in vec3 lightPosTangent;

out vec4 fragment_color;

void main( void )
{


    vec3 normal = texture(normalMap, uvs).rgb;
    normal = normalize(normal * 2.0 - 1.0);


    vec3 color = texture(matDiffuse, uvs).rgb;
    vec3 ambient = 0.1 * color;

    vec3 lightDir = normalize(lightPosTangent - verticesTangent);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(camPosTangent - verticesTangent);
    vec3 reflectDir = normalize(reflect(-lightDir,normal));
  //  vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.5f) * spec;

    fragment_color = vec4(ambient + diffuse + specular, 1.0f);



}

