#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 mat_Model;
uniform mat4 mat_View;
uniform mat4 mat_Proj;
uniform mat4 pvm;

out vec3 vertices;
out vec2 uvs;
out vec3 normals;

void main( void ){
	gl_Position = pvm * vec4(vertex, 1.f);

    vertices = vec3(mat_Model * vec4(vertex,1.f));
	uvs = uv;
    normals = vec3(transpose(inverse(mat_Model)) * vec4 (normal,0.f)); // was used if there is no normal mapping.


	
}
