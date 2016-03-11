#pragma once
#include <iostream>

class Subtitle
{
	
public:
	Subtitle(std::string pSub, float pShowTime) :subtitle(pSub), duration(pShowTime) {}
	std::string subtitle;
	float duration = 0;
};