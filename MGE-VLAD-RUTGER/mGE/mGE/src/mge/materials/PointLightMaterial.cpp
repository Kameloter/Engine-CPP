#include <glm.hpp>

#include "mge/materials/PointLightMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* PointLightMaterial::_shader = NULL;

GLint PointLightMaterial::_uModelMatrix = 0;
GLint PointLightMaterial::_uViewMatrix = 0;
GLint PointLightMaterial::_uProjMatrix = 0;

GLint PointLightMaterial::_uDiffuseColor = 0;
GLint PointLightMaterial::_uGlobalAmbientColor = 0;
GLint PointLightMaterial::_uLightColor = 0;

GLint PointLightMaterial::_uLightPos = 0;
GLint PointLightMaterial::_uCameraPosition = 0;

GLint PointLightMaterial::_aVertex = 0;
GLint PointLightMaterial::_aNormal = 0;
GLint PointLightMaterial::_aUV = 0;

PointLightMaterial::PointLightMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void PointLightMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"fragPointLitColor.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"fragPointLitColor.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uModelMatrix =  _shader->getUniformLocation("mat_Model");
        _uViewMatrix = _shader->getUniformLocation("mat_View");
        _uProjMatrix = _shader->getUniformLocation("mat_Proj");

        _uDiffuseColor =             _shader->getUniformLocation("diffuseColor");
        _uGlobalAmbientColor =       _shader->getUniformLocation("globalAmbientColor");
        _uLightColor =    _shader->getUniformLocation("lightColor");

        _uLightPos =    _shader->getUniformLocation("lightPos");
        _uCameraPosition =    _shader->getUniformLocation("cameraPosition");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

PointLightMaterial::~PointLightMaterial()
{
    //dtor
}

void PointLightMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}
void PointLightMaterial::setGlobalAmbientColor(glm::vec3 pGlobalAmbientColor) {
    _globalAmbientColor = pGlobalAmbientColor;
}
void PointLightMaterial::setLightColor(glm::vec3 pLightColor) {
    _LightColor = pLightColor;
}
void PointLightMaterial::setLightPos(glm::vec3 pLightPos) {
    _LightPos = pLightPos;
}

void PointLightMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glUniformMatrix4fv (_uProjMatrix, 1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));



    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
    glUniform3fv (_uGlobalAmbientColor, 1, glm::value_ptr(_globalAmbientColor));
    glUniform3fv (_uLightColor, 1, glm::value_ptr(_LightColor));
    glUniform3fv (_uLightPos, 1, glm::value_ptr(_LightPos));
    glUniform3fv (_uCameraPosition, 1, glm::value_ptr(pCamera->getWorldPosition()));



    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);

}
