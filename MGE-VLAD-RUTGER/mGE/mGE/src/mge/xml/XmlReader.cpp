#include "XmlReader.h"
#include "mge/config.hpp"
#include "mge/core/collision/StaticGameObject.h"

#include "mge/core/collision/PhysicsWorld.h"

XmlReader::XmlReader()
{
    Read();
}

XmlReader::~XmlReader()
{
    //dtor
}

void XmlReader::Read()
{
     int counter;
  //  pugi::xml_parse_result result = ;
    if(!_xmlFile.load_file("assets/mge/xml/level.xml")) std::cout<<"Couldn't load the file"<<std::endl;

    pugi::xml_node root = _xmlFile.child("GameObjects");
   // std::cout<< "ROOT XML => " << root.name() << std::endl;

    _mainNodes = GetNodeChildren(root);
    std :: cout << "SIZE OF ROOT CHILDREN = > " << _mainNodes.size() << std::endl;

    for(counter=0; counter!= _mainNodes.size();counter++)
    {

        //Add names to a list
        _names.push_back(_mainNodes[counter].attribute("name").value());

        //Read all object node children
        _objectProperties = GetNodeChildren(_mainNodes[counter]);
        //Store positions
        _positions.push_back(glm::vec3(StringToNumber<float>(_objectProperties[3].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[3].attribute("Z").value())));
        //Store scales
        _scales.push_back(glm::vec3(StringToNumber<float>(_objectProperties[5].attribute("X").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Y").value()),
                                            StringToNumber<float>(_objectProperties[5].attribute("Z").value())));

    }
}

void XmlReader::SetupLevelGeometry(PhysicsWorld * pPhysicsWorld)
{
    //Create root geometry
    GameObject * root = new GameObject("Level1_geometry",glm::vec3(0,0,0));
    root->setMesh(Mesh::load(config::MGE_MODEL_PATH + "level_mesh.obj"));

    root->setMaterial(new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"test.jpg"),32.f));
	pPhysicsWorld->add(root);


	//GameObject* cube = new GameObject("cube", glm::vec3(0, 0, 0));
	//cube->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube.obj"));
	//cube->setMaterial(new ColorMaterial(glm::vec3(0,0,1)));
	//pPhysicsWorld->add(cube);


	//GameObject* cube2 = new GameObject("cube2", glm::vec3(0, 0, 1));
	//cube2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube.obj"));
	//cube2->setMaterial(new ColorMaterial(glm::vec3(0, 0, 1)));
	//pPhysicsWorld->add(cube2);

	//GameObject* cube3 = new GameObject("cube3", glm::vec3(0, 0, 2));
	//cube3->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube.obj"));
	//cube3->setMaterial(new ColorMaterial(glm::vec3(0, 0, 1)));
	//pPhysicsWorld->add(cube3);


    for(int i = 0; i < _names.size(); i++)
    {

       // if(_names[i] == "Wallcoll_9")
      //  {
			StaticGameObject * obj = new StaticGameObject(_names[i],_positions[i]/2.0f, pPhysicsWorld);
			//obj->setMesh(cubeMeshF);
			//glm::vec3 colliderSize = obj->getMesh()->GetColliderSize();
			//obj->setMaterial(new ColorMaterial(Color::ForestGreen));
			//_world->add(obj);
           //   std::cout<< "bla" << std::endl;
           // GameObject * obj = new GameObject(_names[i],_positions[i]);  //original
            glm::vec3 boxColSize(_scales[i]);
             //   std::cout<< "cOL SIZE " << _scales[i] << std::endl;
            glm::vec3 halfSize = boxColSize * .5f;
              //  std::cout<< "Half " << halfSize << std::endl;
            glm::vec3 offset = obj->getLocalPosition();

            glm::vec3 minBounds(offset.x - halfSize.x,
                                offset.y - halfSize.y,
                                offset.z - halfSize.z);
            glm::vec3 maxBounds(offset.x + halfSize.x,
                                offset.y + halfSize.y,
                                offset.z + halfSize.z);
			obj->SetBounds(maxBounds, minBounds);

				cout <<"localpos "<< obj->getLocalPosition()<< "worldPos " << obj->getWorldPosition()<< endl;
				cout << "minbound " << minBounds << "maxbound " << maxBounds << endl;
			obj->AddBoxCollider(boxColSize.x, boxColSize.y, boxColSize.z);
          // obj->setCollider(new BoxCollider(minBounds,maxBounds));
            objects.push_back(obj);
			pPhysicsWorld->add(obj);
    //    }

    }
}
void XmlReader::SetupObjects()
{
  //  for(int i = 0; i < _names.size(); i++)
  //  {
  //      GameObject * obj = new GameObject(_names[i],_positions[i]);  //original
  //      obj->setMesh(Mesh::load(config::MGE_MODEL_PATH  + "Cubet.obj"));
  //      obj->setMaterial(new ColorMaterial());
  //      obj->scale(_scales[i]);

  //      glm::vec3 boxColSize(_scales[i]);
  //      //boxColSize.x *= -1;
  //      glm::vec3 halfSize = boxColSize * .5f;

  //      glm::vec3 offset = obj->getLocalPosition();

  //      glm::vec3 minBounds(offset.x - halfSize.x,
  //                          offset.y - halfSize.y,
  //                          offset.z - halfSize.z);
  //      glm::vec3 maxBounds(offset.x + halfSize.x,
  //                          offset.y + halfSize.y,
  //                          offset.z + halfSize.z);

		////obj-
  //      obj->setCollider(new BoxCollider(minBounds,maxBounds));
  //      objects.push_back(obj);
  //      //_collisionManager->addObject(colCube);
  //  }
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
