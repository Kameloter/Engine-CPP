//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

//could maybe add 2 kinds of specular .. as a vector and a texture (for more flexibility)????
struct Material {

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

struct SpotLight {
    vec3 position;
    vec3 direction;

    float innerCircle;
    float outerCircle;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float quadratic;
    float constant;
    float linear;
};

vec3 getDirectionalLight(DirLight light, vec3 n, vec3 view);
vec3 getPointLight(PointLight light, vec3 n, vec3 view);
vec3 getSpotLight(SpotLight light, vec3 n, vec3 view);
#define lightNumber 15
#define spotLightNumber 2
uniform PointLight pointLight[lightNumber];
uniform SpotLight spotLight[spotLightNumber];
uniform DirLight dirLight;
uniform Material material;
uniform sampler2D matDiffuse;
uniform sampler2D matSpecular;
uniform vec3 cameraPosition;
uniform bool specMapOn;

in vec3 vertices;
in vec3 normals;
in vec2 uvs;

out vec4 fragment_color;

void main( void )
{
    vec3 normalizedNormal = normalize(normals);
    vec3 viewDirection = normalize(cameraPosition - vertices);

    vec3 finalColor;
    finalColor = getDirectionalLight(dirLight,normalizedNormal,viewDirection);

    for(int i = 0; i < lightNumber; i++)
    {
        finalColor += getPointLight(pointLight[i],normalizedNormal,viewDirection);
    }
    for(int i = 0; i < spotLightNumber; i++)
    {
        finalColor += getSpotLight(spotLight[i], normalizedNormal, viewDirection);
    }
    fragment_color = vec4(finalColor, 1.f);
}

vec3 getDirectionalLight(DirLight light, vec3 n, vec3 view)
{
    vec3 lightDirection = normalize(-light.direction);

    float diffuse = max(dot(n,lightDirection),0.f);

    vec3 reflectDirection = reflect(-lightDirection, n);
    float specular = pow(max(dot(view, reflectDirection),0.f),material.shininess);

    vec3 ambientTerm = light.ambient * vec3(texture(matDiffuse, uvs));
    vec3 diffuseTerm = light.diffuse * diffuse * vec3(texture(matDiffuse, uvs));
    vec3 specularTerm;
    if(specMapOn)
    {
         specularTerm = light.specular * specular * vec3(texture(matSpecular, uvs));
    }else{
        specularTerm = light.specular * specular *  vec3(0.1);

    }

    return (ambientTerm + diffuseTerm + specularTerm);
}
vec3 getPointLight(PointLight light, vec3 n, vec3 view)
{
    if(light.constant == 0) return vec3(0,0,0);
    //ambient
    vec3 ambientTerm = light.ambient * vec3(texture(matDiffuse, uvs));

    vec3 lightDirection = normalize(light.position - vertices);
    //diffuse
    float diffuse = max(dot(n, lightDirection),0.0f);
    vec3 diffuseTerm = light.diffuse * diffuse * vec3(texture(matDiffuse, uvs));

    //specular - BLINN - PHONG
   vec3 halfWayDir = normalize(lightDirection + view);
   float specular = pow(max(dot(n, halfWayDir), 0.f), material.shininess);
   //specular - BLINN
   // vec3 reflectDirection = reflect(-lightDirection, n);
   // float specular = pow(max(dot(reflectDirection, view), 0.f), material.shininess);
    vec3 specularTerm;
    if(specMapOn)
    {
         specularTerm = light.specular * specular * vec3(texture(matSpecular, uvs));
    }else{
        specularTerm = light.specular * specular *  vec3(0.1);

    }
    //Attenuation
    float distance = length(light.position - vertices);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * pow(distance,2));

    ambientTerm *= attenuation;
    diffuseTerm *= attenuation;
    specularTerm *= attenuation;

    return (ambientTerm + diffuseTerm + specularTerm);
}

vec3 getSpotLight(SpotLight light, vec3 n, vec3 view)
{
    if(light.constant == 0) return vec3(0,0,0);
    vec3 lightDirection = normalize(light.position - vertices);

    vec3 ambientTerm = light.ambient * vec3(texture(matDiffuse, uvs));

    float diffuse = max(dot(n, lightDirection),0.0f);
    vec3 diffuseTerm = light.diffuse * diffuse * vec3(texture(matDiffuse, uvs));

    vec3 viewDirection = normalize(cameraPosition - vertices);

    vec3 reflectDirection = reflect(-lightDirection, n);
    float specular = pow(max(dot(reflectDirection, viewDirection), 0.f), material.shininess);
    vec3 specularTerm;
    if(specMapOn)
    {
         specularTerm = light.specular * specular * vec3(texture(matSpecular, uvs));
    }else{
        specularTerm = light.specular * specular * vec3(0.1);

    }

    //attenuation
    float distance = length(light.position - vertices);
    float attenuation = 1.f / (light.constant + light.linear * distance + light.quadratic * pow(distance,2));


    //spot area
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = (light.innerCircle - light.outerCircle);
    float intensity = clamp((theta - light.outerCircle) / epsilon, 0.0f, 1.0f);

    ambientTerm *= intensity * attenuation;
    diffuseTerm *= intensity * attenuation;
    specularTerm *= intensity * attenuation;
    return (ambientTerm + diffuseTerm + specularTerm);
}
