#include "Label.h"
#include <iostream>

Label::Label(std::string& text,
    float scale[2],
    float italic ,
    float width,
    float textSpaces)
{
    this->italic = italic;
    this->overload = false;

    //memcpy(this->pos, pos, sizeof pos);
    //memcpy(this->scale, scale, sizeof scale);

    textSpaces = textSpaces / scale[0];// *sqrt(italic * italic + 1);

    
    signsAmmount = 0;
    float cursor[2] = {0,0};
    if(width>0.0f)
        while (text.empty() == 0)
        {
            signs.push_back( Sign(text[0]) );

            signs[signsAmmount].SetItalic(italic);
            signs[signsAmmount].Scale(scale);

            if (cursor[0] + signs[signsAmmount].GetWidth() <= width)
            {
                signs[signsAmmount].Position(cursor);
                text.erase(text.begin());
                cursor[0] = cursor[0] + signs[signsAmmount].GetWidth() + textSpaces;

                ++signsAmmount;
            }
            else {
                this->overload = true;
                break;
            }
        }
    else
        while (text.empty() == 0)
        {
            signs.push_back( Sign(text[0]) );

            signs[signsAmmount].SetItalic(italic);
            signs[signsAmmount].Scale(scale);
            signs[signsAmmount].Position(cursor);

            text.erase(text.begin());
            cursor[0]=cursor[0]+ signs[signsAmmount].GetWidth() + textSpaces;

            ++signsAmmount;
        }


    this->hight = 1.0f / scale[1];

    width = 0;
    for (int i = 0; i < this->signsAmmount; ++i)
        this->width = this->width + this->signs[i].GetWidth() + textSpaces;
    this->width =this->width - textSpaces + this->hight * this->italic;
    

}


void Label::Position(float pos[2]) {
    for (int i = 0; i < this->signsAmmount; ++i)
        this->signs[i].Position(pos);
}



void Label::Throw(std::vector<float>& verticies,std::vector<unsigned long int>& indicies)
{
    for (int i = 0; i < this->signsAmmount; ++i)
    {
        signs[i].ShiftIndicies(verticies);

        signs[i].AppendVerticies(verticies);
        signs[i].AppendIndicies(indicies);
    }
}

void Label::Rotate(char rotation)
{
    rotation = rotation % 4;

    for (int i = 0; i < this->signsAmmount; ++i)
        signs[i].Rotate(rotation);

    float aux;
    switch (rotation) {

    case 1:case 3:
        aux = this->width;
        this->width = this->hight;
        this->hight = aux;
        break;

    case 2: case 4:
        break;
    default:
        break;
    }
}

void Label::CenterLabel() {
    float cursor[2] = {-this->width/2,0.0f};

    for (int i = 0; i < this->signsAmmount; ++i)
        signs[i].Position(cursor);
}

void Label::BottomLabel() {
    

    for (int i = 0; i < this->signsAmmount; ++i)
        if (signs[i].GetBottom() < this->bottom)
            this->bottom = signs[i].GetBottom();

    std::cout <<"bottom: "<< this->bottom << std::endl;

    float cursor[2] = { 0.0f,-1.0f - this->bottom };
    
    for (int i = 0; i < this->signsAmmount; ++i)
        signs[i].Position(cursor);

}





Label::~Label()
{
}
