//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
struct Light{
    int type;
float bla;};
uniform Light lights[8];

uniform vec3 diffuseColor;
uniform vec3 globalAmbientColor;
uniform vec3 directionalLightColor;
uniform vec3 directionalLight;
uniform vec3 cameraPosition;

out vec4 fragment_color;

in vec3 vertexWorldPos;
in vec3 normalWorldPos;

void main( void ) {
    //ambient
    vec3 ambientTerm = globalAmbientColor * diffuseColor;

    //diffuse
    float diffuseIntensity = max(dot(normalize(normalWorldPos), normalize(-directionalLight)),0.0f);
    vec3 diffuseTerm = diffuseIntensity * directionalLightColor * diffuseColor;

    //specular
    vec3 viewDirection = normalize(cameraPosition - vertexWorldPos);
    vec3 reflectDirection = reflect(normalize(directionalLight), normalize(normalWorldPos));
    float specularIntensity = pow(max(dot(reflectDirection, viewDirection), 0.f), 32);
    float specScale = 0.5f;
    vec3 specularTerm = specScale * specularIntensity * directionalLightColor * diffuseColor;

    vec3 finalColor = ambientTerm + diffuseTerm + specularTerm;

    fragment_color = vec4(finalColor, 1.f);
}
