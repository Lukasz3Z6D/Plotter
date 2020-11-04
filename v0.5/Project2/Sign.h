#pragma once
#include <vector>
#include <iostream>
class Sign
{
private:
	std::vector<float> verticies;
	std::vector<unsigned long int> indicies;

	float width;
	float hight;
	float bottom;
	float italic;
	unsigned int sizeOfVerticies;
	unsigned int sizeOfIndicies;
	char rotated;


public:
	Sign(int character);
	~Sign();
	inline void SetItalic(float ital) { this->italic = ital; }
	void Scale(float scale[2]);
	void Position(float pos[2]);
	void Rotate(char rotations=1);

	void ShiftIndicies(std::vector<float> verticies);
	void AppendVerticies(std::vector<float>& verticies);
	void AppendIndicies(std::vector<unsigned long int>& indicies);

	void ShowInd();

	void ShowVert();

	
	inline float GetWidth(){return this->width;}
	inline float GetHight(){return this->hight;}
	inline float GetBottom() { return this->bottom; }


};

