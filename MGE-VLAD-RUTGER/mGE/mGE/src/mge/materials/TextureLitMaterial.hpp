#ifndef TEXTURELITMATERIAL_H
#define TEXTURELITMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class TextureLitMaterial : public AbstractMaterial
{
    public:
        TextureLitMaterial(Texture * pDiffuseTexture, Texture* pNormalTexture, float pShininess);
		TextureLitMaterial(Texture * pDiffuseTexture, Texture* pNormalTexture,Texture * pSpecularTexture, float pShininess);

        virtual ~TextureLitMaterial ();
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

#endif // TEXTURELITMATERIAL_H
