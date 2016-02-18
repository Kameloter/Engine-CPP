#ifndef WOBBLYMATERIAL_H
#define WOBBLYMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class WobblyMaterial : public AbstractMaterial
{
    public:
        WobblyMaterial (Texture* pDiffuseTexture);
        virtual ~WobblyMaterial ();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);

        void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
};

#endif // WOBBLYMATERIAL_H
