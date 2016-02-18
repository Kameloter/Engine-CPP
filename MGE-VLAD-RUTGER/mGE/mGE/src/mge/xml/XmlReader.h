#ifndef XMLREADER_H
#define XMLREADER_H
#include "pugixml.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/StaticGameObject.h"

#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"

using namespace std;

class PhysicsWorld;

class XmlReader
{
    public:
            XmlReader();
            virtual ~XmlReader();
            void Read();
            std::vector<pugi::xml_node> GetNodeChildren(pugi::xml_node node);
           // void LoadObjects();
            void SetupObjects();
            void SetupLevelGeometry(PhysicsWorld * pPhysicsWorld);
        //    void setUpPhysics();
            std::vector<StaticGameObject *> objects;

            std::vector<std::string> _names;
            std::vector<std::string> _diffuseTextures;
            std::vector<std::string> _normalMaps;

            std::vector<glm::vec3> _positions;
            std::vector<glm::vec3> _scales;

            template<typename T>
            T StringToNumber(const std::string& numberAsString);
        protected:
        private:

            pugi::xml_document _xmlFile;
            std::vector<pugi::xml_node> _mainNodes;
            std::vector<pugi::xml_node> _objectProperties;


};

#endif // XMLREADER_H
