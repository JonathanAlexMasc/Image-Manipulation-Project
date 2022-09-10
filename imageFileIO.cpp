/** *********************************************************************
 * @file
 *
 * @brief   Handles input and outfiles for all the files passed to main
 ***********************************************************************/

#include "netPBM.h"

 /** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This function receives an input file stream and opens it as a binary file. 
  * Clears any error flags that have been set before opening the file.
  * Returns true if the file opened successfully. 
  * Returns false otherwise. 
  *
  * @param[in,out] fin - the input file stream.
  * @param[in] filename - name of the file to be opened.
  *
  * @returns true if file opened successfully
  * @returns false if file did not open
  *
  * @par Example:
    @verbatim
    
    string filename = "cats.ppm";
    ifstream fin; 

    openInputFile (fin, filename);
    
    //returns true if "cats.ppm" exists and can be opened. 
    //returns false otherwise.

    @endverbatim

  ***********************************************************************/
bool openInputFile( ifstream &fin, string filename)
{
    //clearing any error flags that have been set
    fin.clear();

    //opening a binary file
    fin.open(filename, ios::in | ios::binary);

    if (fin.is_open())
    {
        return true;
    }

    else
    {
        return false;
    }
}

/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * Reads the magic number of the file. The magic number is the first two bytes of the input file. 
  * If the magic number is a P3, the function seeks to beginning of input file and calls the readFileP3 function. 
  * If the magic number is a P6, the function seeks to beginning of input file and calls the readFileP6 function. 
  *
  * @param[in,out] bfin - the input file stream.
  * @param[in,out] img - a structure of type image.
  * @param[in,out] max_pix_val - maximum value that can be in a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ifstream fin;
    image img;
    int max_pix_val;

    readMagicNum(fin, img, max_pix_val);

    //reads the magic number
    //calls readFileP3 or readFileP6 file accordingly

    @endverbatim

  ***********************************************************************/
void readMagicNum(ifstream& bfin, image& img, int& max_pix_val)
{
    //clear any error flags and go to beginning of file
    bfin.clear();
    bfin.seekg(0, ios::beg);

    //read magic number
    bfin >> img.magicNumber;

    //read P3 is thats magic num
    if (img.magicNumber == "P3")
    {        
        bfin.seekg(0, ios::beg);        
        readFileP3(bfin, img, max_pix_val);
    }

    //P6 otherwise
    else if (img.magicNumber == "P6")
    {        
        bfin.seekg(0, ios::beg);
        readFileP6(bfin, img, max_pix_val);
    }

    //invalid magic number
    else
    {
        cout << "Invalid Magic Number" << endl;

        //cleaning up files
        bfin.clear();
        bfin.close();

        exit(0);
    }
}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This functions reads a file containing ascii image data. The rest of the data is also read as ascii.
  * Reads in the magic number, comments, width, height, and the maximum pixel value from the input file.
  * This data is then stored into the structure that has been passed by reference to this function. 
  * The maximum pixel value is stored into the variable max_pix_val that has been passed by reference.
  * Using the width and height, the function allocates 3 2D dynamic arrays using the alloc2D function.
  * The function then proceeds to read in the image data into these dynamically allocated arrays. 
  * The data is supplied for each row. Each column in every row has three values - the red, green, and 
  * blue channel.
  *
  * @param[in,out] bfin - the input file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ifstream fin;
    image img;
    int max_pix_val;

    
    readFileP3(fin, img, max_pix_val);

    //reads image data into the structure img.

    @endverbatim

  ***********************************************************************/
void readFileP3(ifstream& bfin, image &img, int &max_pix_val)
{
    //loop variable
    int i = 0;
    int j = 0;

    //variables to read line in
    string line;

    //variables for reading in image data
    int r, g, b;

    //reading in image header
    bfin >> img.magicNumber;
    bfin.ignore();
    
    //getting the comment
    while (getline(bfin, line, '\n') && line[0] == '#') 
    {
        img.comment += line + "\n";
    }

    
        
    //getting the width and height
    img.cols = stoi(line.substr(0, line.find(' ')));
    img.rows = stoi(line.substr(line.find(' ')));

    //maximum pixel value    
    bfin >> max_pix_val;
    
    //dynamically allocating 3 2D arrays
    img.redGray = alloc2D(img.rows, img.cols);
    img.green = alloc2D(img.rows, img.cols);
    img.blue = alloc2D(img.rows, img.cols);

    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //read in image data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            bfin >> r >> g >> b;

            //assign these values to the array
            img.redGray[i][j] = (pixel)r;
            img.green[i][j] = (pixel)g;
            img.blue[i][j] = (pixel)b;
        }


    }

    

}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This functions reads a file containing binary image data. The rest of the data is read in as ascii.
  * Reads in the magic number, comments, width, height, and the maximum pixel value from the input file.
  * This data is then stored into the structure that has been passed by reference to this function. 
  * The maximum pixel value is stored into the variable max_pix_val that has been passed by reference.
  * Using the width and height, the function allocates 3 2D dynamic arrays using the alloc2D function.
  * The function then proceeds to read in the image data into these dynamically allocated arrays. 
  * Since the image data is in binary, it uses the .read() function to read in the data into the arrays.
  * The data is supplied for each row. Each column in every row has three values - the red, green, and 
  * blue channel.
  *
  * @param[in,out] bfin - the input file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ifstream fin;
    image img;
    int max_pix_val;

    readFileP6(fin, img, max_pix_val);

    //reads image data in binary and stores it into the structure img.
    @endverbatim

  ***********************************************************************/
void readFileP6(ifstream& bfin, image& img, int& max_pix_val)
{
    //loop variable
    int i = 0;
    int j = 0;

    //variables to read line in
    string line;   

    //reading in image header
    bfin >> img.magicNumber;
    bfin.ignore();

    //getting the comment
    while (getline(bfin, line, '\n') && line[0] == '#') {
        img.comment += line + "\n";
    }

    //getting values for rows and columns
    img.cols = stoi(line.substr(0, line.find(' ')));
    img.rows = stoi(line.substr(line.find(' ')));

    //maximum pixel value    
    bfin >> max_pix_val;
    bfin.ignore();

    //dynamically allocating 3 2D arrays
    img.redGray = alloc2D(img.rows, img.cols);
    img.green = alloc2D(img.rows, img.cols);
    img.blue = alloc2D(img.rows, img.cols);

    //if memory allocation fails
    if ((img.redGray == nullptr) || (img.green == nullptr) || (img.blue == nullptr))
    {
        cout << "Memory Allocation Failed" << endl;
        exit(0);
    }

    //read in image data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {

            bfin.read((char*)&img.redGray[i][j], sizeof(pixel));
            bfin.read((char*)&img.green[i][j], sizeof(pixel));
            bfin.read((char*)&img.blue[i][j], sizeof(pixel));

        }


    }


}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This functions outputs the image data to a binary file in ascii. The name of the output file
  * is given by "basename.ppm". Outputs the magic number, comment, width, height, and the maximum 
  * pixel value from the input file. The function then proceeds to output the image data onto the output file.
  * The image data is outputted in ascii format. ofstream fout is used to output the all the data to the file.
  * The order of the data for the output file is the same as that for the input file. The data is supplied for 
  * each row. Each column in every row has three values - the red, green, and blue channel. The pixel values stored
  * in the red, green, and blue channels are typecasted to integers. 
  *
  * @param[in,out] fout - the input file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in] basename - name of the output file.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ofstream fout;
    image img;
    string basename;
    int max_pix_val;

    basename = "dogs.ppm";

    outputP3(fout, img, basename, max_pix_val);

    //outputs the data in img to a file called "dogs.ppm"
    //data output format is in ascii

    @endverbatim

  ***********************************************************************/
void outputP3 (ofstream &fout, image img, string basename, int max_pix_val)
{ 
    int i = 0;
    int j = 0;

    //opening the output file
    fout.clear();
    fout.open(basename + ".ppm", ios::out);

    //output to P3
    fout << "P3" << "\n";
    
    //output the comment/s
    fout << img.comment;

    //output width and height 
    fout << img.cols << " " << img.rows << "\n";

    //output maximum pixel value
    fout << max_pix_val << "\n";

    //outputing image data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            
            fout << (int) img.redGray[i][j] << endl;
            fout << (int) img.green[i][j] << endl;
            fout << (int) img.blue[i][j] << endl;
            
        }
    }
}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * This functions outputs the image data to a binary file in binary format. The rest of the data is still 
  * ascii. Outputs the magic number, comment, width, height, and the maximum pixel value to the output file.
  * This data is still in ascii and outputted using ofstream fout to the output file.
  * The function then proceeds to output the image data onto the output file specified by basename.
  * The output file is named "basename.ppm". Since the image data is to be outputted
  * in binary format, the .write() function is used to output the data to the file. The order of the data in the
  * output file is the same as that in the input file. The image data is supplied for each row. Each column in every 
  * row has three values - the red, green, and blue channel. 
  *
  * @param[in,out] fout - the input file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in] basename - name of the output file.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ifstream fout;
    image img;
    string basename;
    int max_pix_val;

    basename = "dogs.ppm";

    outputP6(fout, img, basename, max_pix_val);

    //outputs data to a file called "dogs.ppm"
    //All the data upto the maximum pixel value is in ascii
    //Following that, the image data is stored in binary

    @endverbatim

  ***********************************************************************/
void outputP6(ofstream& fout, image img, string basename, int max_pix_val)
{
    int i = 0;
    int j = 0;

    //opening the output file
    fout.clear();
    fout.open(basename + ".ppm", ios::out | ios::trunc | ios::binary);

    //output to P3
    fout << "P6" << "\n";

    //output the comment
    fout << img.comment;

    //output width and height
    fout << img.cols << " " << img.rows << "\n";

    //output maximum pixel value
    fout << max_pix_val << "\n";

    //outputing image data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            
            //write the three channels to binary file
            fout.write((char*)&img.redGray[i][j], sizeof(pixel));
            fout.write((char*)&img.green[i][j], sizeof(pixel));
            fout.write((char*)&img.blue[i][j], sizeof(pixel));
        }
    }
}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * The function outputs image data in an ascii format to the output file. The output file type is a .pgm which 
  * represents a grayscale image file. This function only outputs the data in img.redGray channel.  
  * It first outputs the magic number P2 to the top of the output file. Then outputs the comments, width, and 
  * height stored in the structure that is passed to the function. Then it outputs the maximum value that can be 
  * stored in a pixel - the max_pix_val. Then it outputs all the image data in an ascii format to the file 
  * by typecasting the pixel values stored in img.redGray to integers. 
  *
  * @param[in,out] fout - the output file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in] basename - name of the output file.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ofstream fout;
    image img;
    string basename;
    int max_pix_val;

    basename = "dogs.ppm";

    outputGrayP2(fout, img, basename, max_pix_val);

    //outputs the data in ascii format to a file "dogs.ppm"
    //all the data is outputted in ascii

    @endverbatim

  ***********************************************************************/
void outputGrayP2(ofstream& fout, image img, string basename, int max_pix_val)
{
    int i = 0;
    int j = 0;

    //opening the output file
    fout.clear();
    fout.open(basename + ".pgm", ios::out);

    //output to P2
    fout << "P2" << "\n";

    //output comment
    fout << img.comment;

    //output width and height
    fout << img.cols << " " << img.rows << "\n";

    //output maximum pixel value
    fout << max_pix_val << "\n";

    //outputting image data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout << (int) img.redGray[i][j] << endl;
        }
    }
}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * The function outputs image data in an binary format to the output file. The output file type is a .pgm which 
  * represents a grayscale image file. This function only outputs the data in the img.redGray channel.  
  * It first outputs the magic number P5 to the top of the output file. The magic number P5 specifies that it 
  * is a grayscale image file with binary image data. The function then outputs the comments, width, and 
  * height stored in the structure that is passed to the function. Then it outputs the maximum value that can be 
  * stored in a pixel - the max_pix_val. Then it outputs all the image data in a binary format to the file 
  * by using the .write() function.  
  *
  * @param[in,out] fout - the input file stream.
  * @param[in,out] img - a strucutre of type image.
  * @param[in] basename - name of the output file.
  * @param[in,out] max_pix_val - maximum value of a pixel.
  *
  * @returns none
  *
  * @par Example:
    @verbatim

    ofstream fout;
    image img;
    string basename;
    int max_pix_val;

    basename = "dogs.ppm";

    outputGrayP5(fout, img, basename, max_pix_val);

    //outputs the data till max_pix_val in ascii to a file called "dogs.ppm"
    //the image data is then outputted in binary

    @endverbatim

  ***********************************************************************/
void outputGrayP5(ofstream& fout, image img, string basename, int max_pix_val)
{
    //loop variables
    int i = 0;
    int j = 0;

    //opening the output file
    fout.clear();
    fout.open(basename + ".pgm", ios::out | ios::trunc | ios::binary);

    //output to P3
    fout << "P5" << "\n";

    //output comment
    fout << img.comment;

    //output width and height
    fout << img.cols << " " << img.rows << "\n";

    //output maximum pixel value
    fout << max_pix_val << "\n";

    //loop to output grayscale data
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout.write((char*)&img.redGray[i][j], sizeof(pixel));
        }
    }
}



/** ***************************************************************************
 * @author Jonathan Mascarenhas
 *
 * @par Description
 * The function outputs a usage statement if there are incorrect number of command line arguments
 * or an incorrect option or output type that may have been entered by the user at the command line 
 * terminal.
 *
 * @param none
 *
 * @returns none
 *
 * @par Example
 * @verbatim
   c:\> thpExam1.exe [option] --outputtype basename image.ppm
   d:\> c:\bin\thpExam1.exe [option] --outputtype basename image.ppm

         Output Type 
             --ascii                integer text numbers will be written for the data
             --binary               integer numbers will be written in binary form

         Option Code                Option Description
             --flipX                Flip the image on the X axis
             --flipY                Flip the image on the Y axis
             --rotateCW             Rotate the image clockwise
             --rotateCCW            Rotate the image counterclockwise
             --grayscale            Convert the image to grayscale
             --sepia                Antique a color image
   @endverbatim
 *****************************************************************************/
void outputUsage()
{
    cout << "Usage: " << endl;
    
    cout << "c:\\> thpExam1.exe [option] --outputtype basename image.ppm" << endl;
    cout << "d:\\> c:\\bin\\thpExam1.exe [option] --outputtype basename image.ppm" << endl;
    cout << "\n";

    
    cout << "Option Code" << setw(25) << "Option Description" << endl;
    cout << "--flipX" << setw(39) << "Flip the image on the X axis" << endl;
    cout << "--flipY" << setw(39) << "Flip the image on the Y axis" << endl;
    cout << "--rotateCW" << setw(34) << "Rotate the image clockwise" << endl;
    cout << "--rotateCCW" << setw(40) << "Rotate the image counterclockwise" << endl;
    cout << "--grayscale" << setw(37) << "Convert the image to grayscale" << endl;
    cout << "--sepia" << setw(32) << "Antique a color image" << endl;
    cout << "\n";

    cout << "Output Type" << endl;
    cout << "--ascii" << setw(60) << "integer text numbers will be written for the data" << endl;
    cout << "--binary" << setw(56) << "integer numbers will be written in binary form" << endl;
}