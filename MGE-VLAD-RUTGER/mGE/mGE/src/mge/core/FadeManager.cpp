#include "FadeManager.h"
#include "mge/core/Timer.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
#include "mge/materials/FadeScreenMaterial.hpp"

bool FadeManager::_fade = false;
bool FadeManager::_startFade = false;
float FadeManager::_fadeStartTime = 0;
float FadeManager::_alpha = 1;
GameObject * FadeManager::_fadeScreen = NULL;
FadeManager::FadeManager()
{
	


}


FadeManager::~FadeManager()
{

}

void FadeManager::updateFadeScreen()
{
	if (_startFade)
	{
		if (_fade)
		{
			dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setRenderImage(true);
			if ((Timer::now() - _fadeStartTime) < 2)
			{
				_alpha += 0.02;
				if (_alpha > 1)
					_alpha = 1;
				//decrease fade.
				if (_fadeScreen != NULL)
				{
					dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setAlpha(_alpha);					
				}
					
			}
			else {
				
				_startFade = false;
			}

		}
		else
		{
			if ((Timer::now() - _fadeStartTime) < 2)
			{

				_alpha -= 0.02;
				if (_alpha < 0)
					_alpha = 0;
				//decrease fade.
				if (_fadeScreen != NULL)
				{
					dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setAlpha(_alpha);
				
				}
			}
			else
			{
				dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setRenderImage(false);
				_startFade = false;
			}
		}
	}
}

void FadeManager::setFade(bool fade)
{
	_fade = fade;
	_startFade = true;
	_fadeStartTime = Timer::now();
}

void FadeManager::setFadeScreen(GameObject * pObject)
{
	_fadeScreen = pObject;
}


