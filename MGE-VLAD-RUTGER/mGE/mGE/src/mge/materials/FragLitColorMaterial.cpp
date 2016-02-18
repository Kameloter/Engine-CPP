#include <glm.hpp>

#include "mge/materials/FragLitColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* FragLitColorMaterial::_shader = NULL;

GLint FragLitColorMaterial::_uModelMatrix = 0;
GLint FragLitColorMaterial::_uViewMatrix = 0;
GLint FragLitColorMaterial::_uProjMatrix = 0;

GLint FragLitColorMaterial::_uDiffuseColor = 0;
GLint FragLitColorMaterial::_uGlobalAmbientColor = 0;
GLint FragLitColorMaterial::_uDirectionalLightColor = 0;

GLint FragLitColorMaterial::_uDirectionalLight = 0;
GLint FragLitColorMaterial::_uCameraPosition = 0;

GLint FragLitColorMaterial::_aVertex = 0;
GLint FragLitColorMaterial::_aNormal = 0;
GLint FragLitColorMaterial::_aUV = 0;

FragLitColorMaterial::FragLitColorMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void FragLitColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"fragLitColor.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"fragLitColor.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uModelMatrix =  _shader->getUniformLocation("mat_Model");
        _uViewMatrix = _shader->getUniformLocation("mat_View");
        _uProjMatrix = _shader->getUniformLocation("mat_Proj");

        _uDiffuseColor =             _shader->getUniformLocation("diffuseColor");
        _uGlobalAmbientColor =       _shader->getUniformLocation("globalAmbientColor");
        _uDirectionalLightColor =    _shader->getUniformLocation("directionalLightColor");

        _uDirectionalLight =    _shader->getUniformLocation("directionalLight");
        _uCameraPosition =    _shader->getUniformLocation("cameraPosition");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

FragLitColorMaterial::~FragLitColorMaterial()
{
    //dtor
}

void FragLitColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}
void FragLitColorMaterial::setGlobalAmbientColor(glm::vec3 pGlobalAmbientColor) {
    _globalAmbientColor = pGlobalAmbientColor;
}
void FragLitColorMaterial::setDirectionalLightColor(glm::vec3 pDirectionalLightColor) {
    _directionalLightColor = pDirectionalLightColor;
}
void FragLitColorMaterial::setDirectionalLight(glm::vec3 pDirectionalLight) {
    _directionalLight = pDirectionalLight;
}

void FragLitColorMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glUniformMatrix4fv (_uProjMatrix, 1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));



    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
    glUniform3fv (_uGlobalAmbientColor, 1, glm::value_ptr(_globalAmbientColor));
    glUniform3fv (_uDirectionalLightColor, 1, glm::value_ptr(_directionalLightColor));
    glUniform3fv (_uDirectionalLight, 1, glm::value_ptr(_directionalLight));
    glUniform3fv (_uCameraPosition, 1, glm::value_ptr(pCamera->getWorldPosition()));



    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);

}
