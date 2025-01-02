#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// the Colour class is used to represent individual pixels' rgb values. I.e., Image objects contain an array of Colour objects
class Colour
{
public:
    float r, g, b;
    Colour();
    Colour(float r, float g, float b);
    Colour(const Colour &copy);
    void operator=(const Colour &copy);
    ~Colour();
    friend ostream &operator<<(ostream &output, const Colour &colour);
};

class Image
{
private:
    int width;
    int height;
    vector<Colour> colours;

public:
    
    /*
    Required parts of a BMP image:

    File header (general information) - 14 bytes
    Information header (detailed information) - 40 bytes
    Pixel array (RGB values of each pixel)
     */
    
    Image(int width, int height);
    int getHeight();
    int getWidth();
    vector<Colour> getRGBValues();
    ~Image();
    Colour getColour(int x, int y) const;
    void setColour(const Colour &colour, int x, int y);
    void readImage(const char *path);
    void exportImage(const char *path);
    void convertToGreyscale();
    vector<char> convertToASCII();
    string displayASCII(vector<char> ascii);
    void exportToTextFile(const char *path, string chars);
};
