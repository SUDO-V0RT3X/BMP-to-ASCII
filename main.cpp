// a program to convert an image (bmp format) into an ASCII representation, using C++11
// created by vortex January 2025

#include "image.h"
#include "tests.h"
using namespace std;

int main()
{
    // runAllTests();

    cout << "Enter the name of the .bmp file WITHOUT the file extentsion: ";
    string fileNameStr;
    cin >> fileNameStr;

    string fileNameStrExt = fileNameStr + ".bmp";
    const char *fileName = fileNameStrExt.data();

    cout << "\n\n Reading image . . . \n";
    Image image(0, 0);
    image.readImage(fileName);
    cout << "Reading complete . . .\n\n";

    cout << "Converting to greyscale . . . \n";
    image.convertToGreyscale();
    cout << "Converting complete . . .\n\n";

    cout << "Converting to greyscale . . . \n";
    image.convertToGreyscale();
    string fileNameStrGrey = fileNameStr + " Grey.bmp";
    const char *greyName = fileNameStrGrey.data();
    image.exportImage(greyName);
    cout << "Converting complete . . .\n\n";

    cout << "Converting to ASCII . . . \n";
    vector<char> imageASCII = image.convertToASCII();
    string imageString = image.displayASCII(imageASCII);
    cout << "Converting complete . . .\n\n";

    cout << "Exporting to text file . . .\n";
    string fileNameTxt = fileNameStr + ".txt";
    const char *txtName = fileNameTxt.data();
    image.exportToTextFile(txtName, imageString);

    return 0;
}