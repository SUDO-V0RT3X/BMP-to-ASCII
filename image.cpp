#include "image.h"

using namespace std;

// Colour class:
Colour::Colour() : r(0), g(0), b(0) {}

Colour::Colour(float r, float g, float b) : r(r), g(g), b(b) {}

Colour::Colour(const Colour &copy) : r(copy.r), g(copy.g), b(copy.b) {}

void Colour::operator=(const Colour &copy)
{
    r = copy.r;
    g = copy.g;
    b = copy.b;
}

Colour::~Colour() {}

ostream &operator<<(ostream &output, const Colour &colour)
{
    output << "R: " << colour.r << " G: " << colour.g << " B: " << colour.b << "\n";
    return output;
}

// Image class:
Image::Image(int width, int height) : width(width), height(height), colours(vector<Colour>(width * height)) {}

int Image::getHeight()
{
    return height;
}

int Image::getWidth()
{
    return width;
}

vector<Colour> Image::getRGBValues()
{
    return colours;
}

Image::~Image() {}

Colour Image::getColour(int x, int y) const
{
    return colours[y * width + x];
}

void Image::setColour(const Colour &colour, int x, int y)
{
    colours[y * width + x] = colour;
}

void Image::readImage(const char *path)
{
    ifstream file;
    file.open(path, ios::in | ios::binary);

    if (!file.is_open())
    {
        cout << "Unfortunately, the file could not be opened! \n Please enter a valid path." << endl;
    }

    const int fileHeaderSize = 14;
    const int fileInfoHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    // reinterpret_cast is used to convert unsigned char* to a signed char
    file.read(reinterpret_cast<char *>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        cout << "The file is not a BitMap!\n";
        file.close();
        return;
    }

    unsigned char infoHeader[fileInfoHeaderSize];
    file.read(reinterpret_cast<char *>(infoHeader), fileInfoHeaderSize);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

    colours.resize(width * height);

    const int paddingAmount = ((4 - (width * 3) % 4) % 4);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char colour[3];
            file.read(reinterpret_cast<char *>(colour), 3);
            colours[y * width + x].r = static_cast<float>(colour[2]) / 255.0f;
            colours[y * width + x].g = static_cast<float>(colour[1]) / 255.0f;
            colours[y * width + x].b = static_cast<float>(colour[0]) / 255.0f;
        }

        file.ignore(paddingAmount);
    }

    file.close();

    cout << "File was read successfully!\n";
}

void Image::exportImage(const char *path)
{
    ofstream file;
    file.open(path, iostream::out | ios::binary);
    if (!file.is_open())
    {
        cout << "Unfortunately, the file could not be opened! \n Please enter a valid path." << endl;
    }

    unsigned char bmpPadding[3] = {0, 0, 0};
    const int paddingAmmount = ((4 - (width * 3) % 4) % 4);
    const int fileHeaderSize = 14;
    const int fileInfoHeaderSize = 40;
    const int fileSize = fileHeaderSize + fileInfoHeaderSize + (width * height * 3) + (paddingAmmount * height);

    // The file header (14 bytes):
    unsigned char fileHeader[fileHeaderSize];
    // filetype
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // file size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // reserved 1 - unused
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // reserved 2 - unused
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // pixel data offset
    fileHeader[10] = fileHeaderSize + fileInfoHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    // The information header(40 bytes):
    unsigned char infoHeader[fileInfoHeaderSize];
    // file size
    infoHeader[0] = fileInfoHeaderSize;
    infoHeader[1] = 0;
    infoHeader[2] = 0;
    infoHeader[3] = 0;
    // image width
    infoHeader[4] = width;
    infoHeader[5] = width >> 8;
    infoHeader[6] = width >> 16;
    infoHeader[7] = width >> 24;
    // image height
    infoHeader[8] = height;
    infoHeader[9] = height >> 8;
    infoHeader[10] = height >> 16;
    infoHeader[11] = height >> 24;
    // planes
    infoHeader[12] = 1;
    infoHeader[13] = 0;
    // bits per pixel
    infoHeader[14] = 24;
    infoHeader[15] = 0;
    // compression
    infoHeader[16] = 0;
    infoHeader[17] = 0;
    infoHeader[18] = 0;
    infoHeader[19] = 0;
    // image size (no compression)
    infoHeader[20] = 0;
    infoHeader[21] = 0;
    infoHeader[22] = 0;
    infoHeader[23] = 0;
    // X pixels per meter - unspecified
    infoHeader[24] = 0;
    infoHeader[25] = 0;
    infoHeader[26] = 0;
    infoHeader[27] = 0;
    // Y pixels per meter - unspecified
    infoHeader[28] = 0;
    infoHeader[29] = 0;
    infoHeader[30] = 0;
    infoHeader[31] = 0;
    // total colours (colour palette unused)
    infoHeader[32] = 0;
    infoHeader[33] = 0;
    infoHeader[34] = 0;
    infoHeader[35] = 0;
    // important colour (generally ignored)
    infoHeader[36] = 0;
    infoHeader[37] = 0;
    infoHeader[38] = 0;
    infoHeader[39] = 0;

    // The pixel array:
    file.write(reinterpret_cast<char *>(fileHeader), fileHeaderSize);
    file.write(reinterpret_cast<char *>(infoHeader), fileInfoHeaderSize);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char r = static_cast<unsigned char>(getColour(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColour(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColour(x, y).b * 255.0f);

            unsigned char colour[] = {b, g, r};
            file.write(reinterpret_cast<char *>(colour), 3);
        }

        file.write(reinterpret_cast<char *>(bmpPadding), paddingAmmount);
    }

    file.close();

    cout << "File created successfully!\n";
}

void Image::convertToGreyscale()
{
    vector<Colour>::iterator it;

    for (it = colours.begin(); it != colours.end(); it++)
    {
        Colour temp = *it;
        float value = (temp.r / 3) + (temp.g / 3) + (temp.b / 3);
        temp.r = value;
        temp.g = value;
        temp.b = value;
        *it = Colour(temp);
    }
}

vector<char> Image::convertToASCII()
{
    vector<Colour>::iterator it;
    vector<char> chars;
    string greyScale = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    for (it = colours.begin(); it != colours.end(); it++)
    {
        Colour temp = *it;
        chars.push_back(greyScale[ceil((greyScale.length() - 1) * ((temp.r + temp.g + temp.b) / 3))]);
    }

    return chars;
}

string Image::displayASCII(vector<char> ascii)
{
    string result;

    for (int y = height - 1; y > 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            /* The number of repetitions of the pixel can be modified to make the image appear "wider" in the text file.
             
             However, be careful not to repeat the pixel too much with higher resolution images, as the maximum number of characters that can be displayed in Notepad is 1024.

            For example, with an image 500  pixels wide, repeating the pixels once is fine, but twice is problematic. For an image 200 pixels wide, upto 4 repetitions are possible

            */
            result += ascii[y * width + x];
            result += ascii[y * width + x];
        }
        result += "\n";
    }
    result += "\n";

    return result;
}

void Image::exportToTextFile(const char *path, string chars)
{
    ofstream file(path);

    file << chars;

    file.close();
}