//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;


uniform	mat4 mat_Model;
uniform mat4 mat_View;
uniform mat4 mat_Proj;


out vec3 vertexWorldPos;
out vec3 normalWorldPos;

void main( void ){
	gl_Position = mat_Proj * mat_View * mat_Model * vec4(vertex, 1.f);
    vertexWorldPos = vec3(mat_Model * vec4(vertex,1.f));
    normalWorldPos = vec3(transpose(inverse(mat_Model)) * vec4 (normal,0.f));



}
