#pragma once
#include "AbstractBehaviour.hpp"
class WinBehaviour :
	public AbstractBehaviour
{
public:
	WinBehaviour();
	~WinBehaviour();

	virtual void update(float pStep);
};

