//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;
uniform float clock;
uniform vec3 origin;
out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){

    vec3 newVert = vertex;
 //   newVert.y = sin((newVert.x + 0.1f) + clock) * 0.3f;

    vec3 delta = newVert - origin;
    delta.y *= sin(delta.y + clock);
    newVert = origin + delta;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(newVert, 1.f);
	texCoord = uv;
}
