#include <glm.hpp>

#include "mge/materials/SpotLightMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* SpotLightMaterial::_shader = NULL;

GLint SpotLightMaterial::_uModelMatrix = 0;
GLint SpotLightMaterial::_uViewMatrix = 0;
GLint SpotLightMaterial::_uProjMatrix = 0;

GLint SpotLightMaterial::_uDiffuseColor = 0;
GLint SpotLightMaterial::_uGlobalAmbientColor = 0;
GLint SpotLightMaterial::_uLightColor = 0;

GLint SpotLightMaterial::_uLightPos = 0;
GLint SpotLightMaterial::_uCameraPosition = 0;

GLint SpotLightMaterial::_aVertex = 0;
GLint SpotLightMaterial::_aNormal = 0;
GLint SpotLightMaterial::_aUV = 0;

SpotLightMaterial::SpotLightMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void SpotLightMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"spotLight.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"spotLight.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uModelMatrix =  _shader->getUniformLocation("mat_Model");
        _uViewMatrix = _shader->getUniformLocation("mat_View");
        _uProjMatrix = _shader->getUniformLocation("mat_Proj");

        _uDiffuseColor =             _shader->getUniformLocation("diffuseColor");
        _uCameraPosition =    _shader->getUniformLocation("cameraPosition");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

SpotLightMaterial::~SpotLightMaterial()
{
    //dtor
}

void SpotLightMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}
void SpotLightMaterial::setGlobalAmbientColor(glm::vec3 pGlobalAmbientColor) {
    _globalAmbientColor = pGlobalAmbientColor;
}
void SpotLightMaterial::setLightColor(glm::vec3 pLightColor) {
    _LightColor = pLightColor;
}
void SpotLightMaterial::setLightPos(glm::vec3 pLightPos) {
    _LightPos = pLightPos;
}

void SpotLightMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glUniformMatrix4fv (_uProjMatrix, 1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));



    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
    //Light properties
    glUniform3fv (_shader->getUniformLocation("spotLight.ambientColor"), 1, glm::value_ptr(glm::vec3(.1f,.1f,.1f)));
    glUniform3fv (_shader->getUniformLocation("spotLight.diffuseColor"), 1, glm::value_ptr(glm::vec3(.8f,.8f,.8f)));
    glUniform3fv (_shader->getUniformLocation("spotLight.specularColor"), 1, glm::value_ptr(glm::vec3(1,1,1)));
    glUniform1f (_shader->getUniformLocation("spotLight.constant"), 1.f);
    glUniform1f (_shader->getUniformLocation("spotLight.linear"), 0.09f);
    glUniform1f (_shader->getUniformLocation("spotLight.quadratic"), 0.032f);
    glUniform1f (_shader->getUniformLocation("spotLight.cutOff"), glm::cos(glm::radians(6.5f)));
    glUniform1f (_shader->getUniformLocation("spotLight.outerCutOff"), glm::cos(glm::radians(9.5f)));
    glUniform3fv (_shader->getUniformLocation("spotLight.position"), 1, glm::value_ptr(pCamera->getWorldPosition()));
   // glUniform3fv (_shader->getUniformLocation("spotLight.direction"), 1, glm::value_ptr(glm::vec3(0,0,1)));
    glUniform3fv (_shader->getUniformLocation("spotLight.direction"), 1, glm::value_ptr(pCamera->getForward()));
    //camera pos.
    glUniform3fv (_uCameraPosition, 1, glm::value_ptr(pCamera->getWorldPosition()));



    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);

}
