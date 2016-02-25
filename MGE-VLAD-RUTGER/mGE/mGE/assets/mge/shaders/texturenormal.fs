//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform sampler2D matDiffuse;
uniform sampler2D normalMap;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

in vec3 vertices;
in vec2 uvs;
in mat3 TBN;


in vec3 t;

out vec4 fragment_color;

void main( void )
{
    vec3 normal = texture(normalMap, uvs).rgb;
    normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

    vec3 sampleDiff = texture(matDiffuse, uvs).rgb;
    vec3 ambient = 0.1 * sampleDiff;

    vec3 lightDir = normalize(-lightPosition);

    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * sampleDiff;

    // Specular
    vec3 viewDir = normalize(cameraPosition - vertices);
    vec3 reflectDir = normalize(reflect(-lightDir,normal));


     vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.2f) * spec;

    fragment_color = vec4(ambient + diffuse + specular, 1.0f);
				//	fragment_color = vec4(t,1);

}

