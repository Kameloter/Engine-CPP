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
            void Read(string pFileName);
            std::vector<pugi::xml_node> GetNodeChildren(pugi::xml_node node);
           // void LoadObjects();
            void SetupObjects();
            void SetupLevelGeometry();
            std::vector<StaticGameObject *> objects;

            std::vector<std::string> _names;
            std::vector<std::string> _diffuseTextures;
            std::vector<std::string> _normalMaps;

            std::vector<glm::vec3> _positions;
            std::vector<glm::vec3> _scales;
			void LoadLevel(string pLevelName);
            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:
			PhysicsWorld* _world;
            pugi::xml_document _xmlFile;
            std::vector<pugi::xml_node> _mainNodes;
            std::vector<pugi::xml_node> _objectProperties;


};

#endif // XMLREADER_H
