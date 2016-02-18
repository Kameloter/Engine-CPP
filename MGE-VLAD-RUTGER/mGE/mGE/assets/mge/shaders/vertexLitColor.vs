//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;


uniform	mat4 mat_Model;
uniform mat4 mat_View;
uniform mat4 mat_Proj;

uniform vec3 directionalLight;
uniform vec3 cameraPosition;

out float diffuseIntensity;
out float specularIntensity;

void main( void ){
	gl_Position = mat_Proj * mat_View * mat_Model * vec4(vertex, 1.f);

	vec3 vertexWorldPos = vec3(mat_Model * vec4(vertex,1.f));

	vec3 normalWorldPos = vec3(transpose(inverse(mat_Model)) * vec4 (normal,0.f));

    //Diffuse light
    float diffIntensity = max(dot(normalize(normalWorldPos), normalize(-directionalLight)), 0.f);
    diffuseIntensity = diffIntensity;
    //Specular light
    vec3 viewDirection = normalize(cameraPosition - vertexWorldPos);
    vec3 reflectDirection = reflect(normalize(directionalLight), normalize(normalWorldPos));
    float specIntensity = pow(max(dot(reflectDirection, viewDirection), 0.f), 32);
    specularIntensity = specIntensity;


}
