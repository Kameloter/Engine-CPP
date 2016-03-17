#pragma once

class GameObject;
class FadeManager
{
public:
	FadeManager();
	~FadeManager();

	static void updateFadeScreen();

	static void setFade(bool pFade);
	static void setFadeScreen(GameObject * pObject);

	
private:
	static GameObject * _fadeScreen;
	static bool _fade;
	static bool _startFade;
	static float  _alpha;
	static float _fadeStartTime;
};

