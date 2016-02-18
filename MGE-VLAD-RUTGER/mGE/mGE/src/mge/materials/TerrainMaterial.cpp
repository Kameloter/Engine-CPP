#include <glm.hpp>

#include "mge/materials/TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Timer.hpp"
#include "mge/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uDiffuseTextureR = 0;
GLint TerrainMaterial::_uDiffuseTextureG = 0;
GLint TerrainMaterial::_uDiffuseTextureB = 0;
GLint TerrainMaterial::_uDiffuseTextureA = 0;
GLint TerrainMaterial::_uSplatMap = 0;
GLint TerrainMaterial::_uHeightMap = 0;

TerrainMaterial::TerrainMaterial(Texture* pDiffuseTextureR,Texture* pDiffuseTextureG,
                                 Texture* pDiffuseTextureB,Texture* pDiffuseTextureA,
                                 Texture* pSplatMap,Texture* pHeightMap):
    _diffuseTextureR(pDiffuseTextureR),_diffuseTextureG(pDiffuseTextureG),
    _diffuseTextureB(pDiffuseTextureB),_diffuseTextureA(pDiffuseTextureA),
    _splatMap(pSplatMap),_heightMap(pHeightMap) {
    _lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"terrain.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"terrain.fs");
        _shader->finalize();
        _uDiffuseTextureR = _shader->getUniformLocation("tex_DiffuseR");
        _uDiffuseTextureG = _shader->getUniformLocation("tex_DiffuseG");
        _uDiffuseTextureB = _shader->getUniformLocation("tex_DiffuseB");
        _uDiffuseTextureA = _shader->getUniformLocation("tex_DiffuseA");
        _uHeightMap = _shader->getUniformLocation("heightMap");
        _uSplatMap = _shader->getUniformLocation("splatMap");
    }
}

void TerrainMaterial::setDiffuseTexture (Texture* pDiffuseTextureA) {
    _diffuseTextureA = pDiffuseTextureA;
}
void TerrainMaterial::setHeightMapTexture (Texture* pHeightMap) {
    _heightMap = pHeightMap;
}

void TerrainMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    if (!_diffuseTextureA) return;

    _shader->use();
    _shader->setTexture(_uDiffuseTextureR,0,_diffuseTextureR->getId());
    _shader->setTexture(_uDiffuseTextureG,1,_diffuseTextureG->getId());
    _shader->setTexture(_uDiffuseTextureB,2,_diffuseTextureB->getId());
    _shader->setTexture(_uDiffuseTextureA,3,_diffuseTextureA->getId());
    _shader->setTexture(_uHeightMap,4,_heightMap->getId());
    _shader->setTexture(_uSplatMap,5,_splatMap->getId());

    glUniform1f(_shader->getUniformLocation("time"),Timer::now());


   // glUniform1i (_shader->getUniformLocation("heightMap"),0);
    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}

