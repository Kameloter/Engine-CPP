#pragma once
#include "AbstractBehaviour.hpp"
class SubtitleBehaviour :
	public AbstractBehaviour
{
public:

	SubtitleBehaviour();
	~SubtitleBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);
};

