#ifndef SPOTLIGHTMATERIAL_H
#define SPOTLIGHTMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include <glm.hpp>

/**
 * Simple single color material.
 * This material uses no lights.
 */
class SpotLightMaterial : public AbstractMaterial
{
    public:
        SpotLightMaterial(glm::vec3 pColor = glm::vec3(1,0,0));
        virtual ~SpotLightMaterial();
        virtual void render(World* pWorld, GameObject* pGameObject, Camera* pCamera);

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);

        //just for test purposes , would be wise to make the material get them from world?
        void setGlobalAmbientColor (glm::vec3 pGlobalAmbient);
        void setLightColor (glm::vec3 pLightColor);

        void setLightPos (glm::vec3 pLightPos);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uModelMatrix;
        static GLint _uViewMatrix;
        static GLint _uProjMatrix;

        static GLint _uLightPos;
        static GLint _uCameraPosition;

        static GLint _uDiffuseColor;
        static GLint _uGlobalAmbientColor;
        static GLint _uLightColor;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;
        glm::vec3 _globalAmbientColor;
        glm::vec3 _LightColor;
        glm::vec3 _LightPos;

};

#endif // SPOTLIGHTMATERIAL_H
