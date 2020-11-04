/* these are sample signs: "8", "g", "Ó"
											0.25 (CEILING)
										  /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
										  |
							_ _ _ _ _ _ _\|/_  _  _  _  _  _  _  _  _  _(+1.25) 
                             /            |
  _ _ _ _ _                   _ _ _ _ _ _ |
/|\        /‾‾\            /‾‾\          /|\
 |        |    |          |    |          |
 |        |    |          |    |
 |1.00     \  /           |    |
 |         /‾‾\    /‾‾\|  |    |             0.50 (FLOOR)
 |        |    |  |    |  |    |           /‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 |        | 8  |  | g  |  | Ó  |          |
\|/ _ _ _ _\  /    \  /|   \  /_ _ _ _ _ \|/
		  / ‾‾      ‾‾ |    ‾‾            |
		 /             |                  |
		/              |                  |
	   /           \  / _ _ _ _ _ _ _ _ _ |_  _  _  _  _  _  _  _  _  _ (-0.50)
 (0.00,0.00)        ‾‾                   /|\
										  |


//hights are constant,
//width depends on a specific sign though
*/
#define CEILING 0.25f
#define FLOOR 0.50f

#include "Sign.h"


void Sign::Scale(float scale[2])
{
	for (int i = 0; i < size(this->verticies) ; i+=2)
	{
		verticies[i + 1] = verticies[i + 1] / scale[1];
		verticies[i] = verticies[i] / scale[0] + verticies[i + 1] * this->italic;

	}

	//this->width = (this->width / scale[0])  +  this->hight*this->italic;
	this->width = this->width / scale[0];
	this->bottom = this->bottom / scale[1];
}

void Sign::Position(float pos[2])
{
	for (int i = 0; i < size(this->verticies) ; i+=2)
	{
		verticies[i] = verticies[i] + pos[0];
		verticies[i + 1] = verticies[i + 1] + pos[1];
	}
}

void Sign::Rotate(char rotations) 
{



	switch (rotations) {

		rotations = rotations % 4;

	case 1:
		for (int i = 0; i < size(this->verticies); i += 2)
		{
			float aux;
			aux = verticies[i];
			verticies[i] = -verticies[i + 1];
			verticies[i + 1] = aux;
			this->hight = aux;
			this->hight = this->width;
			this->width = aux - this->bottom;
		}
		break;

	case 2:
		for (int i = 0; i < size(this->verticies); i += 2)
		{
			verticies[i] = -verticies[i];
			verticies[i + 1] = -verticies[i + 1];			
		}
		break;

	case 3:
		for (int i = 0; i < size(this->verticies); i += 2)
		{
			float aux;
			aux = -verticies[i];
			verticies[i] = verticies[i + 1];
			verticies[i + 1] = aux;
			this->hight = aux;
			this->hight = this->width;
			this->width = aux - this->bottom;
		}
		break;


	default:
		break;
	}
	
	this->rotated+=rotations;
	this->rotated = this->rotated % 4;
}


void Sign::ShiftIndicies(std::vector<float> verticies)
{
	for (int i = 0; i < size(indicies); ++i)
		indicies[i] = indicies[i] + size(verticies) / 2;
}

Sign::Sign(int character)
{
	this->hight = 1.0f;
	this->bottom = 0.0f;
	this->rotated = 0;

	switch (character) {

	case	32:

		width = 0.750f;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;

	case	33:
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.000f,0.125f,
			0.000f,0.250f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		width = 0.0f;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;

	case	34:
		verticies.insert(verticies.end(), {
			0.000f,0.875f,
			0.000f,1.000f,
			0.250f,0.875f,
			0.250f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		width = 0.250f;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;


	case	35:
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.250f,1.000f,
			0.500f,0.000f,
			0.750f,1.000f,
			0.000f,0.375f,
			1.000f,0.375f,
			0.000f,0.625f,
			1.000f,0.625f
			});
		indicies.insert(indicies.end(), {
			7,6,
			5,4,
			3,2,
			1,0
			});

		width = 1;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;


	case	36:
		verticies.insert(verticies.end(), {
			0.000f,0.125f,
			0.250f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.375f,
			0.750f,0.500f,
			0.250f,0.500f,
			0.000f,0.625f,
			0.000f,0.875f,
			0.250f,1.000f,
			0.750f,1.000f,
			1.000f,0.875f,
			0.5000f,-0.125f,
			0.5000f,1.125f
			});
		indicies.insert(indicies.end(), {
			13,12,
			11,10,
			10,9,
			9,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		width = 1;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;


	case	37:
		verticies.insert(verticies.end(), {
			0.125f,0.000f,
			0.625f,1.000f,
			0.000f,0.5625f,
			0.250f,0.5625f,
			0.250f,0.6875f,
			0.000f,0.6875f,
			0.5f,0.3125f,
			0.75f,0.3125f,
			0.75f,0.4375f,
			0.5f,0.4375f
			});
		indicies.insert(indicies.end(), {
			6,9,
			9,8,
			8,7,
			7,6,
			2,5,
			5,4,
			4,3,
			3,2,
			1,0
			});

		width = 0.75;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;


	case	38:
		verticies.insert(verticies.end(), {
			1.000f,0.375f,
			0.750f,0.125f,
			0.500f,0.000f,
			0.250f,0.000f,
			0.000f,0.125f,
			0.000f,0.250f,
			0.750f,0.875f,
			0.500f,1.000f,
			0.250f,0.875f,
			1.000f,0.000f
			});
		indicies.insert(indicies.end(), {
			9,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		width = 1;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;



	case	39:
		verticies.insert(verticies.end(), {
			0.000f,0.875f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		width = 0.0f;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;



	case	40:
		verticies.insert(verticies.end(), {
			0.250f,0.000f,
			0.000f,0.125f,
			0.000f,0.875,
			0.250f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			2,1,
			1,0
			});

		width = 0.25;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;



	case	41:
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.250f,0.125f,
			0.250f,0.875f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			2,1,
			1,0
			});

		width = 0.25;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;

	case	42:
		verticies.insert(verticies.end(), {
			0.250f,0.875f,
			0.000f,0.750f,
			0.500f,0.750f,
			0.500f,1.000f,
			0.250f,1.000f,
			0.000f,1.000f,
			});
		indicies.insert(indicies.end(), {
			5,0,
			4,0,
			3,0,
			2,0,
			1,0
			});

		width = 0.5;
		sizeOfIndicies = 0;
		sizeOfVerticies = 0;
		break;

	case	43:
		verticies.insert(verticies.end(), {
			0.000f,0.500f,
			0.500f,0.500f,
			0.250f,0.375f,
			0.250f,0.625f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		width = 0.5;
		sizeOfVerticies = 0;
		sizeOfIndicies = 0;
		break;


	case	44://,
		verticies.insert(verticies.end(), {
			0.000f,-0.1875f,
			0.250f,0.0625f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		width = 0.250f;
		this->bottom = -0.1875;
		sizeOfVerticies = 0;
		sizeOfIndicies = 0;
		break;


	case	45://-
		verticies.insert(verticies.end(), {
			0.000f,0.500f,
			0.500f,0.500f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		width = 0.500f;
		sizeOfVerticies = 0;
		sizeOfIndicies = 0;
		break;


	case	46:// .
		verticies.insert(verticies.end(), {
			0.000f,0.03125f,
			0.000f,0.09375f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		width = 0.000f;
		sizeOfVerticies = 0;
		sizeOfIndicies = 0;
		break;


	case	47:// /
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.500f,1.000f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		width = 0.500f;
		sizeOfVerticies = 0;
		sizeOfIndicies = 0;
		break;




	case 48://0
		verticies.insert(verticies.end(), {
			0.25, 0.00,
			0.75,0.00,
			1.00,0.125,
			1.00,0.875,
			0.75,1.00,
			0.25,1.00,
			0.00,0.875,
			0.00,0.125
			});

		indicies.insert(indicies.end(), {
			0,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		width = 1.0f;
		sizeOfVerticies = 16;
		sizeOfIndicies = 16;
		break;

	case 49://1
		verticies.insert(verticies.end(), {
			0.0,0.5,
			0.75,1.0,
			0.75,0.0
			});

		indicies.insert(indicies.end(), {
			2,1,
			1,0
			});

		width = 0.75;
		sizeOfVerticies = 6;
		sizeOfIndicies = 4;
		break;

	case 50://2
		verticies.insert(verticies.end(), {
			0.00f, 0.875f,
			0.25f,1.00f,
			0.75f,1.00f,
			1.00f,0.875f,
			1.00f,0.625f,
			0.00f,0.00f,
			1.00f,0.00f
			});

		indicies.insert(indicies.end(), {
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0 });

		sizeOfVerticies = 14;
		sizeOfIndicies = 12;
		width = 1;
		break;

	case 51://3
		verticies.insert(verticies.end(), {
			0.000f,0.875f,
			0.250f,1.000f,
			0.750f,1.000f,
			1.000f,0.875f,
			1.000f,0.625f,
			0.750f,0.500f,
			0.250f,0.500f,
			1.000f,0.375f,
			1.000f,0.125f,
			0.750f,0.000f,
			0.250f,0.000f,
			0.000f,0.125f
			});
		indicies.insert(indicies.end(), {
			11,10,
			10,9,
			9,8,
			8,7,
			7,5,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 24;
		sizeOfIndicies = 22;
		width = 1;
		break;


	case	52://4
		verticies.insert(verticies.end(), {
			0.250f,1.000f,
			0.000f,0.500f,
			1.000f,0.500f,
			0.750f,1.000f,
			0.750f,0.000f
			});
		indicies.insert(indicies.end(), {
			0,1,
			1,2,
			3,4
			});

		sizeOfVerticies = 10;
		sizeOfIndicies = 6;
		width = 1;
		break;


	case	53://5
		verticies.insert(verticies.end(), {
			1.000f,1.000f,
			0.000f,1.000f,
			0.000f,0.500f,
			0.750f,0.500f,
			1.000f,0.375f,
			1.000f,0.125f,
			0.750f,0.000f,
			0.250f,0.000f,
			0.000f,0.125f
			});
		indicies.insert(indicies.end(), {
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 18;
		sizeOfIndicies = 16;
		width = 1;
		break;


	case	54://6
		verticies.insert(verticies.end(), {
			1.000f,0.875f,
			0.750f,1.000f,
			0.250f,1.000f,
			0.000f,0.875f,
			0.000f,0.125f,
			0.250f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.375f,
			0.750f,0.500f,
			0.250f,0.500f,
			0.000f,0.375f
			});
		indicies.insert(indicies.end(), {
			11,10,
			10,9,
			9,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 24;
		sizeOfIndicies = 22;
		width = 1;
		break;

	case	55://7
		verticies.insert(verticies.end(), {
			0.000f,1.000f,
			1.000f,1.000f,
			0.000f,0.000f,
			0.250f,0.500f,
			0.750f,0.500f
			});
		indicies.insert(indicies.end(), {
			0,1,
			1,2,
			3,4
			});

		sizeOfVerticies = 10;
		sizeOfIndicies = 6;
		width = 1;
		break;

	case	56://8
		verticies.insert(verticies.end(), {
			0.250f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.375f,
			0.750f,0.500f,
			1.000f,0.625f,
			1.000f,0.875f,
			0.750f,1.000f,
			0.250f,1.000f,
			0.000f,0.875f,
			0.000f,0.625f,
			0.250f,0.500f,
			0.000f,0.375f,
			0.000f,0.125f
			});
		indicies.insert(indicies.end(), {
			11,4,
			0,13,
			13,12,
			12,11,
			11,10,
			10,9,
			9,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 28;
		sizeOfIndicies = 30;
		width = 1;
		break;

	case	57://9
		verticies.insert(verticies.end(), {
			0.000f,0.125f,
			0.250f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.875f,
			0.750f,1.000f,
			0.250f,1.000f,
			0.000f,0.875f,
			0.000f,0.625f,
			0.250f,0.500f,
			0.750f,0.500f,
			1.000f,0.625f
			});
		indicies.insert(indicies.end(), {
			11,10,
			10,9,
			9,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 24;
		sizeOfIndicies = 22;
		width = 1;
		break;

	case	58://:
		verticies.insert(verticies.end(), {
			0.000f,0.03125f,
			0.000f,0.09375f,
			0.000f,0.90625f,
			0.000f,0.96875f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 0.000f;
		break;

	case	59://;
		verticies.insert(verticies.end(), {
			0.000f,-0.1875f,
			0.250f,0.0625f,
			0.250f,0.90625f,
			0.250f,0.96875f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		this->width = 0.250f;
		this->bottom = -0.1875;
		break;

	case	60://<
		verticies.insert(verticies.end(), {
			1.000f,0.125f,
			0.000f,0.500f,
			1.000f,0.875f
			});
		indicies.insert(indicies.end(), {
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	61://=
		verticies.insert(verticies.end(), {
			0.000f,0.4375f,
			0.500f,0.4375f,
			0.000f,0.5625f,
			0.500f,0.5625f
			});
		indicies.insert(indicies.end(), {
			3,2,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 0.500f;
		break;

	case	62://>
		verticies.insert(verticies.end(), {
			0.000f,0.125f,
			1.000f,0.500f,
			0.000f,0.875f
			});
		indicies.insert(indicies.end(), {
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	63://?
		verticies.insert(verticies.end(), {
			0.500f,0.000f,
			0.500f,0.125f,
			0.500f,0.250f,
			0.500f,0.375f,
			1.000f,0.625f,
			1.000f,0.875f,
			0.750f,1.000f,
			0.250f,1.000f,
			0.000f,0.875f
			});
		indicies.insert(indicies.end(), {
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	64://@
		verticies.insert(verticies.end(), {
			0.500f,0.125f,
			0.750f,0.250f,
			0.750f,0.500f,
			0.500f,0.625f,
			0.250f,0.500f,
			0.250f,0.250f,
			0.750f,0.625f,
			0.750f,0.125f,
			1.000f,0.125f,
			1.000f,0.625f,
			0.750f,0.750f,
			0.250f,0.750f,
			0.000f,0.625f,
			0.000f,0.125f,
			0.250f,0.000f,
			0.750f,0.000f
			});
		indicies.insert(indicies.end(), {
			15,14,
			14,13,
			13,12,
			12,11,
			11,10,
			10,9,
			9,8,
			8,7,
			7,6,
			0,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	65://A
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.500f,1.000f,
			1.000f,0.000f,
			0.250f,0.500f,
			0.750f,0.500f
			});
		indicies.insert(indicies.end(), {
			4,3,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	66://B
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.375f,
			0.750f,0.500f,
			1.000f,0.625f,
			1.000f,0.875f,
			0.750f,1.000f,
			0.000f,1.000f,
			0.000f,0.500f
			});
		indicies.insert(indicies.end(), {
			9,4,
			0,8,
			8,7,
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	67://C
		verticies.insert(verticies.end(), {
			1.000f,0.125f,
			0.750f,0.000f,
			0.250f,0.000f,
			0.000f,0.125f,
			0.000f,0.875f,
			0.250f,1.000f,
			0.750f,1.000f,
			1.000f,0.875f
			});
		indicies.insert(indicies.end(), {
			7,6,
			6,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	68://D
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.875f,
			0.750f,1.000f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			0,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	69:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	70:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	71:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	72://H
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.000f,1.000f,
			1.000f,0.000f,
			1.000f,1.000f,
			0.000f,0.500f,
			1.000f,0.500f
			});
		indicies.insert(indicies.end(), {
			5,4,
			3,2,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	73:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	74:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	75:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	76:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	77:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	78:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	79:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	80:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	81:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	82:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	83:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	84:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	85:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	86:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	87:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	88:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	89:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	90:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	91:// [
		verticies.insert(verticies.end(), {
			0.250f,0.000f,
			0.000f,0.000f,
			0.000f,1.000f,
			0.250f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		this->width = 0.250f;
		break;

	case	92:// "\"
		verticies.insert(verticies.end(), {
			0.500f,0.000f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 0.500f;
		break;

	case	93://]
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.250f,0.000f,
			0.250f,1.000f,
			0.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 0.250f;
		break;

	case	94:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	95:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	96:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	97:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	98:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	99:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	100://d
		verticies.insert(verticies.end(), {
			0.250f,0.000f,
			1.000f,0.000f,
			1.000f,0.500f,
			0.250f,0.500f,
			0.000f,0.375f,
			0.000f,0.125f,
			1.000f,1.000f
			});
		indicies.insert(indicies.end(), {
			6,2,
			0,5,
			5,4,
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	101:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	102:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	103://g
		verticies.insert(verticies.end(), {
			0.250f,0.000f,
			0.750f,0.000f,
			1.000f,0.125f,
			1.000f,0.500f,
			1.000f,0.375f,
			0.750f,0.500f,
			0.250f,0.500f,
			0.000f,0.375f,
			0.000f,0.125f,
			1.000f,-0.375f,
			0.750f,-0.500f,
			0.250f,-0.500f,
			0.000f,-0.375f
			});
		indicies.insert(indicies.end(), {
			12,11,
			11,10,
			10,9,
			9,2,
			0,8,
			8,7,
			7,6,
			6,5,
			5,4,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		this->bottom = -0.5f;
		break;

	case	104:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	105:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	106:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	107:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	108:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	109://m
		verticies.insert(verticies.end(), {
			0.000f,0.000f,
			0.000f,0.500f,
			0.500f,0.250f,
			1.000f,0.500f,
			1.000f,0.000f
			});
		indicies.insert(indicies.end(), {
			4,3,
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		this->width = 1;
		this->bottom = 0;
		break;

	case	110:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	111:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	112:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	113:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	114:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	115:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	116:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	117:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	118:
		verticies.insert(verticies.end(), {

			});
		indicies.insert(indicies.end(), {

			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	case	119:
		break;

	case	120:
		break;

	case	121:
		break;

	case	122://z
		verticies.insert(verticies.end(), {
			1.000f,0.000f,
			0.000f,0.000f,
			1.000f,0.500f,
			0.000f,0.500f
			});
		indicies.insert(indicies.end(), {
			3,2,
			2,1,
			1,0
			});

		sizeOfVerticies = 1;
		sizeOfIndicies = 1;
		width = 1;
		break;

	default:
		break;
	}
}


Sign::~Sign()
{
}



void Sign::AppendVerticies(std::vector<float>& verticies)
{
	verticies.insert(std::end(verticies), std::begin(this->verticies), std::end(this->verticies));
}


void Sign::AppendIndicies(std::vector<unsigned long int>& indicies)
{
	indicies.insert(std::end(indicies), std::begin(this->indicies), std::end(this->indicies));
}


void Sign::ShowInd() {
	for (int i = 0; i < size(this->indicies); ++i)
		std::cout << indicies[i] << std::endl;
	std::cout << std::endl<<std::endl;
}


void Sign::ShowVert() {
	for (int i = 0; i < size(this->verticies); ++i)
		std::cout << verticies[i] << std::endl;
	std::cout << std::endl << std::endl;
}