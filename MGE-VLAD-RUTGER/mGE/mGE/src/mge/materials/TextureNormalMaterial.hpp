#ifndef TEXTURENORMALMATERIAL_H
#define TEXTURENORMALMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class TextureNormalMaterial : public AbstractMaterial
{
    public:
        TextureNormalMaterial(Texture * pDiffuseTexture,glm::vec3 pSpecular, float pShininess,Texture* pNormalMap);
        virtual ~TextureNormalMaterial ();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);

        void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
        Texture* _normalMap;
        glm::vec3 _specular;
        float _shininess;
};

#endif // TEXTURENORMALMATERIAL_H
