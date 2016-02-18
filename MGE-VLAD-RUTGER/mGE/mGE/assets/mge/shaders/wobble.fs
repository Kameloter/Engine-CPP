//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D textureDiffuse;
in vec2 texCoord;
out vec4 fragment_color;
uniform float clock;
void main( void ) {

  //  vec2 newUv = texCoord;
  //  newUv.x += sin(newUv.y * clock/10) * 0.2f;

	fragment_color = texture(textureDiffuse,texCoord);
}
