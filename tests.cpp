#include "image.h"
#include "tests.h"

void testBMPGeneration()
{
    cout << "::::::::::: Creating First BitMap Image (a colour gradient) :::::::::::\n";

    const int width1 = 1280;
    const int height1 = 720;

    Image firstImage(width1, height1);

    for (int y = 0; y < height1; y++)
    {
        for (int x = 0; x < width1; x++)
        {
            Colour temp((float)x / (float)width1, 1.0f - ((float)x / (float)width1), (float)y / (float)height1);
            firstImage.setColour(temp, x, y);
        }
    }

    cout << "::::::::::: Exporting Image :::::::::::\n";
    firstImage.exportImage("image1.bmp");

    cout << "::::::::::: Creating Second BitMap Image (another colour gradient) :::::::::::\n";

    const int width2 = 640;
    const int height2 = 40000;

    Image secondImage(width2, height2);

    for (int y = 0; y < height2; y++)
    {
        for (int x = 0; x < width2; x++)
        {
            Colour temp((float)x / (float)width2, 1.0f - ((float)x / (float)width2), (float)y / (float)height2);
            secondImage.setColour(temp, x, y);
        }
    }

    cout << "::::::::::: Exporting Image :::::::::::\n";
    secondImage.exportImage("image2.bmp");

    cout << "::::::::::: Creating Third BitMap Image (another colour gradient) :::::::::::\n";

    const int width3 = 500;
    const int height3 = 500;

    Image thirdImage(width3, height3);

    for (int y = 0; y < height3; y++)
    {
        for (int x = 0; x < width3; x++)
        {
            Colour temp((float)x / (float)width3, 1.0f - ((float)x / (float)width3), ((float)height3 * (float)y));
            thirdImage.setColour(temp, x, y);
        }
    }

    cout << "::::::::::: Exporting Image :::::::::::\n";
    thirdImage.exportImage("image3.bmp");

    cout << "::::::::::: Creating Fourth BitMap Image (randomised pixels - looks like \"static noise\" on TV) :::::::::::\n";

    const int width4 = 1920;
    const int height4 = 1080;

    Image fourthImage(width4, height4);

    for (int y = 0; y < height4; y++)
    {
        for (int x = 0; x < width4; x++)
        {
            // int randNum formula to generate a random number between 0 and 255 (inclusive): int randNum = rand()%(max-min + 1) + min;
            Colour temp(rand() % 256, rand() % 256, rand() % 256);
            fourthImage.setColour(temp, x, y);
        }
    }

    cout << "::::::::::: Exporting Image :::::::::::\n";
    fourthImage.exportImage("image4.bmp");

    cout << "::::::::::: Creating Fifth BitMap Image (checker-boaord pattern in 64*64 pixels) :::::::::::\n";

    const int width5 = 64;
    const int height5 = 64;

    Image fifthImage(width5, height5);

    for (int y = 0; y < height5; y++)
    {
        for (int x = 0; x < width5; x++)
        {
            // if even x and even y ==> green, else ==> non-green
            Colour greenPixel(3, 252, 82);
            Colour purplePixel(182, 3, 252);
            if ((x % 2 == 0) && (y % 2 == 0))
            {
                fifthImage.setColour(greenPixel, x, y);
            }
            else
            {
                fifthImage.setColour(purplePixel, x, y);
            }
        }
    }

    cout << "::::::::::: Exporting Image :::::::::::\n";
    fifthImage.exportImage("image5.bmp");

    cout << "::::::::::: Creating Sixth BitMap Image (smileyface in 10*10 grid) :::::::::::\n";

    const int width6 = 10;
    const int height6 = 10;

    Image sixthImage(width6, height6);

    for (int y = 0; y < height6; y++)
    {
        for (int x = 0; x < width6; x++)
        {
            Colour bluePixel(233, 227, 186);
            sixthImage.setColour(bluePixel, x, y);
        }
    }

    Colour greenPixel(2, 40, 32);
    sixthImage.setColour(greenPixel, 3, 6);
    sixthImage.setColour(greenPixel, 6, 6);

    sixthImage.setColour(greenPixel, 2, 2);
    sixthImage.setColour(greenPixel, 3, 2);
    sixthImage.setColour(greenPixel, 4, 2);
    sixthImage.setColour(greenPixel, 5, 2);
    sixthImage.setColour(greenPixel, 6, 2);
    sixthImage.setColour(greenPixel, 7, 2);

    cout << "::::::::::: Exporting Image :::::::::::\n";
    sixthImage.exportImage("image6.bmp");
}

void testReadingBMP()
{
    cout << "::::::::: Testing Reading Capabilities ::::::::::" << endl;

    Image copy(0, 0);
    copy.readImage("readMe.bmp");
    copy.exportImage("copy.bmp");

    cout << "::::::::: Reading Tests Complete ::::::::::" << endl;
}

void testReadingImageProperties()
{
    Image readME(0, 0);
    readME.readImage("readMe.bmp");
    vector<Colour> result = readME.getRGBValues();

    vector<Colour>::iterator it;
    cout << ":::::::::: Getting readMe.bmp's properties ::::::::::\n";
    cout << "Width: " << readME.getWidth() << "\nHeight: " << readME.getHeight() << endl;

    cout << "RGB Values: \n";
    for (it = result.begin(); it != result.end(); it++)
    {
        cout << *it << endl;
    }
    cout << ":::::::::: Getting readMe.bmp's properties complete ::::::::::\n";
}

void testConvertAndExport()
{
    cout << ":::::::::: Testing converting to greyscale :::::::::\n";

    Image colour(0, 0);
    colour.readImage("colour.bmp");
    colour.convertToGreyscale();
    colour.exportImage("grey.bmp");

    cout << ":::::::::: Testing converting to greyscale complete :::::::::\n";

    cout << ":::::::::: Testing converting to ASCII :::::::::\n";

    vector<char> temp = colour.convertToASCII();

    vector<char>::iterator it;

    for (it = temp.begin(); it != temp.end(); it++)
    {
        cout << *it << endl;
    }

    cout << ":::::::::: Testing converting to ASCII complete:::::::::\n";

    cout << ":::::::::: Testing displaying in ASCII :::::::::\n";

    string imageASCII = colour.displayASCII(temp);

    cout << imageASCII << endl;

    cout << ":::::::::: Testing displaying in ASCII :::::::::\n";

    cout << ":::::::::: Testing exporting ASCII to text file :::::::::\n";

    colour.exportToTextFile("ascii.txt", imageASCII);

    cout << ":::::::::: Testing exporting ASCII to text file complete :::::::::\n";
}

void runAllTests()
{
    testBMPGeneration();
    testReadingBMP();
    testReadingImageProperties();
    testConvertAndExport();
}