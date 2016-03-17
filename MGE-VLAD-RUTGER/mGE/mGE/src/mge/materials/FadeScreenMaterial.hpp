#pragma once

#include "mge/materials/AbstractMaterial.hpp"
#include <glm.hpp>

/**
 * Simple single color material.
 * This material uses no lights.
 */
class FadeScreenMaterial : public AbstractMaterial
{
    public:
		FadeScreenMaterial(glm::vec3 pColor = glm::vec3(1,0,0));
        virtual ~FadeScreenMaterial();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);
		void setRenderImage(bool value);
        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);
		void setAlpha(float amount);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix;
        static GLint _uDiffuseColor;
		static GLuint _uAlpha;
		float _alpha;
		bool _renderImage;
        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;
};

