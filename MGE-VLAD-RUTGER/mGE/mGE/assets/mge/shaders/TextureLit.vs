#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec3 tangent;

uniform	mat4 mat_Model;
uniform mat4 mat_View;
uniform mat4 mat_Proj;
uniform mat4 pvm;

out vec3 vertices;
out vec2 uvs;
out mat3 TBN;
//out vec3 normals;

void main( void ){
	gl_Position = pvm * vec4(vertex, 1.f);

    vertices = vec3(mat_Model * vec4(vertex,1.f));
	uvs = uv;
 //   normals = vec3(transpose(inverse(mat_Model)) * vec4 (normal,0.f)); // was used if there is no normal mapping.


	vec3 T = normalize(vec3(mat_Model * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(mat_Model * vec4(normal, 0.0)));

    T = normalize(T - dot(T, N) * N); // re-orthogonalize T with respect to N

    vec3 B = cross(T, N);  // then retrieve perpendicular vector B with the cross product of T and N		
				 
	if(dot(cross(T,N), B) > 0.0f)
	{
		T *= -1;
	}

    TBN = mat3(T, B, N);

}
