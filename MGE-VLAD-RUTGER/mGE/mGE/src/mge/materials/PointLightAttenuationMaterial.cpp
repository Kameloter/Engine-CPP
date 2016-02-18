#include <glm.hpp>

#include "mge/materials/PointLightAttenuationMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* PointLightAttenuationMaterial::_shader = NULL;

GLint PointLightAttenuationMaterial::_uModelMatrix = 0;
GLint PointLightAttenuationMaterial::_uViewMatrix = 0;
GLint PointLightAttenuationMaterial::_uProjMatrix = 0;

GLint PointLightAttenuationMaterial::_uDiffuseColor = 0;
GLint PointLightAttenuationMaterial::_uGlobalAmbientColor = 0;
GLint PointLightAttenuationMaterial::_uLightColor = 0;

GLint PointLightAttenuationMaterial::_uLightPos = 0;
GLint PointLightAttenuationMaterial::_uCameraPosition = 0;

GLint PointLightAttenuationMaterial::_aVertex = 0;
GLint PointLightAttenuationMaterial::_aNormal = 0;
GLint PointLightAttenuationMaterial::_aUV = 0;

PointLightAttenuationMaterial::PointLightAttenuationMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void PointLightAttenuationMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"vertPointAttenuation.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"fragPointAttenuation.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uModelMatrix =  _shader->getUniformLocation("mat_Model");
        _uViewMatrix = _shader->getUniformLocation("mat_View");
        _uProjMatrix = _shader->getUniformLocation("mat_Proj");

        _uDiffuseColor =             _shader->getUniformLocation("diffuseColor");
        _uGlobalAmbientColor =       _shader->getUniformLocation("globalAmbientColor");
        _uLightPos =    _shader->getUniformLocation("lightPos");
        _uCameraPosition =    _shader->getUniformLocation("cameraPosition");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

PointLightAttenuationMaterial::~PointLightAttenuationMaterial()
{
    //dtor
}

void PointLightAttenuationMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}
void PointLightAttenuationMaterial::setGlobalAmbientColor(glm::vec3 pGlobalAmbientColor) {
    _globalAmbientColor = pGlobalAmbientColor;
}
void PointLightAttenuationMaterial::setLightColor(glm::vec3 pLightColor) {
    _LightColor = pLightColor;
}
void PointLightAttenuationMaterial::setLightPos(glm::vec3 pLightPos) {
    _LightPos = pLightPos;
}

void PointLightAttenuationMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glUniformMatrix4fv (_uProjMatrix, 1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));



    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
    //Light properties
    glUniform3fv (_uGlobalAmbientColor, 1, glm::value_ptr(_globalAmbientColor));
    glUniform3fv (_shader->getUniformLocation("lightColor"), 1, glm::value_ptr(glm::vec3(1.f,1.f,1.f)));
    glUniform1f (_shader->getUniformLocation("constant"), 1.f);
    glUniform1f (_shader->getUniformLocation("linear"), 0.09f);
    glUniform1f (_shader->getUniformLocation("quadratic"), 0.032f);
    glUniform3fv (_uLightPos, 1, glm::value_ptr(_LightPos));
    //camera pos.
    glUniform3fv (_uCameraPosition, 1, glm::value_ptr(pCamera->getWorldPosition()));



    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);

}
