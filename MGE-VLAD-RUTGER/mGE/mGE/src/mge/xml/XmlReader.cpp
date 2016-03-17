#include "XmlReader.h"
#include "mge/config.hpp"

#include "mge/LUA/LUAManager.h"
#include "mge/core/Camera.hpp"

#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/Player.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/BasicTextureLight.hpp"
#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/TextureNormalMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

#include "mge/core/light/SpotLight.h"
#include "mge/core/light/PointLight.h"

//behaviours for objects
#include "mge/behaviours/StatueBehaviour.h"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/BoxBehaviour.h"
#include "mge/behaviours/DoorBehaviour.h"
#include "mge/behaviours/TriggerBehaviour.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/behaviours/CollectableBehaviour.h"
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge/behaviours/PushBlockBehaviour.h"
#include "mge/behaviours/SpikeBehaviour.h"
#include "mge/behaviours/SubtitleBehaviour.h"
#include "mge/behaviours/DeathBehaviour.h"
#include "mge/SubtitleManager.h"
#include "mge/behaviours/SceneSwitchBehaviour.h"
#include "mge/behaviours/GhostBehaviour.h"
#include "mge/behaviours/BrokenBridgeBehaviour.h"
#include "mge/behaviours/TrapTriggerBehaviour.h"
#include "mge/behaviours/SpawnPointBehaviour.h"

#include "mge/materials/TerrainMaterial.hpp" 

AbstractMaterial * pressurePlateMaterial;
AbstractMaterial * statueMaterial;
AbstractMaterial * coinMaterial;
AbstractMaterial * pushBlockMaterial;
AbstractMaterial * spikesMaterial;
AbstractMaterial * keyMaterial;
AbstractMaterial * hiddenPassageMaterial;
AbstractMaterial * flashLightMaterial;
AbstractMaterial * coffinMaterial;
AbstractMaterial * gateBigMaterial;
AbstractMaterial * bridge1Material;
AbstractMaterial * stepMaterial;
AbstractMaterial * terrainMaterial;
AbstractMaterial * spikeWallMaterial;
AbstractMaterial * brokenBridgeMaterial;
AbstractMaterial * pedeStalMaterial;
AbstractMaterial * torchMaterial;
AbstractMaterial * ghostMaterial;
AbstractMaterial * ghostBackMaterial;


XmlReader::XmlReader(PhysicsWorld* pWorld) :
	_world(pWorld)
{
	pressurePlateMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "pplatebird_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "pplatebird_NRM.png"), 0.1f);
	statueMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "statue_DIFF (TEMP).png"), Texture::load(config::MGE_TEXTURE_PATH + "statue_NRM.png"), 0.1f);
	coinMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "coin_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "coin_NRM.png"), 0.1f);
	pushBlockMaterial = new BasicTextureLit(Texture::load(config::MGE_TEXTURE_PATH + "pushblock_DIFF(TEMP).png"), 0.1f);
	spikesMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "spikes_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "trap_normal.jpg"), 0.1f);
	keyMaterial = new BasicTextureLit(Texture::load(config::MGE_TEXTURE_PATH + "keyred_DIFF.png"), 0.1f);
	hiddenPassageMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "hiddenpassage_DIFF (TEMP, tiled).png"), Texture::load(config::MGE_TEXTURE_PATH + "hiddenpassage_NRM.png"), 0.1f);
	flashLightMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Flashlight_diffuse.jpg"), Texture::load(config::MGE_TEXTURE_PATH + "Flashlight_normal.jpg"), Texture::load(config::MGE_TEXTURE_PATH + "Flashlight_specular.jpg"), 0.1f);
	coffinMaterial = new BasicTextureLit(Texture::load(config::MGE_TEXTURE_PATH + "coffin_DIFF(TEMP).png"), 0.1f);
	gateBigMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "gatebig_DIFF (TEMP).png"), Texture::load(config::MGE_TEXTURE_PATH + "gatebig_NRM.png"), 0.1f);
	bridge1Material = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bridgelv1_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "bridgelv1_NRM.png"), 0.1f);
	stepMaterial = new BasicTextureLit(Texture::load(config::MGE_TEXTURE_PATH + "step_DIFF.png"), 0.1f);
	terrainMaterial = new TerrainMaterial(Texture::load(config::MGE_TEXTURE_PATH + "lava.jpg"));
	spikeWallMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "spikescover_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "spikescover_NRM.png"), 0.1f);
	brokenBridgeMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "brokenbridge_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "brokenbridge_NRM.png"), 0.1f);
	pedeStalMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "pedestal_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "pedestal_NRM.png"), 0.1f);
	torchMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "torch_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "torch_NRM.png"), 0.1f);
	ghostMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Ghost_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "Ghost_NRM.png"), 0.1f);
	ghostBackMaterial = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "ghostback_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "ghostback_NRM.png"), 0.1f);

}

XmlReader::~XmlReader()
{
	//dtor
}

void XmlReader::Read(const char* pFileName)
{
	std::string path = config::MGE_XML_PATH;
	path += pFileName;
	path += ".xml";
	const char* fullpath = path.c_str();

	cout << "Reading Level Data... - " << fullpath << endl;
	if (!_xmlFile.load_file(fullpath)) std::cout << "Couldn't load the file" << std::endl;
	pugi::xml_node root = _xmlFile.child("GameObjects");
	// std::cout<< "ROOT XML => " << root.name() << std::endl;
	_mainNodes = GetNodeChildren(root);
	//std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;
	for (int i = 0; i != _mainNodes.size(); i++)
	{

		//Add names to a list
		_names.push_back(_mainNodes[i].attribute("name").value());

		//Read all object node children
		_objectProperties = GetNodeChildren(_mainNodes[i]);
		//Store positions
		_positions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[0].attribute("X").value()),
			StringToNumber<float>(_objectProperties[0].attribute("Y").value()),
			StringToNumber<float>(_objectProperties[0].attribute("Z").value())));
		//Store scales
		_scales.push_back(glm::vec3(StringToNumber<float>(_objectProperties[1].attribute("X").value()),
			StringToNumber<float>(_objectProperties[1].attribute("Y").value()),
			StringToNumber<float>(_objectProperties[1].attribute("Z").value())));

	}
	cout << "XML finished reading -- > " << _mainNodes.size() << " objects " << endl;
}
void XmlReader::LoadLevel(const char* pLevelName)
{
	Read(pLevelName);
	SetupLevelGeometry(pLevelName);
	//clean yup xml lists
}

void XmlReader::SetupLevelGeometry(std::string pLevelName)
{
	cout << " Setting up level geometry..." << endl;
	//Create root geometry
	GameObject * root = new GameObject(pLevelName, glm::vec3(0, 0, 0));
	root->setMesh(Mesh::load(config::MGE_MODEL_PATH + pLevelName + ".obj"));

	root->setMaterial(new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + pLevelName + "_diff.png"), Texture::load(config::MGE_TEXTURE_PATH + "level_norm.png"), 0.1f));

	_world->add(root);

	GameObject * sand = new GameObject(pLevelName + "sand" + ".obj", glm::vec3(0, 0, 0));
	sand->setMesh(Mesh::load(config::MGE_MODEL_PATH + pLevelName + "_sand" + ".obj"));

	sand->setMaterial(new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "sand_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "sand_NRM.png"), 0.1f));
	_world->add(sand);

	GameObject * ceiling = new GameObject(pLevelName + "ceiling" + ".obj", glm::vec3(0, 0, 0));
	ceiling->setMesh(Mesh::load(config::MGE_MODEL_PATH + pLevelName + "_ceiling" + ".obj"));
	ceiling->setMaterial(new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "ceiling_DIFF.png"), Texture::load(config::MGE_TEXTURE_PATH + "ceiling_NRM.png"), 0.1f));
	_world->add(ceiling);

	for (int i = 0; i < _names.size(); i++)
	{
		StaticGameObject* obj = new StaticGameObject(_names[i], _positions[i], _world);

		glm::vec3 boxColSize(_scales[i]);
		obj->AddBoxCollider(boxColSize.x, boxColSize.y, boxColSize.z);

		objects.push_back(obj);
		_world->add(obj);
	}
	cout << "Level geometry loaded .... " << endl;
}

std::vector<pugi::xml_node> XmlReader::GetNodeChildren(pugi::xml_node node)
{
	std::vector<pugi::xml_node> values;

	for (node = node.first_child(); node; node = node.next_sibling()) {
		values.push_back(node);
	}

	return values;
}

template<typename T>
T XmlReader::StringToNumber(const std::string& numberAsString)
{
	T value;
	std::stringstream stream(numberAsString);
	stream >> value;
	return value;
}

void XmlReader::LoadInteractables(const char* pName)
{
	ReadInteractables(pName);
	SetupInteractableGeometry(pName);
	//clean yup xml lists
}

void XmlReader::LoadSubtitleTriggers(const char * pLevelName)
{
	ReadSubtitleTriggers(pLevelName);
	SetupSubtitleTriggers(pLevelName);
	//clean yup xml lists
}

void XmlReader::ReadInteractables(const char* pFileName)
{
	std::string path = config::MGE_XML_PATH;
	path += pFileName;
	path += ".xml";
	const char* fullpath = path.c_str();

	cout << "Reading interactable Data... - " << fullpath << endl;
	if (!_xmlFileInteractables.load_file(fullpath)) std::cout << "Couldn't load the file" << std::endl;
	pugi::xml_node root = _xmlFileInteractables.child("GameObjects");
	//std::cout<< "ROOT XML => " << root.name() << std::endl;
	_mainNodesInteractable = GetNodeChildren(root);
	//std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;
	for (int i = 0; i != _mainNodesInteractable.size(); i++)
	{

		//Add names to a list
		_namesInteractables.push_back(_mainNodesInteractable[i].attribute("name").value());


		//Read all object node children
		_interactableProperties = GetNodeChildren(_mainNodesInteractable[i]);
		//Store positions
		_positionsInteractables.push_back(glm::vec3(StringToNumber<float>(_interactableProperties[0].attribute("X").value()),
			StringToNumber<float>(_interactableProperties[0].attribute("Y").value()),
			StringToNumber<float>(_interactableProperties[0].attribute("Z").value())));

		_rotationsInteractables.push_back(glm::vec3(StringToNumber<float>(_interactableProperties[1].attribute("X").value()),
			StringToNumber<float>(_interactableProperties[1].attribute("Y").value()),
			StringToNumber<float>(_interactableProperties[1].attribute("Z").value())));

		_typeInteractables.push_back(StringToNumber<int>(_interactableProperties[2].attribute("Type").value()));
	}
	cout << "XML finished reading -- > " << _mainNodesInteractable.size() << " objects " << endl;
}



void XmlReader::SetupInteractableGeometry(std::string pLevelName)
{
	cout << " Setting up level geometry..." << endl;

	for (int i = 0; i < _namesInteractables.size(); i++)
	{
		switch (_typeInteractables[i])
		{
		case 0:
		{
			RigidbodyGameObject * obj = new RigidbodyGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "statue.obj"));
			obj->setMaterial(statueMaterial);
			obj->setBehaviour(new StatueBehaviour());

			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			glm::vec3 center = obj->getLocalPosition();

			glm::vec3 minbound(center.x - colSize.x / 2, center.y - colSize.y / 2, center.z - colSize.z / 2);
			glm::vec3 maxbound(center.x + colSize.x / 2, center.y + colSize.y / 2, center.z + colSize.z / 2);
			obj->SetBounds(minbound, maxbound);

			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);

			f32 mass = 30;
			obj->GetRigidBody()->SetInertiaTensor(neBoxInertiaTensor(colSize.x, colSize.y, colSize.z, mass));
			obj->GetRigidBody()->SetMass(mass);
			obj->GetRigidBody()->SetAngularDamping(1.0f);
		}
		break;
		case 1:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);

			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "pressurePlate.obj"));
			obj->setMaterial(pressurePlateMaterial);

			obj->setBehaviour(new PressurePlateBehaviour(_world));
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.2f, center2.y - 1.5f, center2.z - 0.2f);
			glm::vec3 maxbound2(center2.x + 0.2f, center2.y + 1.5f, center2.z + 0.2f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			break;
		}
		case 2:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], glm::vec3(_positionsInteractables[i].x, _positionsInteractables[i].y - 1.0f, _positionsInteractables[i].z), _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "coin.obj"));
			obj->setMaterial(coinMaterial);


			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);

			obj->setBehaviour(new CollectableBehaviour(false));
			_world->add(obj);
		}
		break;
		case 3:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "pushblock.obj"));
			obj->setMaterial(pushBlockMaterial);
			obj->setBehaviour(new PushBlockBehaviour());

			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			dynamic_cast<PushBlockBehaviour*>(obj->getBehaviour())->InitializePositions();
		}
		break;
		case 4:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "SpikesWall.obj"));
			obj->setMaterial(spikesMaterial);

			obj->setBehaviour(new SpikeBehaviour(true));
			_world->add(obj);

			StaticGameObject * obj2 = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "CoverWalls.obj"));
			obj2->setMaterial(spikeWallMaterial);

			_world->add(obj2);

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));
				obj2->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.z, center2.y - colSize.x, center2.z - colSize.x);
				glm::vec3 maxbound2(center2.x + colSize.z, center2.y + colSize.x, center2.z + colSize.x);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			else
			{
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.x, center2.y - colSize.y, center2.z - colSize.z);
				glm::vec3 maxbound2(center2.x + colSize.x, center2.y + colSize.y, center2.z + colSize.z);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			obj2->translate(obj2->getWorldForward() * -2.5f);

			dynamic_cast<SpikeBehaviour*>(obj->getBehaviour())->InitializePositions();

		}
		break;

		case 5:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "pushblock2.obj"));
			obj->setMaterial(pushBlockMaterial);
			obj->setBehaviour(new PushBlockBehaviour());

			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			dynamic_cast<PushBlockBehaviour*>(obj->getBehaviour())->InitializePositions();
		}
		break;

		case 6:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "key1.obj"));
			obj->setMaterial(keyMaterial);

			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);

			obj->setBehaviour(new CollectableBehaviour(true));
		}
		break;

		case 7:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "SpikesWall.obj"));
			obj->setMaterial(spikesMaterial);

			obj->setBehaviour(new SpikeBehaviour(false));
			_world->add(obj);

			StaticGameObject * obj2 = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "CoverWalls.obj"));
			obj2->setMaterial(spikeWallMaterial);

			_world->add(obj2);

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));
				obj2->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.z, center2.y - colSize.x, center2.z - colSize.x);
				glm::vec3 maxbound2(center2.x + colSize.z, center2.y + colSize.x, center2.z + colSize.x);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			else
			{
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.x, center2.y - colSize.y, center2.z - colSize.z);
				glm::vec3 maxbound2(center2.x + colSize.x, center2.y + colSize.y, center2.z + colSize.z);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			obj2->translate(obj2->getWorldForward() * -2.5f);

			dynamic_cast<SpikeBehaviour*>(obj->getBehaviour())->InitializePositions();
		}
		break;

		case 8:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Gate2x2.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0)));

			obj->setBehaviour(new DoorBehaviour());
			dynamic_cast<DoorBehaviour*>(obj->getBehaviour())->InitializePositions();

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			_world->add(obj);

		}
		break;

		case 9:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, false);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "secret_path.obj"));
			obj->setMaterial(hiddenPassageMaterial);

			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0)
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));

		}
		break;

		case 10:
		{
			Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
			_world->add(camera);
			_world->setMainCamera(camera);

			Player * player = new Player("Player", _positionsInteractables[i], _world, camera);
			player->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));
			_world->add(player);

			camera->setParent(player);
			camera->setLocalPosition(glm::vec3(0, 2, 0));
			camera->setBehaviour(new FPCamera(1.0f, 1.0f, player));

			StaticGameObject * flashLight = new StaticGameObject("FLASHLIGHT - OBJECT", glm::vec3(0, 0, 0), _world, true);
			_world->add(flashLight);
			flashLight->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Flashlight.obj"));
			flashLight->setMaterial(flashLightMaterial);

			flashLight->setParent(camera);
			flashLight->setLocalPosition(camera->getForward() - glm::vec3(0, 0.5f, 0) + camera->getRight() / 2.0f);

			flashLight->scale(glm::vec3(0.1f));
			flashLight->rotate(glm::radians(-90.f), glm::vec3(0, 1, 0));

			Light *slight = new SpotLight("FLASHLIGHT - POINT LIGHT", glm::vec3(40, 2, 35), glm::vec3(.3), glm::vec3(1, 1, 1), glm::vec3(0.1));
			_world->add(slight);
			slight->setParent(flashLight);
			slight->setLocalPosition(-2.5f * flashLight->getForward());
			_world->AddLight(slight);

		}
		break;

		case 11:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Bridge1.obj"));
			obj->setMaterial(bridge1Material);

			obj->setBehaviour(new DoorBehaviour());
			dynamic_cast<DoorBehaviour*>(obj->getBehaviour())->InitializePositions();

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			_world->add(obj);
		}
		break;

		case 12:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, false);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Stairs.obj"));
			obj->setMaterial(stepMaterial);
			obj->rotate(glm::radians(_rotationsInteractables[i].y) , glm::vec3(0,1,0));
			_world->add(obj);
		}
		break;

		case 13:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, false);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Step.obj"));
			obj->setMaterial(stepMaterial);
			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
		}
		break;

		case 14:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "coffin_01.obj"));
			obj->setMaterial(coffinMaterial);

			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
		}
		break;

		case 15:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Ghost.obj"));
			obj->setMaterial(ghostMaterial);
			obj->setBehaviour(new GhostBehaviour());
			obj->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
			_world->add(obj);

			StaticGameObject * obj2 = new StaticGameObject(_namesInteractables[i] + "back", _positionsInteractables[i], _world, true);
			obj2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "ghostback.obj"));
			obj2->setMaterial(ghostBackMaterial);
			_world->add(obj2);

			obj2->setParent(obj);
			obj2->setLocalPosition(glm::vec3(0));

			if (_rotationsInteractables[i].z > 0) {
				obj->rotate(glm::radians(_rotationsInteractables[i].z), glm::vec3(0, 0, 1));
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.y, center2.y - colSize.x, center2.z - colSize.z);
				glm::vec3 maxbound2(center2.x + colSize.y, center2.y + colSize.x, center2.z + colSize.z);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			else
			{
				glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize() / 2);
				glm::vec3 center2 = obj->getLocalPosition();
				glm::vec3 minbound2(center2.x - colSize.x, center2.y - colSize.y, center2.z - colSize.z);
				glm::vec3 maxbound2(center2.x + colSize.x, center2.y + colSize.y, center2.z + colSize.z);
				obj->SetBounds(glm::vec3(minbound2.x, minbound2.y, minbound2.z), glm::vec3(maxbound2.x, maxbound2.y, maxbound2.z));
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
		}
		break;
		case 16:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "bridge_broken_01.obj"));
			obj->setMaterial(brokenBridgeMaterial);


			_world->add(obj);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}


			glm::vec3 triggerPos = _positionsInteractables[i] + glm::vec3(0, 0.5f, 0);
			StaticGameObject * trigger = new StaticGameObject(_namesInteractables[i] + "trigger", _positionsInteractables[i], _world, true);

			glm::vec3 center2 = trigger->getLocalPosition();
			glm::vec3 minbound2(center2.x - 1.0f, center2.y - 1.0f, center2.z - 1.0f);
			glm::vec3 maxbound2(center2.x + 1.0f, center2.y + 1.0f, center2.z + 1.0f);
			trigger->SetBounds(minbound2, maxbound2);

			trigger->AddBoxCollider(1, 1, 1);

			trigger->setBehaviour(new BrokenBridgeBehaviour(obj));
			_world->add(trigger);

		}
		break;

		case 17:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "gate3x3.obj"));
			obj->setMaterial(gateBigMaterial);

			obj->setBehaviour(new DoorBehaviour());
			dynamic_cast<DoorBehaviour*>(obj->getBehaviour())->InitializePositions();

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			_world->add(obj);

		}
		break;

		case 18:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Torch.obj"));
			obj->setMaterial(torchMaterial);
			obj->rotate(glm::radians(_rotationsInteractables[i].y), glm::vec3(0, 1, 0));

			PointLight  * pointLight = new PointLight("pointLight", glm::vec3(_positionsInteractables[i]), glm::vec3(1,0.7f,0), glm::vec3(1,0.7f,0), glm::vec3(0.1f));
			_world->add(pointLight);
			_world->AddLight(pointLight);

			_world->add(obj);
		}
		break;

		case 20:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Fence.obj"));
			obj->setMaterial(gateBigMaterial);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
			_world->add(obj);

		}
		break;

		default:
			break;
		}
		std::cout << "loaded-> " << _namesInteractables[i] << std::endl;
	}

	cout << "Interactable geometry loaded.... " << endl;
}
void XmlReader::ReadSubtitleTriggers(const char * pFilename)
{
	std::string path = config::MGE_XML_PATH;
	path += pFilename;
	path += ".xml";
	const char* fullpath = path.c_str();

	cout << "Reading Subtitles Data... - " << fullpath << endl;
	if (!_xmlSubtitle.load_file(fullpath)) std::cout << "Couldn't load the file" << std::endl;
	pugi::xml_node root = _xmlSubtitle.child("GameObjects");
	_subtitleMainNodes = GetNodeChildren(root);

	for (int i = 0; i != _subtitleMainNodes.size(); i++)
	{
		//Add names to a list
		_subtitleTriggerName.push_back(_subtitleMainNodes[i].attribute("name").value());

		//Read all object node children
		_subtitleProperties = GetNodeChildren(_subtitleMainNodes[i]);
		//Store positions
		_subtitleTriggerPosition.push_back(glm::vec3(StringToNumber<float>(_subtitleProperties[0].attribute("X").value()),
			StringToNumber<float>(_subtitleProperties[0].attribute("Y").value()),
			StringToNumber<float>(_subtitleProperties[0].attribute("Z").value())));

		_subtitleTriggerSize.push_back(glm::vec3(StringToNumber<float>(_subtitleProperties[1].attribute("X").value()),
			StringToNumber<float>(_subtitleProperties[1].attribute("Y").value()),
			StringToNumber<float>(_subtitleProperties[1].attribute("Z").value())));

		_typeTriggers.push_back(StringToNumber<int>(_subtitleProperties[2].attribute("Type").value()));
		std::cout << _typeTriggers[i] << std::endl;
	}
	cout << "XML finished reading -- > " << _subtitleMainNodes.size() << " objects " << endl;
}
void XmlReader::SetupSubtitleTriggers(std::string pLevelname)
{
	for (int i = 0; i < _subtitleTriggerName.size(); i++)
	{
		switch (_typeTriggers[i])
		{

		case 0: //Subtitle tirgger
		{
			StaticGameObject * obj = new StaticGameObject(_subtitleTriggerName[i], _subtitleTriggerPosition[i], _world, true);
			_world->add(obj);

			std::cout << _subtitleTriggerPosition[i].x << std::endl;

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 triggerSize = _subtitleTriggerSize[i] / 2;
			glm::vec3 minbound2(center2.x - triggerSize.x, center2.y - triggerSize.y, center2.z - triggerSize.z);
			glm::vec3 maxbound2(center2.x + triggerSize.x, center2.y + triggerSize.y, center2.z + triggerSize.z);
			obj->SetBounds(minbound2, maxbound2);

			obj->AddBoxCollider(0, 0, 0);

			obj->setBehaviour(new SubtitleBehaviour());
			std::cout << " Sub triggaas added " << std::endl;
		}
		break;
		case 1: //Death trigger
		{

			StaticGameObject * obj = new StaticGameObject(_subtitleTriggerName[i], _subtitleTriggerPosition[i], _world, true);
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 triggerSize = _subtitleTriggerSize[i] / 2;
			glm::vec3 minbound2(center2.x - triggerSize.x, center2.y - triggerSize.y, center2.z - triggerSize.z);
			glm::vec3 maxbound2(center2.x + triggerSize.x, center2.y + triggerSize.y, center2.z + triggerSize.z);
			obj->SetBounds(minbound2, maxbound2);

			obj->AddBoxCollider(0, 0, 0);
			obj->setMaterial(terrainMaterial);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "lava_mesh.obj"));
			obj->setBehaviour(new DeathBehaviour());

		}
		break;

		case 2: //Scene switcher
		{
			StaticGameObject * obj = new StaticGameObject(_subtitleTriggerName[i], _subtitleTriggerPosition[i], _world, true);
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 triggerSize = _subtitleTriggerSize[i] / 2;
			glm::vec3 minbound2(center2.x - triggerSize.x, center2.y - triggerSize.y, center2.z - triggerSize.z);
			glm::vec3 maxbound2(center2.x + triggerSize.x, center2.y + triggerSize.y, center2.z + triggerSize.z);
			obj->SetBounds(minbound2, maxbound2);

			obj->AddBoxCollider(0, 0, 0);

			obj->setBehaviour(new SceneSwitchBehaviour());

		}
		break;

		case 3: //checkpoint
		{
			StaticGameObject * obj = new StaticGameObject(_subtitleTriggerName[i], _subtitleTriggerPosition[i], _world, true);
			_world->add(obj);


			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 triggerSize = _subtitleTriggerSize[i] / 2;
			glm::vec3 minbound2(center2.x - triggerSize.x, center2.y - triggerSize.y, center2.z - triggerSize.z);
			glm::vec3 maxbound2(center2.x + triggerSize.x, center2.y + triggerSize.y, center2.z + triggerSize.z);

			std::cout << minbound2 << maxbound2 << std::endl;
			obj->SetBounds(minbound2, maxbound2);


			obj->AddBoxCollider(0, 0, 0);

			obj->setBehaviour(new SpawnPointBehaviour());

		}
		break;

		case 4: //traptrigger
		{
			StaticGameObject * obj = new StaticGameObject(_subtitleTriggerName[i], _subtitleTriggerPosition[i], _world, true);
			_world->add(obj);


			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 triggerSize = _subtitleTriggerSize[i] / 2;
			glm::vec3 minbound2(center2.x - triggerSize.x, center2.y - triggerSize.y, center2.z - triggerSize.z);
			glm::vec3 maxbound2(center2.x + triggerSize.x, center2.y + triggerSize.y, center2.z + triggerSize.z);

			std::cout << minbound2 << maxbound2 << std::endl;
			obj->SetBounds(minbound2, maxbound2);


			obj->AddBoxCollider(0, 0, 0);

			obj->setBehaviour(new TrapTriggerBehaviour());

		}
		break;
		}


	}
}

