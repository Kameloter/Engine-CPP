#ifndef XMLREADER_H
#define XMLREADER_H
#include "pugixml.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "glm.hpp"

using namespace std;

class PhysicsWorld;
class StaticGameObject;
class XmlReader
{
    public:
            XmlReader(PhysicsWorld * pWorld);
            virtual ~XmlReader();
            void Read(const char* pFileName);
			void ReadInteractables(const char* pFileName);
            std::vector<pugi::xml_node> GetNodeChildren(pugi::xml_node node);
           // void LoadObjects();
            void SetupLevelGeometry(std::string pLevelName);
			void SetupInteractableGeometry(std::string pLevelName);

            std::vector<StaticGameObject *> objects;

            std::vector<std::string> _names;
            std::vector<std::string> _diffuseTextures;
            std::vector<std::string> _normalMaps;

            std::vector<glm::vec3> _positions;
            std::vector<glm::vec3> _scales;

			std::vector<std::string> _namesInteractables;
			std::vector<glm::vec3> _positionsInteractables;
			std::vector<glm::vec3> _rotationsInteractables;
			std::vector<int>  _typeInteractables;

			void LoadLevel(const char* pLevelName);
			void LoadInteractables(const char* pLevelName);

            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:
			PhysicsWorld* _world;
            pugi::xml_document _xmlFile;
			pugi::xml_document _xmlFileInteractables;

            std::vector<pugi::xml_node> _mainNodes;
            std::vector<pugi::xml_node> _objectProperties;

			std::vector<pugi::xml_node> _mainNodesInteractable;
			std::vector<pugi::xml_node> _interactableProperties;


};

#endif // XMLREADER_H
