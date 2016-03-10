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

    float factorX = sin(time / 25);
    float factorY = cos(time / 25);

    vec2 changeUv = texCoord;
    vec2 dis1 = texture (tex_DiffuseG,vec2(texCoord.x + factorX, texCoord.y + factorY)).rg  * .1f;
    vec2 dis2 = texture (tex_DiffuseG,vec2(-texCoord.x + factorX, texCoord.y - factorY)).rg * .1f;
    vec2 disT = dis1 + dis2;

    changeUv += disT;

  //  vec4 splatVector = texture(splatMap,texCoord);
    vec4 finalColor = vec4(0.f);

 //   finalColor += texture(tex_DiffuseR,texCoord) * splatVector.r;
    finalColor += texture(tex_DiffuseG,changeUv) ;//* splatVector.g;
 //   finalColor += texture(tex_DiffuseB,texCoord) * splatVector.b;
 //   finalColor += texture(tex_DiffuseA,texCoord) * splatVector.a;

	fragment_color = finalColor;
}
