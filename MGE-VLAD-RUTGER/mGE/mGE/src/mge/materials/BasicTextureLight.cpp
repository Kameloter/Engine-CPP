#include <glm.hpp>

#include "mge/materials/BasicTextureLight.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/light/Light.h"
#include "mge/core/light/DirectionalLight.h"
#include "mge/core/light/PointLight.h"
#include "mge/config.hpp"

ShaderProgram* BasicTextureLit::_shader = NULL;

BasicTextureLit::BasicTextureLit(Texture * pDiffuseTexture, float pShininess) :
	_diffuseTexture(pDiffuseTexture), specMapOn(false), _specularTexture(0),_shininess(pShininess)
{
    _lazyInitializeShader();
}

BasicTextureLit::BasicTextureLit(Texture * pDiffuseTexture, Texture* pSpecularTexture, float pShininess) :
	_diffuseTexture(pDiffuseTexture), specMapOn(true), _specularTexture(pSpecularTexture),_shininess(pShininess)
{
	_lazyInitializeShader();
}

BasicTextureLit::~BasicTextureLit()
{
	//cout << "DESTROYED TextureLitMaterial "  << endl;
	//delete _shader;
	//_shader = NULL;

}

void BasicTextureLit::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"BasicLit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"BasicLit.fs");
        _shader->finalize();
    }
}

void BasicTextureLit::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void BasicTextureLit::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    if (!_diffuseTexture) return;

    _shader->use();

    // set texture slots
    _shader->setTexture(_shader->getUniformLocation("mat_diffuse"),0,_diffuseTexture->getId());
	//_shader->setTexture(_shader->getUniformLocation("mat_normal"), 1, _normalTexture->getId());
	if (specMapOn) {
		_shader->setTexture(_shader->getUniformLocation("mat_specular"), 2, _specularTexture->getId());
		glUniform1i(_shader->getUniformLocation("mat_useSpecMap"), 1);
	}
	else
	{
		glUniform1i(_shader->getUniformLocation("mat_useSpecMap"), 0);
	}
	// tell shader what specularity and shininess to use

    glUniform1f (_shader->getUniformLocation("mat_shininess"), _shininess);
	//Camera position --> needs optimization  
    glUniform3fv(_shader->getUniformLocation("cameraPosition"),1, glm::value_ptr( pCamera->getWorldPosition()));
   
	
	int pointCount = 0;
    int spotCount = 0;
	int dirCount = 0;

    for (int i =0; i < pWorld->getLightCount(); i++)
    {
		
		//cout <<"lightcount ->> " << pWorld->getLightCount() << endl;

            Light* temp = pWorld->getLightAt(i);
        switch(temp->type){
            case Light::LightType::Directional:
				dirCount++;
				//cout << "dasdasdasdas" << endl;
                glUniform3fv(_shader->getUniformLocation("dirLight.direction"),1, glm::value_ptr(((DirectionalLight*)temp)->direction));
                glUniform3fv(_shader->getUniformLocation("dirLight.ambient"),1, glm::value_ptr(temp->ambient));
                glUniform3fv(_shader->getUniformLocation("dirLight.diffuse"),1,glm::value_ptr(temp->diffuse));
                glUniform3fv(_shader->getUniformLocation("dirLight.specular"),1, glm::value_ptr(temp->specular));
                break;
    //        case Light::LightType::Point:
    //            {
    //              pointCount++;
				// // std::cout <<"POINTCOUNT ->"<< pointCount << std::endl;
    //            std::string num = "pointLight[" + std::to_string(pointCount - 1) + "].";

    //            glUniform3fv(_shader->getUniformLocation(num + "position"),1, glm::value_ptr(temp->getWorldPosition()));
				////glUniform3fv(_shader->getUniformLocation(num + "direction"), 1, glm::value_ptr(-temp->getUp()));

    //            glUniform3fv(_shader->getUniformLocation(num + "ambient"),1, glm::value_ptr(temp->ambient));
    //            glUniform3fv(_shader->getUniformLocation(num + "diffuse"),1,glm::value_ptr(temp->diffuse));
    //            glUniform3fv(_shader->getUniformLocation(num + "specular"),1, glm::value_ptr(temp->specular));

    //            glUniform1f (_shader->getUniformLocation(num + "constant"), 1.f);
    //            glUniform1f (_shader->getUniformLocation(num + "linear"), 0.09f);
    //            glUniform1f (_shader->getUniformLocation(num + "quadratic"), 0.032f);
    //            }
    //            break;
            case Light::LightType::Spot:
                {
					spotCount++;
                    std::string num = "spotLight[" + std::to_string(spotCount - 1) + "].";

                    glUniform3fv(_shader->getUniformLocation(num + "position"),1, glm::value_ptr(temp->getWorldPosition()));
					glUniform3fv(_shader->getUniformLocation(num + "direction"), 1, glm::value_ptr(-temp->getWorldRight()));
                    glUniform3fv(_shader->getUniformLocation(num + "ambient"),1, glm::value_ptr(temp->ambient));
                    glUniform3fv(_shader->getUniformLocation(num + "diffuse"),1,glm::value_ptr(temp->diffuse));
                    glUniform3fv(_shader->getUniformLocation(num + "specular"),1, glm::value_ptr(temp->specular));
                    glUniform1f (_shader->getUniformLocation(num + "constant"), 1.f);
                    glUniform1f (_shader->getUniformLocation(num + "linear"), 0.09f);
                    glUniform1f (_shader->getUniformLocation(num + "quadratic"), 0.032f);
					glUniform1f(_shader->getUniformLocation(num + "innerCircle"), glm::cos(glm::radians(14.5f)));
					glUniform1f(_shader->getUniformLocation(num +"outerCircle"), glm::cos(glm::radians(18.5f)));
                }
                break;
        }


    }

	//glUniform1i(_shader->getUniformLocation("spotLightCount"), spotCount);
//	glUniform1i(_shader->getUniformLocation("pointLightCount"), pointCount);
	if(dirCount==1)
		glUniform1i(_shader->getUniformLocation("calculateDirLight"), 1);
	else
		glUniform1i(_shader->getUniformLocation("calculateDirLight"), 0);

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_Proj"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_View"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("mat_Model"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform()));

	glm::mat4 pvm = pCamera->getProjection() * glm::inverse(pCamera->getWorldTransform()) * pGameObject->getWorldTransform();
	glUniformMatrix4fv(_shader->getUniformLocation("pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
		
    );
}

