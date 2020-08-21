Filter MD 

- We're given a few files:
    -   bmp.h
    -   filter.c
    -   helpers.h
    -   helpers.c
    -   Makefile

- In this challenge we have 4 possible filters we can apply to an image:
    -   Greyscale   g
    -   Sepia       s
    -   Blur        b
    -   Reflect     r

** TLDR:
The challenge here is to write the code for these 4 filters (in helpers.c). 
Our goal:
-   Each of these functions should edit the 2D array of pixels in such a way 
    that the desired filter is applied to the image.

In filter.c we find the 'main' program itself, which will call the filter function that the matches the filter the user provides. 
So for example, if the user passes in 'g' when calling this program, 
    then the main function will call the greyscale function. 

Contents:
                                    Line
-   Challenge Specification         32
-   Understanding                   57
-   Hints                           152
-   Filter Functions                157

** Challenge Specification: 
-   Implement the functions in helpers.c 
    -   such that a user can apply grayscale, sepia, reflection, or blur filters to their images.

    -   greyscale 
        -   should take an image
        &   turn it into a black-and-white version of the same image

    -   sepia 
        -   should take an image
        &   turn it into a sepia version of the same image

    -   reflect
        -   should take an image
        &   reflect it horizontally

    -   blur
        -   should take an image
        &   turn it into a box-blurred version of the same image

You should not:
-   modify any of the function signatures
-   modify any other files other than helpers.c.

** Understanding

*   bmp.h
    -   You’ll see definitions of the headers (BITMAPINFOHEADER and BITMAPFILEHEADER)
    -   This file defines BYTE, DWORD, LONG, and WORD
        ->  data types normally found in the world of Windows programming
    -   BITMAPFILEHEADER and BITMAPINFOHEADER make use of these types
    -   This file also defines a struct called RGBTRIPLE
        ->  “encapsulates” three bytes: one blue, one green, and one red 
        (the order, in which we expect to find RGB triples actually on disk).
        
    Recall: 
    -   a file = a sequence of bytes (or, ultimately, bits) on disk
        ->  those bytes are generally ordered in such a way 
            that the first few represent something, the next few represent something else, and so on.
    -   “File formats” exist because the world has standardized what bytes mean what.

    -   We could just read a file from disk into RAM as one big array of bytes. 
        -> And we could just remember that the byte at array[i] represents one thing, while the byte at array[j] represents another. 
    OR 
        We could give some of those bytes names so that we can retrieve them from memory easier. 
        ->  That’s precisely what the structs in bmp.h allow us to do. 
            -   Rather than think of some file as one long sequence of bytes, 
                we can instead think of it as a sequence of structs.

*   filter.c
This file has been written already for you, it's the file we'll be running/compiling to see if our functions work as we're expecting. 

There are a couple important points worth noting here:
-   Notice the definition of filters on line 11.
    ->  That string tells the program what the allowable command-line arguments to the program are: 
        -   b   ->      blur
        -   g   ->      greyscale             
        -   r   ->      reflection
        -   s   ->      sepia

-   The next several lines 
    -   open up an image file, 
    -   make sure it’s indeed a BMP file,
    &   and read all of the pixel information into a 2D array called image.

-   Scroll down to the switch statement that begins on line 102
    -   depending on what filter we’ve chosen, 
        ->  a different function is called
    So if the user chooses filter b
        ->  case 'b' will resolve to true 
        -   then the blur function will be called
    -   each of these functions take as arguments
        -   the height of the image, 
        -   the width of the image, 
        &   the 2D array of pixels.

-   The remaining lines of the program 
    -   take the resulting image
    &   write them out to a new image file



*   helpers.h
This file is quite short, and just provides the function prototypes for the filter functions.
-   Note: 
    -   Each function takes an argument:
        ->  2D array called 'image'
        -   image = an array of (int) 'height' many rows, 
            &   and each row = (itself) another array of 'width' many RGBTRIPLEs.
        So if image represents the whole picture, 
        -   then image[0] represents the first row,
        &   image[0][0] represents the pixel in the upper-left corner of the image.

*   helpers.c
Here’s where the implementation of the functions declared in helpers.h belong. 

Note: the implementations are missing! 
->  This part is up to you.

*   Makefile
-   This file specifies what should happen when we run a terminal command like make filter.
-   Whereas programs you may have written before were confined to just one file, 
    ->  filter seems to use multiple files: 
        -   filter.c, 
        -   bmp.h, 
        -   helpers.h,
        -   & helpers.c. 
    So we’ll need to tell make how to compile this file.

Try compiling filter for yourself by going to your terminal and running
    $ make filter
Then, you can run the program by running:
    $ ./filter -g images/yard.bmp out.bmp

->  which: 
    -   takes the image at images/yard.bmp
    -   runs the pixels through the grayscale function.
    -   generates a new image called out.bmp 
If you do it now, 
-   grayscale doesn’t do anything just yet
-   so the output image should look the same as the original yard.


** Hints:
-   The values of a pixel’s rgbtRed, rgbtGreen, and rgbtBlue components are all integers, 
    -   so be sure to round any floating-point numbers to the nearest integer 
        when assigning them to a pixel value!

** Filter Functions
                        Line:
-   Greyscale           165
-   Sepia               190
-   Reflections         213
-   Blur                221


*   Greyscale
    -   Recall:
        -   if the red, green, and blue values are all set to 0x00 (hexadecimal for 0), 
            ->  then the pixel is black. 
        -   if all values are set to 0xff (hexadecimal for 255), 
            ->  then the pixel is white. 
    -   So long as the red, green, and blue values are all equal, 
        ->  the result will be varying shades of gray along the black-white spectrum, 
            -   higher values -> lighter shades (closer to white)
            &   lower values -> darker shades (closer to black).
    
    -   To convert a pixel to grayscale,
        -   The red, green & blue values should all be the same value
        -   if the original red, green, and blue values were all pretty high,
            ->  then the new value should also be pretty high.
        -   if the original values were all low 
            ->  then the new value should also be low.

        -   to ensure each pixel of the new image still has the same general brightness or darkness 
            as the old image, 
            ->  *** we can take the average of the red, green, and blue values to determine what shade of grey to make the new pixel.

        -> If you apply that to each pixel in the image, the result will be an image converted to grayscale.

    
*   Sepia
    -   Supported by most image editing programs
    -   Gives images an old-timey feel by making the whole image look a bit reddish-brown.
    -   converted to sepia by:
        -   taking each pixel
        &   computing new red, green, and blue values based on the original values of the three
    -   For this challenge, I'm asked to use a specific algorithm. 

    -   Algorith: 
        -   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        -   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        -   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

        ->  the result of each of these formulas may not be an integer, 
            ->  but each value could be rounded to the nearest integer. 

        - It's possible that the result of the formula could be a number greater than 255
            - If true:
                ->  the red, green, and blue values should be capped at 255

            -   As a result, we can guarantee that the resulting red, green, and blue values 
                will be whole numbers between 0 and 255, inclusive

* Reflections
-   a filter where the resulting image is what you would get by placing the original image
    in front of a mirror. 
    ->  So any pixels on the left side of the image should end up on the right, and vice versa.
-   Note: 
    -   All of the original pixels of the original image will still be present in the reflected image, 
        it’s just that those pixels may have rearranged to be in a different place in the image.

*   Blur    
-   There are a number of ways to create the effect of blurring or softening an image
-   For this problem, we’ll use the “box blur,” 
    ->  which works by taking each pixel 
    &   for each color value, giving it a new value 
            by averaging the color values of neighboring pixels.

-   The new value of each pixel = the average of the values of all of the pixels 
        that are within 1 row and column of the original pixel 
        ->  (forming a 3x3 box).
    EG: 
        Say we have this grid:

        1   2   3   4
        
        5   6   7   8
        
        9   10  11  12
    
        13  14  15  16

    -   To obtain each of the colour pixels for pixel 6
        -   by averaging the original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11 
            (note that pixel 6 itself is included in the average). 
    
    -   Likewise to obtain the color values for pixel 11
        -   by averaging the color values of pixels 6, 7, 8, 10, 11, 12, 14, 15 and 16.

    -   To obtain each of the colour pixels for a pixel on an edge/corner:  
        -> lets try to grab 15
        -   we would still look for all pixels within 1 row and column: 
            ->  in this case, pixels 10, 11, 12, 14, 15, and 16.

    

