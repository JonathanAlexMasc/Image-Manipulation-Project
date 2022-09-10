#pragma once

/** *********************************************************************
 * @file
 *
 * @brief Contains the includes, definitions, strucutre, typedef, and 
 *        the prototypes for all the functions used in the program.
 ***********************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/**
 * @brief Prevents multiple declarations
 * 
 */
#ifndef __NETPBM__H__
#define __NETPBM__H__

/************************************************************************
 *             Typedefs and Strucutres
 ***********************************************************************/

 /**
 * @brief The datatype of the 2D arrays used to store image data.
 */
typedef unsigned char pixel;


 /**
 * @brief Holds the image data from the file. Passed around to different functions in the program. 
 *        Passed by reference only when necessary.
 */
struct image
{
    string magicNumber;   /**< The number which specifies if the file contains binary or ascii data. */
    string comment;       /**< The comments which start with a # symbol. Saved and printed to output file. */
    int rows;             /**< Height of the image. */
    int cols;             /**< Width of the image. */
    pixel** redGray;      /**< Dynamic 2D array which stores all the data for the red channel of the image. */
    pixel** green;        /**< Dynamic 2D array which stores all the data for the green channel of the image. */
    pixel** blue;         /**< Dynamic 2D array which stores all the data for the blue channel of the image. */

};



/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/

//imageFileIO prototypes
bool openInputFile(ifstream& bfin, string filename);

void readMagicNum(ifstream& bfin, image& img, int& max_pix_val);

void readFileP3(ifstream& fin, image &img, int &max_pix_val);

void readFileP6(ifstream& fin, image& img, int& max_pix_val);

void outputP3(ofstream& fout, image img, string basename, int max_pix_val);

void outputP6(ofstream& fout, image img, string basename, int max_pix_val);

void outputGrayP2(ofstream& fout, image img, string basename, int max_pix_val);

void outputGrayP5(ofstream& fout, image img, string basename, int max_pix_val);

void outputUsage();

//memory prototypes
//void alloc2D (pixel **&ptr, int row, int cols);
pixel** alloc2D(int rows, int cols);

void free2D (pixel**& ptr, int rows);

void copy2D(pixel**& ptr1, pixel** ptr2, int rows, int cols);

//image operations prototypes
void rotateClockWise( image &img);

void rotateCounterClockWise(image& img);

void flipAxisX(image &img);

void flipAxisY(image& img);

void convertGrayScale(image& img);

void convertSepia(image& img);
#endif