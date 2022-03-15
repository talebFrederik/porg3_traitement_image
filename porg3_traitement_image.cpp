#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#pragma pack(push, 1)
struct BMPFilheader
{
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset{0};
};

struct BMPInfoHeader {
	uint32_t size{ 0 };
	int32_t width{ 0 };
	int32_t height{ 0 };
	uint16_t planes{ 1 };
	uint16_t bit_count{ 0 };
	uint32_t compression{ 0 };
	uint32_t size_image{ 0 };
	int32_t x_pixels_per_meter{ 0 };
	int32_t y_pixels_per_meter{ 0 };
	uint32_t colors_used{ 0 };
	uint32_t colors_important{ 0 };
};

struct BMPColorHeader 
{
    uint32_t red_mask{ 0x00ff0000 };
    uint32_t green_mask{ 0x0000ff00 };
    uint32_t blue_mask{ 0x000000ff };
    uint32_t alpha_mask{ 0xff000000 };
    uint32_t color_space{ 0x73524742 };
    uint32_t unused[16]{ 0 };
};

#pragma pack(pop)

int main()
{

    streampos size;
    vector<uint8_t> data{};
    BMPFilheader fileHeader;
    BMPInfoHeader infoHeader;
    BMPColorHeader colorHeader;

    ifstream image{ "C:/Users/ftaleb/Documents/H2022_prog3/test.bmp", ios::in | ios::binary };
    if (image.is_open())
    {
        image.read((char *)&fileHeader, sizeof(fileHeader));
        image.read((char*)&infoHeader, sizeof(infoHeader));
        image.read((char*)&colorHeader, sizeof(colorHeader));

        data.resize(infoHeader.size_image);

        image.seekg(fileHeader.offset, image.beg);
        image.read((char*)data.data(), data.size());

        cout << (int)data[0];



        image.close();
    }
}
