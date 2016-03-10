#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class TerrainMaterial : public AbstractMaterial
{
    public:
        TerrainMaterial (Texture* pDiffuseTextureG
                      );
        virtual ~TerrainMaterial ();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);

        void setDiffuseTexture (Texture* pDiffuseTexture);
        void setHeightMapTexture (Texture* pHeightMapTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();
        static GLint _uDiffuseTextureR;
        static GLint _uDiffuseTextureG;
        static GLint _uDiffuseTextureB;
        static GLint _uDiffuseTextureA;
        static GLint _uSplatMap;
        static GLint _uHeightMap;
        Texture* _diffuseTextureR;
        Texture* _diffuseTextureG;
        Texture* _diffuseTextureB;
        Texture* _diffuseTextureA;
        Texture* _splatMap;
        Texture* _heightMap;
};

#endif // TERRAINMATERIAL_H
