#include <cassert>
#include <iostream>
using namespace std;

#include <glm.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/materials/AbstractMaterial.hpp"

GameObject::GameObject(std::string pName, glm::vec3 pPosition )
:	_name( pName ), _transform( glm::translate( pPosition ) ),  _parent(NULL), _children(),
    _mesh( NULL ),_behaviour( NULL ), _material(NULL), _world(NULL), updateTransform(true)
{
    oldPos = getLocalPosition();
}


GameObject::~GameObject()
{
	//detach all children
	cout << "GC running on:" << _name << endl;
	delete _behaviour;

	if (_material != NULL)
	{
		delete _material;
		_material = NULL;
	}
		

	while (_children.size() > 0) {
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
	//do not forget to delete behaviour, material, mesh, collider manually if required!
}

void GameObject::setName (std::string pName)
{
    _name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setTransform (const glm::mat4& pTransform)
{
    _transform = pTransform;
	updateTransform = true; 
}

glm::mat4& GameObject::getTransform()
{
    return _transform;
}

void GameObject::setLocalPosition (glm::vec3 pPosition)
{
    _transform[3] = glm::vec4 (pPosition,1);
	updateTransform = true;
	for (int i = 0; i < _children.size(); i++)
	{
		_children[i]->updateTransform = true;
	}
}

glm::vec3 GameObject::getLocalPosition()
{
	return glm::vec3(_transform[3]);
}

void GameObject::setMaterial(AbstractMaterial* pMaterial)
{
    _material = pMaterial;
}

AbstractMaterial * GameObject::getMaterial() const
{
    return _material;
}

void GameObject::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * GameObject::getMesh() const
{
    return _mesh;
}

void GameObject::setBehaviour(AbstractBehaviour* pBehaviour)
{
	_behaviour = pBehaviour;
	_behaviour->setOwner(this);
}

AbstractBehaviour * GameObject::getBehaviour() const
{
    return _behaviour;
}

void GameObject::setParent (GameObject* pParent) {
    //remove from previous parent
    if (_parent != NULL) {
        _parent->_innerRemove(this);
        _parent = NULL;
        _world = NULL;
    }

    //set new parent
    if (pParent != NULL) {
        _parent = pParent;
        _parent->_innerAdd(this);
        //pass on world to child
        _world = _parent->_world;
    }
}
GameObject* GameObject::getParent() {
    return _parent;
}

BoxTrigger* GameObject::getTrigger()
{
    glm::vec3 translation = getLocalPosition()  - oldPos;
    oldPos = getLocalPosition();

    _trigger->translate(translation);
    return _trigger;
}



void GameObject::_innerAdd(GameObject* pChild)
{
    //set new parent
    pChild->_parent = this;
	_children.push_back(pChild);
}

void GameObject::_innerRemove (GameObject* pChild) {
    for (auto i = _children.begin(); i != _children.end(); ++i) {
        if (*i == pChild) {
            (*i)->_parent = NULL;
            _children.erase(i);
            return;
        }
    }
}

void GameObject::add (GameObject* pChild) {
    pChild->setParent(this);
}

void GameObject::remove (GameObject* pChild) {
    pChild->setParent(NULL);
}

void GameObject::setWorldPosition(glm::vec3 pWorldPos)
{
	if (updateTransform)
	{
		if (getParent() == nullptr)
		{
			_worldTransform = _transform;
		}
		else
		{
			_worldTransform = _parent->getWorldTransform() * _transform;
		}
		updateTransform = false;
	}

	_worldTransform[3] = glm::vec4(pWorldPos, 1);

	if (getParent() == nullptr) 
	{ 
		_transform = _worldTransform;
	}
	else 
	{ 
		_transform = _worldTransform / getParent()->getWorldTransform(); 
	}
}
glm::vec3 GameObject::getWorldPosition()
{
	
	return glm::vec3(getWorldTransform()[3]);
}

glm::mat4& GameObject::getWorldTransform()
{
	if (updateTransform) {
		if (getParent() == nullptr) 
		{
			return _transform; 
		}
		_worldTransform = getParent()->getWorldTransform() * _transform;
		updateTransform = false;
	}
	return _worldTransform;
}
glm::vec3 GameObject::getForward()
{
    return  glm::normalize(glm::vec3(-_transform[2]));
}

glm::vec3 GameObject::getWorldForward()
{
	return  glm::normalize(glm::vec3(-_worldTransform[2]));
}
glm::vec3 GameObject::getWorldRight()
{
	return glm::normalize(glm::vec3(_worldTransform[0]));
}
glm::vec3 GameObject::getRight()
{
    return glm::normalize(glm::vec3(_transform[0]));
}
glm::vec3 GameObject::getUp()
{
    return glm::normalize(glm::vec3(_transform[1]));
}

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::update(float pStep, const glm::mat4& pParentTransform)
{
    _worldTransform = pParentTransform * _transform;
	updateTransform = false;

    if (_behaviour) {
		_behaviour->update(pStep);
	}

    for (int i = _children.size()-1; i >= 0; --i ) {
        _children[i]->update(pStep, _worldTransform);
    }
}

int GameObject::getChildCount() {
    return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) {
    return _children[pIndex];
}

