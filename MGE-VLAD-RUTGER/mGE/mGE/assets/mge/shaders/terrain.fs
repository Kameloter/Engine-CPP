//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

//uniform sampler2D tex_DiffuseR;
uniform sampler2D tex_DiffuseG;
//uniform sampler2D tex_DiffuseB;
//uniform sampler2D tex_DiffuseA;
uniform float time;
//uniform sampler2D splatMap;
in vec2 texCoord;
out vec4 fragment_color;

void main( void ) {

    float factorX = sin(time / 20);
    float factorY = cos(time / 20);

    vec2 changeUv = texCoord;
    vec2 dis1 = vec2(texCoord.x + factorX, texCoord.y + factorY)  * 4f;
    vec2 disT = dis1 ;

    changeUv += disT;

  //  vec4 splatVector = texture(splatMap,texCoord);
    vec3 finalColor = vec3(0.f);

 //   finalColor += texture(tex_DiffuseR,texCoord) * splatVector.r;
    finalColor += texture(tex_DiffuseG,changeUv).rgb ;//* splatVector.g;
 //   finalColor += texture(tex_DiffuseB,texCoord) * splatVector.b;
 //   finalColor += texture(tex_DiffuseA,texCoord) * splatVector.a;

	fragment_color = vec4(finalColor,1.0f);
}
