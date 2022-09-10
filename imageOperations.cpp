/** *********************************************************************
 * @file
 *
 * @brief   contains functions that manipulate images 
 ***********************************************************************/

#include "netPBM.h"

 /** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This function takes a struct of type image as input. It then proceeds to allocate three new temporary 
  * 2D dynamic arrays with pixel datatype, each for red, green, and blue channels respectively.
  * The function checks to see if the memory has been allocated and exits with zero if not.
  * The dimensions of these arrays are cols x rows, since the image is to be rotated clockwise.
  * The function then proceeds to execute two loops which interchange the rows of the original 
  * image for the columns of the resulting image. The first row of the original image is now at the 
  * last column for the modified image. The free2D function is called to delete the original 2D arrays of 
  * the structure. They are then assigned new dimensions of cols x rows using the alloc2D function. Memory 
  * allocation success is checked for again. Then the data from the temporary arrays is copied into the newly 
  * allocated arrays of the structure. The memory allocated to the temporary arrays is then freed up. 
  * The rows and columns parameters of the strucutre are also exchanged to reflect the dimensions of the new image.
  * 
  *
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    
    //rotating an image of dimensions 210 x 771 clockwise
    img.rows = 210;
    img.cols = 771;

    rotateClockwise(img);

    //img now contains a clockwise image of dimensions 771 x 210.
    //img.rows = 771;
    //img.cols = 210;

    @endverbatim

  ***********************************************************************/
void rotateClockWise(image &img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;    

    //assigning the values of rows and columns of flip X
    rows = img.rows;
    cols = img.cols;    

    //temporary 2D arrays
    pixel** redGrayTemp = nullptr;
    pixel** greenTemp = nullptr;
    pixel** blueTemp = nullptr;

    //allocate three new 2D arrays
    redGrayTemp = alloc2D(cols, rows);
    greenTemp = alloc2D(cols, rows);
    blueTemp = alloc2D(cols, rows);

    //if memory allocation fails
    if ((redGrayTemp == nullptr) || (greenTemp == nullptr) || (blueTemp == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //two for loops 
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            redGrayTemp[j][img.rows - i - 1] = img.redGray[i][j];
            greenTemp[j][img.rows - i - 1] = img.green[i][j];
            blueTemp[j][img.rows - i - 1] = img.blue[i][j];

        }
    }

    //freeing up the memory allocated to img.redgray, img.green, img.blue
    free2D(img.redGray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    //making a new size for the img pointers
    img.redGray = alloc2D(cols, rows);
    img.green = alloc2D(cols, rows);
    img.blue = alloc2D(cols, rows);

    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //assigning each value of temporary arrays to structure
    copy2D(img.redGray, redGrayTemp, cols, rows);
    copy2D(img.green, greenTemp, cols, rows);
    copy2D(img.blue, blueTemp, cols, rows);

    //freeing up the memory allocated to temporary arrays
    free2D(redGrayTemp, cols);
    free2D(greenTemp, cols);
    free2D(blueTemp, cols);

    //changing the values of rows and columns
    img.rows = cols;
    img.cols = rows;    
 
        
    
}



/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This function takes a struct of type image as input. It then proceeds to allocated three new 2D
  * dynamic arrays with pixel datatype, each for red, green, and blue channels respectively.
  * The function checks to see if the memory has been allocated and exits with zero if not.
  * The dimensions of these arrays are cols x rows, since the image is to be rotated counter clockwise.
  * The function then proceeds to execute two loops which interchange the rows of the original
  * image for the columns of the resulting image. The first row of the original image is now at the
  * first column for the modified image. The free2D function is called to delete the original 2D arrays of 
  * the structure. They are then assigned new dimensions of cols x rows using the alloc2D function. Memory 
  * allocation success is checked for again. Then the data from the temporary arrays is copied into the newly 
  * allocated arrays of the structure. The memory allocated to the temporary arrays is then freed up. 
  * The rows and columns parameters of the strucutre are also exchanged to reflect the dimensions of the new image.
  *
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    //rotating an image of dimensions 210 x 771 counter clockwise
    img.rows = 210;
    img.cols = 771;

    rotateCounterClockwise(img);

    //img now contains a counter clockwise image of dimensions 771 x 210.
    //img.rows = 771;
    //img.cols = 210;

    @endverbatim

  ***********************************************************************/
void rotateCounterClockWise(image& img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;

    //assigning the values of rows and columns of flip X
    rows = img.rows;
    cols = img.cols;

    //temporary 2D arrays
    pixel** redGrayTemp = nullptr;
    pixel** greenTemp = nullptr;
    pixel** blueTemp = nullptr;

    //allocate three new 2D arrays
    redGrayTemp = alloc2D(cols, rows);
    greenTemp = alloc2D(cols, rows);
    blueTemp = alloc2D(cols, rows);

    //if memory allocation fails
    if ((redGrayTemp == nullptr) || (greenTemp == nullptr) || (blueTemp == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }


    //two for loops 
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            redGrayTemp[img.cols -1 -j][i] = img.redGray[i][j];
            greenTemp[img.cols - 1 - j][i] = img.green[i][j];
            blueTemp[img.cols - 1 - j][i] = img.blue[i][j];

        }
    }

    //freeing up the memory allocated to img.redgray, img.green, img.blue
    free2D(img.redGray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    //making a new size for the img pointers
    img.redGray = alloc2D(cols, rows);
    img.green = alloc2D(cols, rows);
    img.blue = alloc2D(cols, rows);


    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }


    //assigning each value of temporary arrays to structure
    copy2D(img.redGray, redGrayTemp, cols, rows);
    copy2D(img.green, greenTemp, cols, rows);
    copy2D(img.blue, blueTemp, cols, rows);

    //free up the memory allocated to the temporary arrays
    free2D(redGrayTemp, cols);
    free2D(greenTemp, cols);
    free2D(blueTemp, cols);

    //changing the values of rows and columns
    img.rows = cols;
    img.cols = rows;    

    

}



/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This function takes a struct of type image as input. It then proceeds to allocated three new temporary 2D
  * dynamic arrays with pixel datatype, each for red, green, and blue channels respectively.
  * The function checks if the memory has been allocated and exits with a zero if it did not.
  * The dimensions of these arrays are rows x cols, since flipping on X axis does not affect dimensions.
  * The function then proceeds to execute two loops which interchange the rows of the original
  * image for the mirroring rows of the resulting image. The first row of the original image is now at the
  * last row for the modified image. The mth row is now at the (rows - m)th row in the resulting image. The 
  * values of row and column for img do not the change. The free2D function is called to delete the original 2D arrays of 
  * the structure. They are then assigned new dimensions of cols x rows using the alloc2D function. Memory 
  * allocation success is checked for again. Then the data from the temporary arrays is copied into the newly 
  * allocated arrays of the structure. The memory allocated to the temporary arrays is then freed up. 
  * The rows and columns parameters of the strucutre are also exchanged to reflect the dimensions of the new image.
  *
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    //flipping an image of dimensions 210 x 771 on the X axis
    img.rows = 210;
    img.cols = 771;

    flipAxisX(img);

    //img now contains a flipped image on X axis of dimensions 210 x 771.
    //img.rows = 210;
    //img.cols = 771;

    @endverbatim

  ***********************************************************************/
void flipAxisX(image &img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;

    //assigning the values of rows and columns of flip X
    rows = img.rows;
    cols = img.cols;

    //temporary 2D arrays
    pixel** redGrayTemp = nullptr;
    pixel** greenTemp = nullptr;
    pixel** blueTemp = nullptr;

    //allocate three new 2D arrays
    redGrayTemp = alloc2D(rows, cols);
    greenTemp = alloc2D(rows, cols);
    blueTemp = alloc2D(rows, cols);

    if (redGrayTemp == nullptr || greenTemp == nullptr || blueTemp == nullptr)
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //two for loops 
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {

            redGrayTemp[rows - i - 1][j] = img.redGray[i][j];
            greenTemp[rows - i - 1][j] = img.green[i][j];
            blueTemp[rows - i - 1][j] = img.blue[i][j];

        }
    }


    //freeing up the memory allocated to img.redgray, img.green, img.blue
    free2D(img.redGray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    //making a new size for the img pointers
    img.redGray = alloc2D(rows, cols);
    img.green = alloc2D(rows, cols);
    img.blue = alloc2D(rows, cols);


    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //assigning each value of temporary arrays to structure
    copy2D(img.redGray, redGrayTemp, rows, cols);
    copy2D(img.green, greenTemp, rows, cols);
    copy2D(img.blue, blueTemp, rows, cols);

    //free up the memory allocated to the temporary arrays
    free2D(redGrayTemp, rows);
    free2D(greenTemp, rows);
    free2D(blueTemp, rows);

    
}



/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This function takes a struct of type image as input. It then proceeds to allocated three new temporary 2D
  * dynamic arrays with pixel datatype, each for red, green, and blue channels respectively.
  * The function checks if the memory has been allocated and exits with a zero if it did not.
  * The dimensions of these arrays are rows x cols, since flipping on Y axis does not affect dimensions.
  * The function then proceeds to execute two loops which interchange the columns of the original
  * image for the mirroring columns of the resulting image. The first column of the original image is now at the
  * last column for the modified image. The nth column is now at the (cols - n)th column in the resulting image. The
  * values of row and column for img do not the change. The free2D function is called to delete the original 2D arrays of 
  * the structure. They are then assigned new dimensions of rows x cols using the alloc2D function. Memory 
  * allocation success is checked for again. Then the data from the temporary arrays is copied into the newly 
  * allocated arrays of the structure. The memory allocated to the temporary arrays is then freed up. 
  *
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim

   //flipping an image of dimensions 210 x 771 on the Y axis
    img.rows = 210;
    img.cols = 771;

    flipAxisY(img);

    //img now contains a flipped image on Y axis of dimensions 210 x 771.
    //img.rows = 210;
    //img.cols = 771;

    @endverbatim

  ***********************************************************************/
void flipAxisY(image& img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;

    //assigning the values of rows and columns of flip X
    rows = img.rows;
    cols = img.cols;

    //temporary 2D arrays
    pixel** redGrayTemp = nullptr;
    pixel** greenTemp = nullptr;
    pixel** blueTemp = nullptr;

    //allocate three new 2D arrays
    redGrayTemp = alloc2D(rows, cols);
    greenTemp = alloc2D(rows, cols);
    blueTemp = alloc2D(rows, cols);

    //if memory allocation fails
    if (redGrayTemp == nullptr || greenTemp == nullptr || blueTemp == nullptr)
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //two for loops 
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            redGrayTemp[i][cols - j -1] = img.redGray[i][j];
            greenTemp[i][cols - j - 1] = img.green[i][j];
            blueTemp[i][cols - j - 1] = img.blue[i][j];

        }
    }


    //freeing up the memory allocated to img.redgray, img.green, img.blue
    free2D(img.redGray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    //making a new size for the img pointers
    img.redGray = alloc2D(rows, cols);
    img.green = alloc2D(rows, cols);
    img.blue = alloc2D(rows, cols);

    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //assigning each value of temporary arrays to structure
    copy2D(img.redGray, redGrayTemp, rows, cols);
    copy2D(img.green, greenTemp, rows, cols);
    copy2D(img.blue, blueTemp, rows, cols);

    //free up the memory allocated to the temporary arrays
    free2D(redGrayTemp, rows);
    free2D(greenTemp, rows);
    free2D(blueTemp, rows);
}



/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * The convertGrayScale function covnerts a coloured image to a grayscale image. This function takes a 
  * struct of type image as input. The function then proceeds to execute two loops where the gray channel 
  * is assigned a value equal to a function of the red, green, and blue channels of the image. The gray channel 
  * equals 30% of the red channel, 60% of the green channel, and 10% of the blue channel. The value obtained 
  * from taking fractional values of each channel is a double. Since the arrays of the structure store the pixel
  * datatype, the double is typecasted to a pixel. The values of row and column for img do not the change. 
  * 
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim

   //grayscaling an image of dimensions 210 x 771
    img.rows = 210;
    img.cols = 771;

    convertGrayScale(img);

    //img now contains a grayscaled image of dimensions 210 x 771.
    //img.rows = 210;
    //img.cols = 771;

    @endverbatim

  ***********************************************************************/
void convertGrayScale(image& img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;

    //assigning the respective values
    rows = img.rows;
    cols = img.cols;

        
    //looping through each element of dynamic array
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            img.redGray[i][j] = (pixel) (0.3 * img.redGray[i][j] + 0.6 * img.green[i][j] + 0.1 * img.blue[i][j]);
        }
    }

    
}



/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * The convertSepia function anitiques an image. 
  * This function takes a struct of type image as input. It then proceeds to allocated three new temporary 2D
  * dynamic arrays with pixel datatype. These arrays are named tr, tg, and tb respectively.
  * The function checks if the memory has been allocated to tr, tg, and tb and exits with zero if not.
  * The dimension of these arrays is rows x cols, since anitquing an image does not affect its dimensions.
  * The function then proceeds to execute two loops where the tr, tg, and tb channels are assigned a value equal to
  * a function of the red, green, and blue channels of the original image. If the value of any element of tr, 
  * tg, or tb is greater than 255, then a value of 255 is assgined to them instead. The copy2D function is then 
  * called to copy the values from tr, tg, and tb back into the 2D arrays of the structure. The temporary arrays 
  * tr, tg, and tb are then freed up.
  *
  * @param[in,out] img - the struct of type image that is manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim

   //antiquing an image of dimensions 210 x 771
    img.rows = 210;
    img.cols = 771;

    convertSepia(img);

    //img now contains an antiqued image of dimensions 210 x 771.
    //img.rows = 210;
    //img.cols = 771;

    @endverbatim

  ***********************************************************************/
void convertSepia(image& img)
{
    //loop variables
    int i = 0;
    int j = 0;

    //initializing variables
    int rows = 0;
    int cols = 0;

    //more variables
    int r, g, b;

    //assigning the respective values
    rows = img.rows;
    cols = img.cols;

    //creating a 2D pointer
    pixel** tr = nullptr;
    pixel** tg = nullptr;
    pixel** tb = nullptr;

    //allocating a dynamic 2D array for sepia
    tr = alloc2D(img.rows, img.cols);
    tg = alloc2D(img.rows, img.cols);
    tb = alloc2D(img.rows, img.cols);

    if (tr == nullptr || tg == nullptr || tb == nullptr)
    {
        cout << "Memory Allocation Error" << endl;
        exit(0);
    }

    //looping through each element of dynamic array
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            r = (int) (0.393 * img.redGray[i][j] + 0.769 * img.green[i][j] + 0.189 * img.blue[i][j]);
            g = (int) (0.349 * img.redGray[i][j] + 0.686 * img.green[i][j] + 0.168 * img.blue[i][j]);
            b = (int) (0.272 * img.redGray[i][j] + 0.534 * img.green[i][j] + 0.131 * img.blue[i][j]);

            if (r > 255)
            {
                tr[i][j] = 255;
            }

            else
            {
                tr[i][j] = r;
            }

            if (g > 255)
            {
                tg[i][j] = 255;
            }

            else
            {
                tg[i][j] = g;
            }

            if (b > 255)
            {
                tb[i][j] = 255;
            }

            else
            {
                tb[i][j] = b;
            }

            
        }
    }

    //assigning the values back to the original array
    copy2D(img.redGray, tr, rows, cols);
    copy2D(img.green, tg, rows, cols);
    copy2D(img.blue, tb, rows, cols);

    //freeing up the temporary arrays
    free2D(tr, rows);
    free2D(tg, rows);
    free2D(tb, rows);


}