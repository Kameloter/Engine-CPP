//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform sampler2D matDiffuse;
uniform sampler2D normalMap;


in vec3 vertices;

in vec2 uvs;
in vec3 verticesTangent;
in vec3 camPosTangent;
in vec3 lightPosTangent;
in vec3 t;

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
   // vec3 reflectDir = normalize(reflect(-lightDir,normal));
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.2f) * spec;

    fragment_color = vec4(ambient + diffuse + specular, 1.0f);
//	fragment_color = vec4(t,1);

}

