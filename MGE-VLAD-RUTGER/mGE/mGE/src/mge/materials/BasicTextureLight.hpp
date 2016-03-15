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
		void _cacheUniformsAttributes();
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
        Texture* _specularTexture;
		Texture* _normalTexture;
		bool specMapOn;
        float _shininess;

		float _pointLightInnerCutOff;
		float _pointLightOuterCutOff;



		GLuint _uViewMat;
		GLuint _uProjMat;
		GLuint _uModelMat;


		GLuint _uCameraPosition;
		GLuint _uDiffuseMap;
		GLuint _uSpecularMap;
		GLuint _uUseSpecularMap;
		GLuint _uMaterialShininess;


		GLuint _uDirLight_Dir;
		GLuint _uDirLight_Ambient;
		GLuint _uDirLight_Diffuse;
		GLuint _uDirLight_Specular;

		GLuint _uSpotLight_Pos;
		GLuint _uSpotLight_Dir;
		GLuint _uSpotLight_Ambient;
		GLuint _uSpotLight_Diffuse;
		GLuint _uSpotLight_Specular;
		GLuint _uSpotLight_Linear;
		GLuint _uSpotLight_Quadratic;
		GLuint _uSpotLight_InnerCutOff;
		GLuint _uSpotLight_OutterCutOff;

		GLuint _aVertex;
		GLuint _aNormal;
		GLuint _aUv;
};

