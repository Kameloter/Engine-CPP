#include "XmlReader.h"
#include "mge/config.hpp"

#include "mge/LUA/LUAManager.h"

#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/TextureNormalMaterial.hpp"

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
