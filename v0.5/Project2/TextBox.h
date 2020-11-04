#pragma once
#include "Label.h"

class TextBox
{
	float italic = 0.125f;
	std::string text;
	float pos[2] = { 0.0f,0.0f };
	float scale[2] = { 1.0f,1.0f };
	std::vector<Sign> signs;
	unsigned int labelsAmmount;
	float width;
	float hight;

public:

	void Throw(std::vector<float>& verticies,
		std::vector<unsigned long int>& indicies);


};

