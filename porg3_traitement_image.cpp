#include <iostream>
#include <fstream>
#include <vector>

#include "Headers.h"
#include "Bmp32.h"

using namespace std;

void genererCle()
{
    std::ofstream outImage{ "cle.steg", std::ios_base::binary };
    if (outImage)
    {
        char cle{ 0b01010011 };
        outImage.write(&cle, 1);
    }
}

void lireCle()
{
    char cle;
    std::ifstream image{ "cle.steg", std::ios::in | std::ios::binary };
    if (image.is_open())
    {
        image.read(&cle, 1);

        image.close();
    }

    for (int i = 7; i >= 0; i--)
    {
        std::cout << ((cle >> i) & 1);
    }
}


int main()
{
    Bmp32 bmp{ "Shapes.bmp" };
    Bmp32 bmp2{ 800, 600, 125, 33, 65 };
    bmp2.DrawRect(400, 300, 100, 200);
    bmp2.Encode("Ouvre tes yeux Simon ");
    bmp2.Save("test2.bmp");
    Bmp32 bmp3{ "test2.bmp" };
    std::string msg{ bmp3.Decode() };

    std::cout << "fin";
}
