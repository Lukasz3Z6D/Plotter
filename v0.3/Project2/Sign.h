#pragma once
#include <vector>
class Sign
{
private:
	std::vector<float> verticies;
	std::vector<unsigned long int> indicies;

	float width;
	float hight;


	void ScaleAndPosition(float scale[2], float pos[2]);
	void ShiftIndicies(unsigned long int indShift);

public:
	Sign(int character, float scale[2], float pos[2], unsigned long int indShift);
	~Sign();

	void AppendVerticies(std::vector<float>& verticies);
	void AppendIndicies(std::vector<unsigned long int>& indicies);

	float GetWidth();
	float GetHight();


};

