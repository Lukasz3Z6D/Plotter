#include "Transform.h"


Transform::Transform(static const float space,float hight)
{
    this->ReadFile(data, "x1.txt", Rows, Columns);


    
    vector<complex<double>>auxiliary;
    for (int i = 0; i < size(data[1]); ++i)
        auxiliary.push_back(data[1][i]);

    this->FFTeval(auxiliary, 0);

    for (int i = 0; i < size(data[1]); ++i)
        data[1][i]=abs(auxiliary[i])/size(data[1]);
    
    std::cout << "data size: " << size(data[1]) << std::endl << std::endl;


}

Transform::~Transform()
{
}

void Transform::ReadFile(vector<vector<double>>& data, const char* path, unsigned long int& Rows, unsigned int& Columns)
{

    std::ifstream infile("x1.txt");
    std::string line;

    {
        std::getline(infile, line);
        std::istringstream iss(line);
        iss >> line;
    }


    std::getline(infile, line);
    std::istringstream iss(line);


    //this section counts columns
    Columns = 0;
    vector<double> auxiliary;
    while (true) {

        if ((iss >> a >> z)) {
            Columns += 1;
            auxiliary.push_back(a);
        }
        else { break; }
    }
    //

    //

    data.resize(Columns);
    //

    std::cout << endl << "pien";


    //this section writes data to the vector of vectors
    Rows = 0;

    i = Columns;
    int aa = 0;
    while (i--) {
        data[i].push_back(auxiliary[i]);
        auxiliary.pop_back();

        //cout <<"i= "<<i<< endl << "result: " << result[i][0] << endl << "auxiliary: " <<auxiliary[i]<< endl;

        aa++;
        std::cout << "loops: " << aa << endl;
    }
    auxiliary.clear();

    Rows += 1;


    while (std::getline(infile, line))
    {
        i = 0;

        std::istringstream iss(line);

        while (true) {
            if ((iss >> a >> z)) {

                data[i].push_back(a);
                i += 1;
                Rows += 1;//for real, it counts each cell, not rows
                //std::cout << a << "\t" << i << "\t";
            }

            else {

                //std::cout << "\t"<< Rows<< "\n";
                break;
            }
        }
    }

    Rows /= Columns;//now, full rows only matter. "Rows" variable holds value of amount of Rows


    i = 0;


    unsigned long int CutRows = Rows;

    Rows--;
    Rows |= Rows >> 1;
    Rows |= Rows >> 2;
    Rows |= Rows >> 4;
    Rows |= Rows >> 8;
    Rows |= Rows >> 16;
    Rows |= Rows >> 32;
    Rows++;
    if (CutRows != Rows) {
        Rows /= 2;
        CutRows = CutRows - Rows + 1;
    }
    else
        CutRows = 1;


    while (CutRows--)
        for (int j = 0; j < Columns; ++j)
            data[j].pop_back();

}



void Transform::FFTeval(vector<complex<double>>& points, bool invert = 0)
{
    const double PI = acos(-1);

    int n = points.size();
    if (n == 1)
        return;

    vector<complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = points[2 * i];
        a1[i] = points[2 * i + 1];
    }
    FFTeval(a0, invert);
    FFTeval(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    complex<double> w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        points[i] = a0[i] + w * a1[i];
        points[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            points[i] /= 2;
            points[i + n / 2] /= 2;
        }
        w *= wn;
    }

}

void Transform::ColumnTodBV(unsigned int columnID)
{

    for (int i = 0; i < size(data[columnID]); ++i)
        data[columnID][i] = 20 * log10(data[columnID][i]);



}

void Transform::ColumnToV(unsigned int columnID)
{

    double max_val = *std::max_element(data[columnID].begin(), data[columnID].end()) ;

    for (int i = 0; i < size(data[columnID]); ++i)
        data[columnID][i] = data[columnID][i] / max_val*1.90 - 0.95;

}

void Transform::ProjectPrepare(unsigned int columnID, float space,float hight)
{
    double max_val = *std::max_element(data[columnID].begin(), data[columnID].end());
    double min_val = *std::min_element(data[columnID].begin(), data[columnID].end());

    for (int i = 0; i < size(data[columnID]); ++i)
        data[columnID][i] = (data[columnID][i] - min_val) / (max_val - min_val) * ((double)hight-2*space) - ((double)hight-space);
}

    


std::vector<float> Transform::getColumn(unsigned int columnID,float space,float hight,float width) {

    std::vector<float> auxiliary;
    
    

    for (int i = 0; i < size(data[columnID])/2+1; ++i) // /2 for half of the spectrum +1 one point more
        auxiliary.push_back( (float)data[columnID][i]) ;

    //dla V






    //dla dBV
    std::cout << std::endl << size(auxiliary) << std::endl;
    for (int i = 0; i < size(auxiliary); ++i)
        auxiliary[i] = 20 * log10(auxiliary[i]);   


    double max_val = *std::max_element(auxiliary.begin(), auxiliary.end());
    double min_val = *std::min_element(auxiliary.begin(), auxiliary.end());

    for (int i = 0; i < size(auxiliary); ++i)
        auxiliary[i] = ( auxiliary[i]-min_val ) / ( max_val-min_val ) *((double)hight-2*(double)space) -hight/2+space;



    return auxiliary;
}


