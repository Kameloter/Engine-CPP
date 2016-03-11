#pragma once

#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class BasicTextureLit : public AbstractMaterial
{
    public:
		BasicTextureLit(Texture * pDiffuseTexture, float pShininess);
		BasicTextureLit(Texture * pDiffuseTexture, Texture * pSpecularTexture, float pShininess);

        virtual ~BasicTextureLit();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);
        void setDiffuseTexture (Texture* pDiffuseTexture);
       
    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
        Texture* _specularTexture;
		Texture* _normalTexture;
		bool specMapOn;
        float _shininess;
};

