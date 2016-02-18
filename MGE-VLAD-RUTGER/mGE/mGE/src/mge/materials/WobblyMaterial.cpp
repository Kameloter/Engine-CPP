#include <glm.hpp>

#include "mge/materials/WobblyMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/core/Timer.hpp"

ShaderProgram* WobblyMaterial::_shader = NULL;

WobblyMaterial::WobblyMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

WobblyMaterial::~WobblyMaterial() {}

void WobblyMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"wobble.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"wobble.fs");
        _shader->finalize();
    }
}

void WobblyMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void WobblyMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    if (!_diffuseTexture) return;

    _shader->use();

    //setup texture slot 0
    _shader->setTexture(_shader->getUniformLocation("textureDiffuse"),0,_diffuseTexture->getId());

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );
    glUniform1f(_shader->getUniformLocation("clock"), Timer::now());
    glm::vec3 origin = pGameObject->getLocalPosition();
    glUniform3f(_shader->getUniformLocation("origin"), origin.x,origin.y,origin.z);
    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}

