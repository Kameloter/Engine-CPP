#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>
#include "glm.hpp"


class AbstractBehaviour;
class AbstractMaterial;
class World;
class Mesh;
class BoxTrigger;
class GameObject
{
	public:
		GameObject(std::string pName = NULL, glm::vec3 pPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) );
		virtual ~GameObject();

        void setName (std::string pName);
        std::string getName() const;

        //contains local rotation, scale, position
		void setTransform (const glm::mat4& pTransform);
        glm::mat4& getTransform();

        //access just the local position
		void setLocalPosition (glm::vec3 pPosition);
		glm::vec3 getLocalPosition();

        //get the objects world position by combining transforms
		void setWorldPosition(glm::vec3 pWorldPos);
		glm::vec3 getWorldPosition();

		virtual glm::mat4& getWorldTransform();

		glm::vec3 getForward();
		glm::vec3 getRight();
		glm::vec3 getUp();
	
        //change local position, rotation, scaling
		void translate(glm::vec3 pTranslation);
		void rotate(float pAngle, glm::vec3 pAxis);
		void scale(glm::vec3 pScale);

        //mesh and material should be shared as much as possible
		void setMesh(Mesh* pMesh);
		Mesh* getMesh() const;

		void setMaterial (AbstractMaterial* pMaterial);
		AbstractMaterial* getMaterial() const;

        //behaviour will probably be a unique instance per gameobject
		void setBehaviour(AbstractBehaviour* pBehaviour);
		AbstractBehaviour* getBehaviour() const;

		virtual void update(float pStep, const glm::mat4& pParentTransform);

        //child management

        //shortcut to set the parent of pChild to ourselves
		void add (GameObject* pChild);
		//shortcut to set the parent of pChild to NULL
		void remove (GameObject* pChild);

		virtual void setParent (GameObject* pGameObject);
		GameObject* getParent();

        int getChildCount();
        GameObject* getChildAt (int pIndex);
		bool updateTransform;
		BoxTrigger * getTrigger();
		inline void SetBounds(glm::vec3 pMinBound, glm::vec3 pMaxBound)
		{
			_minBounds = pMinBound;
			_maxBounds = pMaxBound;
			//std::cout << " bounds set " << _minBounds << "   max - > " << _maxBounds << std::endl;

		}
		inline glm::vec3 GetMinBounds()
		{
			return _minBounds;
		}
		inline glm::vec3 GetMaxBounds()
		{
			return _maxBounds;
		}

        glm::vec3 oldPos;
	protected:
		std::string _name;
		glm::mat4 _transform;
		glm::mat4 _worldTransform;


        GameObject* _parent;
		std::vector<GameObject*> _children;
		BoxTrigger* _trigger;
        Mesh* _mesh;
		AbstractBehaviour* _behaviour;
		AbstractMaterial* _material;
		World* _world;

        //update children list administration
        void _innerAdd (GameObject* pChild);
		void _innerRemove (GameObject* pChild);

		glm::vec3 _minBounds;
		glm::vec3 _maxBounds;
};

#endif // GAMEOBJECT_H
