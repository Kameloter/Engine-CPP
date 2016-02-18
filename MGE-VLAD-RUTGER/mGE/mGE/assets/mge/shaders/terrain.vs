//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;



uniform sampler2D heightMap;
uniform float time;
in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){

    vec3 heightVertex = vertex;
    //heightVertex.y = sin(heightVertex.x + time) / 3.f + cos(heightVertex.z + time) / 3.f;
    heightVertex.y = texture(heightMap, uv).r * 1.f;

    //heightVertex.y = sin(heightVertex.x + time) * 0.4f;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(heightVertex, 1.f);
	texCoord = uv;
}
