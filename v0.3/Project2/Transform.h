#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <algorithm>
#include <cmath>

using namespace std;

class Transform
{
	unsigned long int Rows = 0;
	unsigned int Columns = 0;
	std::vector<std::vector<double>> data;

	float hight;

	double a, b, c, d, e;
	char z;
	int i = 0;

	const double PI = acos(-1);


public:
	Transform(static const float space, float hight);
	~Transform();

	void ReadFile(vector<vector<double>>& data, const char* path, unsigned long int& Rows, unsigned int& Columns);

	void FFTeval(vector<complex<double>>& points, bool invert);

	void ColumnTodBV(unsigned int columnID);

	void ColumnToV(unsigned int columnID);

	void ProjectPrepare(unsigned int columnID, float space,float hight);

	std::vector<float> getColumn(unsigned int columnID);

};

