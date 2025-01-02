
# BMP-to-ASCII

A simple terminal program that converts bitmap images (.bmp) to and ASCII representation, using C++11.


## Installation and usage
Installation:
```
  git clone https://github.com/SUDO-V0RT3X/BMP-to-ASCII
  cd BMP-to-ASCII
  make
```

Usage:
1. Acquire a picture in any format.
2. Resize the image to be < 1024 pixels wide (See line 264 of image.cpp for further information about image size).
3. Use an online tool, like [https://convertio.co/] or any equivalent, to convert the image to a .bmp format (if it not already in a .bmp format). You will notice that the image's file size will increase by a factor of approximately 30 (depending on the file) after converting to a .bmp format. This is because .bmp file format is not compressed, like .jpeg. Avoid using the Photos app on Windows to convert the image to a .bmp format. In my experience, it does not work.
4. Add the .bmp image in the BMP-to-ASCII folder. 
5. Uncomment line 10 in main.cpp if you want to run all the tests.
6. Run ```./main``` in Mac or Linux/WSL, or modify the makefile to compile for Windows.
7. View the .txt that is outputted using Notepad or any other equivalent. Be sure to zoom out to see the "image" and turn of the spelling checker.
    

## Screenshots

Original .bmp image:
![Before](https://raw.githubusercontent.com/SUDO-V0RT3X/BMP-to-ASCII/refs/heads/main/colour.bmp)

After converting to ASCII (whole image is not shown): 
![After](https://raw.githubusercontent.com/SUDO-V0RT3X/BMP-to-ASCII/refs/heads/main/screenshot.png)


## Problems to revisit

1.  When reading an image, you will notice that a certain number of columns of pixels are removed from the right side of the image and moved to the left side of the image.

2. The program does not automatically resize images so that they fit within a Notepad window. It strictly represents every single pixel with a single or multiple ASCII characters. A feature could be added that allows the user to choose to resize their images before converting to ASCII.

3. The program strictly uses a scale of 70 characters. Changes could be made that allow the user to choose how big of a scale they want to use.