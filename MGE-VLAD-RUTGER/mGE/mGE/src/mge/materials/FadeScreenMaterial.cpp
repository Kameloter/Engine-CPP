#include <glm.hpp>

#include "mge/materials/FadeScreenMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "SFML\Graphics.hpp"

ShaderProgram* FadeScreenMaterial::_shader = NULL;

GLint FadeScreenMaterial::_uMVPMatrix = 0;
GLint FadeScreenMaterial::_uDiffuseColor = 0;

GLint FadeScreenMaterial::_aVertex = 0;
GLint FadeScreenMaterial::_aNormal = 0;
GLint FadeScreenMaterial::_aUV = 0;
GLuint FadeScreenMaterial::_uAlpha = 0;

FadeScreenMaterial::FadeScreenMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor),_alpha(1)
{
	_renderImage = true;
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void FadeScreenMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"FadeScreen.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"FadeScreen.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix=  _shader->getUniformLocation("mvpMatrix");
        _uDiffuseColor =    _shader->getUniformLocation("diffuseColor");
		_uAlpha = _shader->getUniformLocation("alpha");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");

    }
}

FadeScreenMaterial::~FadeScreenMaterial()
{
	std::cout << " color material cleaned " << std::endl;
}

void FadeScreenMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void FadeScreenMaterial::setAlpha(float amount)
{
	_alpha = amount;
	
}


void FadeScreenMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
	if (!_renderImage) return;

	_shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pCamera->getProjection() * glm::inverse(pCamera->getWorldTransform()) * pGameObject->getWorldTransform();
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
	glUniform1f(_uAlpha, _alpha);

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);

}

void FadeScreenMaterial::setRenderImage(bool value)
{
	_renderImage = value;
}
