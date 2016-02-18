//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
struct SpotLight {
    vec3 position;
    vec3 direction;

    float innerCircle;
    float outerCircle;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    float quadratic;
    float constant;
    float linear;
};
uniform SpotLight spotLight;
uniform vec3 diffuseColor;
uniform vec3 cameraPosition;



in vec3 vertexWorldPos;
in vec3 normalWorldPos;

out vec4 fragment_color;

void main( void ) {
    //ambient
    vec3 ambientTerm = spotLight.ambientColor * diffuseColor;

    //diffuse
    vec3 lightDirection = normalize(spotLight.position - vertexWorldPos);
    float diffuseIntensity = max(dot(normalize(normalWorldPos), lightDirection),0.0f);
    vec3 diffuseTerm = spotLight.diffuseColor * diffuseIntensity * diffuseColor;

    //specular
    vec3 viewDirection = normalize(cameraPosition - vertexWorldPos);

   // vec3 halfWayDir = normalize(lightDirection + viewDirection);
  // float specularIntensity = pow(max(dot(normalize(normalWorldPos), halfWayDir), 0.f), 32.f);

    vec3 reflectDirection = reflect(-lightDirection, normalize(normalWorldPos));
    float specularIntensity = pow(max(dot(reflectDirection, viewDirection), 0.f), 32.f);
    float specScale = 0.20f;
    vec3 specularTerm =  specScale * specularIntensity * spotLight.specularColor;


    float theta = dot(lightDirection, normalize(-spotLight.direction));
    float epsilon = ( spotLight.outerCircle - spotLight.innerCircle );
    float intensity = clamp((theta - spotLight.outerCircle) / epsilon, 0.0f, 1.0f);
    //ambientTerm *= intensity;
    diffuseTerm *= intensity;
    specularTerm *= intensity;

    //Attenuation
    float distance = length(spotLight.position - vertexWorldPos);
    float attenuation = 1.f / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

    ambientTerm *= attenuation;
    diffuseTerm *= attenuation;
    specularTerm *= attenuation;

    vec3 finalColor = ambientTerm + diffuseTerm + specularTerm;

    fragment_color = vec4(finalColor, 1.f);
}
