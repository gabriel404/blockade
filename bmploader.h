#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

class BMP
{
private:
    std::uint32_t width, height;
    std::uint16_t BitsPerPixel;
    std::vector<std::uint8_t> Pixels;

public:
    std::vector<std::uint8_t> GetPixels() const {return this->Pixels;}
    std::uint32_t GetWidth() const {return this->width;}
    std::uint32_t GetHeight() const {return this->height;}

public:
    BMP(const char* FilePath);
    bool HasAlphaChannel() {return BitsPerPixel == 32;}
};
