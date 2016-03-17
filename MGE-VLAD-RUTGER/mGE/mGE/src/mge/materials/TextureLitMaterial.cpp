#include <glm.hpp>

#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/light/Light.h"
#include "mge/core/light/DirectionalLight.h"
#include "mge/core/light/PointLight.h"
#include "mge/config.hpp"

ShaderProgram* TextureLitMaterial::_shader = NULL;

TextureLitMaterial::TextureLitMaterial(Texture * pDiffuseTexture, Texture* pNormalTexture, float pShininess) :
	_diffuseTexture(pDiffuseTexture), _normalTexture(pNormalTexture), specMapOn(false), _specularTexture(0),_shininess(pShininess), cachePointLights(false)
{
    _lazyInitializeShader();
	_cacheUniformsAttributes();

}

TextureLitMaterial::TextureLitMaterial(Texture * pDiffuseTexture, Texture* pNormalTexture, Texture* pSpecularTexture, float pShininess) :
	_diffuseTexture(pDiffuseTexture), _normalTexture(pNormalTexture), specMapOn(true), _specularTexture(pSpecularTexture),_shininess(pShininess), cachePointLights(false)
{
	_lazyInitializeShader();
	_cacheUniformsAttributes();

}

TextureLitMaterial::~TextureLitMaterial() 
{
	//cout << "DESTROYED TextureLitMaterial "  << endl;
	//delete _shader;
	//_shader = NULL;

}

void TextureLitMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"TextureLit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"TextureLit.fs");
        _shader->finalize();

		
		
    }
}

void TextureLitMaterial::_cacheUniformsAttributes()
{
	_uProjMat = _shader->getUniformLocation("mat_Proj");
	_uViewMat = _shader->getUniformLocation("mat_View");
	_uModelMat = _shader->getUniformLocation("mat_Model");

	_uCameraPosition = _shader->getUniformLocation("cameraPosition");
	_uDiffuseMap = _shader->getUniformLocation("diffuseMap");
	_uNormalMap = _shader->getUniformLocation("normalMap");
	_uSpecularMap = _shader->getUniformLocation("specularMap");
	_uUseSpecularMap = _shader->getUniformLocation("mat_useSpecMap");
	_uMaterialShininess = _shader->getUniformLocation("mat_shininess");


	_uDirLight_Dir = _shader->getUniformLocation("dirLight.direction");
	_uDirLight_Ambient = _shader->getUniformLocation("dirLight.ambient");
	_uDirLight_Diffuse = _shader->getUniformLocation("dirLight.diffuse");
	_uDirLight_Specular = _shader->getUniformLocation("dirLight.specular");

	_uSpotLight_Pos = _shader->getUniformLocation("spotLight.position");
	_uSpotLight_Dir = _shader->getUniformLocation("spotLight.direction");
	_uSpotLight_Ambient = _shader->getUniformLocation("spotLight.ambient");
	_uSpotLight_Diffuse = _shader->getUniformLocation("spotLight.diffuse");
	_uSpotLight_Specular = _shader->getUniformLocation("spotLight.specular");
	_uSpotLight_Linear = _shader->getUniformLocation("spotLight.linear");
	_uSpotLight_Quadratic = _shader->getUniformLocation("spotLight.quadratic");
	_uSpotLight_InnerCutOff = _shader->getUniformLocation("spotLight.innerCircle");
	_uSpotLight_OutterCutOff = _shader->getUniformLocation("spotLight.outerCircle");


	_aVertex = _shader->getAttribLocation("vertex");
	_aNormal = _shader->getAttribLocation("normal");
	_aUv = _shader->getAttribLocation("uv");
	_aTangent = _shader->getAttribLocation("tangent");

	_pointLightInnerCutOff = glm::cos(glm::radians(14.5f));
	_pointLightOuterCutOff = glm::cos(glm::radians(18.5f));
}

void TextureLitMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureLitMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) { 
	if (!cachePointLights)
	{
		int count = 0;
		for (int i = 0; i < pWorld->getLightCount(); i++)
		{
			Light* temp = pWorld->getLightAt(i);
			switch (temp->type) 
			{
				case Light::LightType::Point:
				{
					count++;
					std::string num = "pointLight[" + std::to_string(count - 1) + "].";

				   	 _uPointLight_Pos[count - 1] = _shader->getUniformLocation(num + "position");
					 _uPointLight_Ambient[count - 1] = _shader->getUniformLocation(num + "ambient");
					 _uPointLight_Diffuse[count - 1] = _shader->getUniformLocation(num + "diffuse");
					 _uPointLight_Specular[count - 1] = _shader->getUniformLocation(num + "specular");
					
					break;
				}
			}
		}

		cachePointLights = true;
	}

    if (!_diffuseTexture || !_normalTexture) return;

    _shader->use();

    // set texture slots
    _shader->setTexture(_uDiffuseMap,0,_diffuseTexture->getId());
	_shader->setTexture(_uNormalMap, 1, _normalTexture->getId());
	if (specMapOn) {
		glUniform1i(_uUseSpecularMap, 1);
		_shader->setTexture(_uSpecularMap, 2, _specularTexture->getId());
	}
	else
	{
		glUniform1i(_uUseSpecularMap, 0);
		glUniform1f(_uMaterialShininess, _shininess);
	}

    glUniform3fv(_uCameraPosition,1, glm::value_ptr( pCamera->getWorldPosition()));
   
	int pointCount = 0;
	for (int i =0; i < pWorld->getLightCount(); i++)
    {
		
		//cout <<"lightcount ->> " << pWorld->getLightCount() << endl;

            Light* temp = pWorld->getLightAt(i);
        switch(temp->type){
            case Light::LightType::Directional:
			/*	dirCount++;*/
				//cout << "dasdasdasdas" << endl;
                glUniform3fv(_uDirLight_Dir,1, glm::value_ptr(((DirectionalLight*)temp)->direction));
                glUniform3fv(_uDirLight_Ambient,1, glm::value_ptr(temp->ambient));
                glUniform3fv(_uDirLight_Diffuse,1,glm::value_ptr(temp->diffuse));
                glUniform3fv(_uDirLight_Specular,1, glm::value_ptr(temp->specular));
                break;
            case Light::LightType::Point:
                {
                  pointCount++;
				 // std::cout <<"POINTCOUNT ->"<< pointCount << std::endl;
              //  std::string num = "pointLight[" + std::to_string(pointCount - 1) + "].";

                glUniform3fv(_uPointLight_Pos[pointCount - 1],1, glm::value_ptr(temp->getWorldPosition()));

                glUniform3fv(_uPointLight_Ambient[pointCount - 1],1, glm::value_ptr(temp->ambient));
                glUniform3fv(_uPointLight_Diffuse[pointCount - 1],1,glm::value_ptr(temp->diffuse));
                glUniform3fv(_uPointLight_Specular[pointCount - 1],1, glm::value_ptr(temp->specular));

          /*      glUniform1f (_shader->getUniformLocation(num + "constant"), 1.f);
                glUniform1f (_shader->getUniformLocation(num + "linear"), 0.09f);
                glUniform1f (_shader->getUniformLocation(num + "quadratic"), 0.032f);*/
                }
                break;
            case Light::LightType::Spot:
                {
					glUniform3fv(_uSpotLight_Pos, 1, glm::value_ptr(temp->getWorldPosition()));
					glUniform3fv(_uSpotLight_Dir, 1, glm::value_ptr(-temp->getWorldRight()));
					glUniform3fv(_uSpotLight_Ambient, 1, glm::value_ptr(temp->ambient));
					glUniform3fv(_uSpotLight_Diffuse, 1, glm::value_ptr(temp->diffuse));
					glUniform3fv(_uSpotLight_Specular, 1, glm::value_ptr(temp->specular));
					glUniform1f(_uSpotLight_Linear, 0.09f);
					glUniform1f(_uSpotLight_Quadratic, 0.032f);
					glUniform1f(_uSpotLight_InnerCutOff, _pointLightInnerCutOff);
					glUniform1f(_uSpotLight_OutterCutOff, _pointLightOuterCutOff);
                }
                break;
        }


    }

	//glUniform1i(_shader->getUniformLocation("spotLightCount"), spotCount);
	glUniform1i(_shader->getUniformLocation("pointLightCount"), pointCount);




    //pass in all MVP matrices separately
    glUniformMatrix4fv (_uProjMat,   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv (_uViewMat ,         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv (_uModelMat ,        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));

	/*glm::mat4 pvm = pCamera->getProjection() * glm::inverse(pCamera->getWorldTransform()) * pGameObject->getWorldTransform();
	glUniformMatrix4fv(_shader->getUniformLocation("pvm"), 1, GL_FALSE, glm::value_ptr(pvm));*/

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(
      _aVertex,_aNormal,_aUv,_aTangent
    );
}

