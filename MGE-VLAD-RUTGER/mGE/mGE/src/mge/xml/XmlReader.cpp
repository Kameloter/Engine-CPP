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
#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/TextureNormalMaterial.hpp"

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

XmlReader::XmlReader(PhysicsWorld* pWorld) :
	_world(pWorld)
{
    
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

	cout << "Reading Level Data... - " << fullpath <<  endl;
    if(!_xmlFile.load_file(fullpath)) std::cout<<"Couldn't load the file"<<std::endl;
    pugi::xml_node root = _xmlFile.child("GameObjects");
   // std::cout<< "ROOT XML => " << root.name() << std::endl;
    _mainNodes = GetNodeChildren(root);
    //std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;
    for(int i=0; i!= _mainNodes.size();i++)
    {

        //Add names to a list
        _names.push_back(_mainNodes[i].attribute("name").value());

        //Read all object node children
        _objectProperties = GetNodeChildren(_mainNodes[i]);
        //Store positions
        _positions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[3].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Z").value())));
        //Store scales
        _scales.push_back(glm::vec3(StringToNumber<float>(_objectProperties[5].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Z").value())));

    }
	cout << "XML finished reading -- > " << _mainNodes.size() << " objects " << endl;
}
void XmlReader::LoadLevel(const char* pLevelName)
{
	Read(pLevelName);
	SetupLevelGeometry(pLevelName);
}

void XmlReader::SetupLevelGeometry(std::string pLevelName)
{
	cout << " Setting up level geometry..." << endl;
    //Create root geometry
    GameObject * root = new GameObject(pLevelName,glm::vec3(0,0,0));
    root->setMesh(Mesh::load(config::MGE_MODEL_PATH + pLevelName + ".obj"));

	root->setMaterial(new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + pLevelName + "_diff.png"), Texture::load(config::MGE_TEXTURE_PATH + pLevelName + "_norm.png"), 0.1));
	//root->setMaterial(new TextureNormalMaterial(Texture::load(config::MGE_TEXTURE_PATH + pLevelName + "_diff.png"),glm::vec3(1), 32, Texture::load(config::MGE_TEXTURE_PATH + pLevelName + "_norm.png")));
	//root->setMaterial(new ColorMaterial(glm::vec3(1, 0, 0)));
	_world->add(root);


    for(int i = 0; i < _names.size(); i++)
    {
			StaticGameObject* obj = new StaticGameObject(_names[i], _positions[i], _world);

			glm::vec3 boxColSize(_scales[i]);
			obj->AddBoxCollider(boxColSize.x,boxColSize.y, boxColSize.z);
            
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
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "statue.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0, 0)));
			obj->setBehaviour(new StatueBehaviour);
			dynamic_cast<StatueBehaviour*>(obj->getBehaviour())->SetPlayer(_world->getRigidObjects()[0]);
			_world->add(obj);
			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
		}
		break;
		case 1:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "pressurePlate.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0)));
			obj->setBehaviour(new PressurePlateBehaviour());
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			break;
		}
		case 2:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], glm::vec3( _positionsInteractables[i].x, _positionsInteractables[i].y - 1.0f, _positionsInteractables[i].z), _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "coin.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0)));

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);

			obj->setBehaviour(new CollectableBehaviour());
			_world->add(obj);
		}
		break;
		case 3:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "pushblock.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0.5f)));
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
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "traps.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0, 0)));
			obj->setBehaviour(new SpikeBehaviour());
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);
			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].z > 0) {
				obj->rotate(glm::radians(_rotationsInteractables[i].z), glm::vec3(0, 0, 1));
				std::cout << colSize << std::endl;
				obj->AddBoxCollider(colSize.x, colSize.z, colSize.y);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			dynamic_cast<SpikeBehaviour*>(obj->getBehaviour())->InitializePositions();


		}
		break;
		case 5:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "Spikes.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0)));
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].x > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}
		}
		break;
		case 6:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "key.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0)));
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());
			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);

			obj->setBehaviour(new CollectableBehaviour());
		}
		break;
		case 7:
		{
			/*StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "traps.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0.923f, 0)));
			_world->add(obj);*/
		}
		break;
		case 8:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "gate.obj"));
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

			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world, true);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "secret_path.obj"));
			obj->setMaterial(new ColorMaterial(glm::vec3(1, 0, 0)));
			_world->add(obj);

			glm::vec3 center2 = obj->getLocalPosition();
			glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
			glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
			obj->SetBounds(minbound2, maxbound2);

		
			glm::vec3 colSize = glm::vec3(obj->getMesh()->GetColliderSize());

			if (_rotationsInteractables[i].y > 0) {
				obj->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				obj->AddBoxCollider(colSize.z, colSize.y, colSize.x);
			}
			else
			{
				obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
			}

			obj->AddBoxCollider(colSize.x, colSize.y, colSize.z);
		}
		break;

		case 10:
		{
			Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
			_world->add(camera);
			_world->setMainCamera(camera);

			Player * player = new Player("Player", _positionsInteractables[i], _world, camera);
			_world->add(player);

			camera->setParent(player);
			camera->setLocalPosition(glm::vec3(0, 2, 0));
			camera->setBehaviour(new FPCamera(1.0f, 1.0f, player));
		}
		break;

		case 11:
		{
			StaticGameObject * obj = new StaticGameObject(_namesInteractables[i], _positionsInteractables[i], _world);
			obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "bridge.obj"));
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
		default:
			break;
		}

	}

	cout << "intactable geonmytry loaded.... " << endl;
}

