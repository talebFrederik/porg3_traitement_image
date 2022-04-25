#include <iostream>
#include <fstream>
#include <vector>

#include "Headers.h"

using namespace std;


int main()
{
    vector<uint8_t> data{};
    BMPFilheader fileHeader;
    BMPInfoHeader infoHeader;
    BMPColorHeader colorHeader;

    ifstream image{ "shapes.bmp", ios::in | ios::binary };
    if (image.is_open())
    {
        image.read((char*)&fileHeader, sizeof(fileHeader));
        image.read((char*)&infoHeader, sizeof(infoHeader));
        image.read((char*)&colorHeader, sizeof(colorHeader));

        data.resize(infoHeader.size_image);

        image.seekg(fileHeader.offset, image.beg);
        image.read((char*)data.data(), data.size());

        image.close();
    }

    for (int i = 0; i < data.size(); i+=4)
    {
        data[i] = 255;
        data[i + 1] = 0;
        data[i + 2] = 0;
        data[i + 3] = 255;
    }

    ofstream outImage{ "test.bmp", ios_base::binary };
    if (outImage)
    {
        outImage.write((char*)&fileHeader, sizeof(fileHeader));
        outImage.write((char*)&infoHeader, sizeof(infoHeader));
        outImage.write((char*)&colorHeader, sizeof(colorHeader));
        outImage.write((char*)data.data(), data.size());
    }
}
