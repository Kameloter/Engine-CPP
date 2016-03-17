#include "Player.h"

#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/behaviours/FPController.h"


Player::Player(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld, GameObject * cam):
 RigidbodyGameObject(pName,pPosition,pWorld), _cam(cam)
{
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube.obj");
	this->setMesh(cubeMeshF);
//	this->setMaterial(new ColorMaterial(glm::vec3(1,0,0)));
	this->setBehaviour(new FPController(60.0f, 1.0f, _cam, FPController::InputType::WASD));

	glm::vec3 center = this->getLocalPosition();
	glm::vec3 minbound(center.x - 0.5f, center.y - 1.5f, center.z - 1);
	glm::vec3 maxbound(center.x + 0.5f, center.y + 1.5f, center.z + 1);
	this->SetBounds(minbound, maxbound);

	this->AddBoxCollider(1, 1, 1);

	f32 mass = 10;
	_rigidbody->SetInertiaTensor(neBoxInertiaTensor(1,1,1, mass));
	_rigidbody->SetMass(mass);
	_rigidbody->SetAngularDamping(1.0f);
}


Player::~Player()
{
}
