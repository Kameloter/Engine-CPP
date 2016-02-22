#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec3 tangent;
in vec3 bitangent;

out vec3 vertices;
out vec2 uvs;
out vec3 verticesTangent;
out vec3 camPosTangent;
out vec3 lightPosTangent;


uniform	mat4 mat_Model;
uniform mat4 mat_View;
uniform mat4 mat_Proj;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

out vec3 t;
out vec3 b;


void main( void ){

	gl_Position = mat_Proj * mat_View * mat_Model * vec4(vertex, 1.f);
    vertices = vec3(mat_Model * vec4(vertex,1.f));
    uvs = uv;

    vec3 T = normalize(vec3(mat_Model * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(mat_Model * vec4(normal, 0.0)));

    //T = normalize(T - dot(T, N) * N); // re-orthogonalize T with respect to N
	//T -= N * dot(T,N);
	//T = normalize(T);

    vec3 B = cross(T, N);  // then retrieve perpendicular vector B with the cross product of T and N		
				 
	if(dot(cross(T,N), B) > 0.0f)
	{
		T *= -1;
	}

	mat3 TBN = mat3(T, B, N);



    verticesTangent = TBN * vertices;
    camPosTangent = TBN * cameraPosition;
    lightPosTangent = TBN * lightPosition;

	t = tangent;

}
