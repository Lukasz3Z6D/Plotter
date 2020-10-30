#include "Sign.h"


void Sign::ScaleAndPosition(float scale[2], float pos[2])
{
	for (int i = 0; i < size(verticies) ; i+=2)
	{
		verticies[i] = verticies[i] / scale[0] + pos[0];
		verticies[i + 1] = verticies[i + 1] / scale[1] + pos[1];

	}

	this->width = this->width / scale[0];
	this->hight = this->hight / scale[1];
}

void Sign::ShiftIndicies(unsigned long int indShift)
{
	for (int i = 0; i < size(indicies); ++i)
		indicies[i] = indicies[i] + indShift;
}

Sign::Sign(int character, float scale[2], float pos[2], unsigned long int indShift)
{
	switch (character) {

	case 48:
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

		width = 1;
		hight = 1;
		break;

	case 49:
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
		hight = 1;
		break;

	case 50:
		break;

	case 51:
		break;

	case	52:
		break;

	case	53:
		break;

	case	54:
		break;

	case	55:
		break;

	case	56:
		break;

	case	57:
		break;

	case	58:
		break;

	case	59:
		break;

	case	60:
		break;

	case	61:
		break;

	case	62:
		break;

	case	63:
		break;

	case	64:
		break;

	case	65:
		break;

	case	66:
		break;

	case	67:
		break;

	case	68:
		break;

	case	69:
		break;

	case	70:
		break;

	case	71:
		break;

	case	72:
		break;

	case	73:
		break;

	case	74:
		break;

	case	75:
		break;

	case	76:
		break;

	case	77:
		break;

	case	78:
		break;

	case	79:
		break;

	case	80:
		break;

	case	81:
		break;

	case	82:
		break;

	case	83:
		break;

	case	84:
		break;

	case	85:
		break;

	case	86:
		break;

	case	87:
		break;

	case	88:
		break;

	case	89:
		break;

	case	90:
		break;

	case	91:
		break;

	case	92:
		break;

	case	93:
		break;

	case	94:
		break;

	case	95:
		break;

	case	96:
		break;

	case	97:
		break;

	case	98:
		break;

	case	99:
		break;

	case	100:
		break;

	case	101:
		break;

	case	102:
		break;

	case	103:
		break;

	case	104:
		break;

	case	105:
		break;

	case	106:
		break;

	case	107:
		break;

	case	108:
		break;

	case	109:
		break;

	case	110:
		break;

	case	111:
		break;

	case	112:
		break;

	case	113:
		break;

	case	114:
		break;

	case	115:
		break;

	case	116:
		break;

	case	117:
		break;

	case	118:
		break;

	case	119:
		break;

	case	120:
		break;

	case	121:
		break;

	case	122:
		break;

	default:
		break;
	}


	this->ScaleAndPosition(scale, pos);;
	this->ShiftIndicies(indShift);
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

float Sign::GetWidth()
{
	return width;
}

float Sign::GetHight()
{
	return hight;
}

