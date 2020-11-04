#pragma once
#include "Sign.h"
#include <string>
#include <cmath>
class Label
{
	float italic = 0.125f;
	std::string text;
	float pos[2] = { 0.0f,0.0f };
	float scale[2] = {1.0f,1.0f};
	std::vector<Sign> signs;
	unsigned int signsAmmount;
	float width;
	float hight;
	bool overload;
	float bottom;

public:



	Label(std::string& text,
		float scale[2],
		float italic=0.0f,
		float width = 0.0f,
		float textSpaces = 0.25f);

	void Position(float pos[2]);

	void CenterLabel();

	void BottomLabel();

	void Rotate(char rotation=1);

	void Throw(std::vector<float>& verticies,
		std::vector<unsigned long int>& indicies);


	inline float getHight() { return this->hight; };
	inline float getWidth() { return this->width; };
	inline unsigned getSignsAmmount() { return this->signsAmmount; }
	inline bool isOverloaded() { return this->overload; }

	~Label();

};

