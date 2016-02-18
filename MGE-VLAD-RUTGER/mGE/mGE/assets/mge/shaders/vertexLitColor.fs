//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 diffuseColor;
uniform vec3 globalAmbientColor;
uniform vec3 directionalLightColor;

out vec4 fragment_color;

in float diffuseIntensity;
in float specularIntensity;

void main( void ) {
    vec3 ambientTerm = globalAmbientColor * diffuseColor;
    vec3 diffuseTerm = diffuseIntensity * directionalLightColor * diffuseColor;
    float specScale = 1.f;
    vec3 specularTerm = specScale * specularIntensity * directionalLightColor *diffuseColor;

    fragment_color = vec4(ambientTerm + diffuseTerm + specularTerm, 1.f);
}
