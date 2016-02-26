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
			void ReadSubtitleTriggers(const char* pFilename);
			
            std::vector<pugi::xml_node> GetNodeChildren(pugi::xml_node node);
           // void LoadObjects();
            void SetupLevelGeometry(std::string pLevelName);
			void SetupInteractableGeometry(std::string pLevelName);
			void SetupSubtitleTriggers(std::string pLevelname);

            std::vector<StaticGameObject *> objects;

            std::vector<std::string> _names;
            std::vector<std::string> _diffuseTextures;
            std::vector<std::string> _normalMaps;

            std::vector<glm::vec3> _positions;
            std::vector<glm::vec3> _scales;

			std::vector<std::string> _namesInteractables;
			std::vector<glm::vec3> _positionsInteractables;
			std::vector<glm::vec3> _rotationsInteractables;


			std::vector<std::string> _subtitleTriggerName;
			std::vector<glm::vec3> _subtitleTriggerPosition;
			std::vector<glm::vec3> _subtitleTriggerSize;

			std::vector<int>  _typeInteractables;
			std::vector<int> _typeTriggers;

			void LoadLevel(const char* pLevelName);
			void LoadInteractables(const char* pLevelName);
			void LoadSubtitleTriggers(const char * pLevelName);

            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:
			PhysicsWorld* _world;
            pugi::xml_document _xmlFile;
			pugi::xml_document _xmlFileInteractables;
			pugi::xml_document _xmlSubtitle;

            std::vector<pugi::xml_node> _mainNodes;
            std::vector<pugi::xml_node> _objectProperties;


			std::vector<pugi::xml_node> _mainNodesInteractable;
			std::vector<pugi::xml_node> _interactableProperties;

			std::vector<pugi::xml_node> _subtitleMainNodes;
			std::vector<pugi::xml_node> _subtitleProperties;


};

#endif // XMLREADER_H
