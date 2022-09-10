/** *********************************************************************
 * @file
 *
 * @brief manipulates and outputs image data to a binary file. Contains function main.
 *        
 ***********************************************************************/

 /** ********************************************************************
  *
  * @mainpage Take Home Programming Exam 1
  *
  * @section course_section Course Information
  *
  * @authors Jonathan Mascarenhas
  *
  * @date Feburary 7, 2022
  *
  * @par Instructor:
  *         Prof. Schrader
  *
  * @par Course:
  *         CSC 215 - Section 2 - 2:00 pm 
  *
  * @par Location:
  *         Classroom Building - Room 329
  *
  * @section program_section Program Information
  *
  * @details This program takes a binary file with ascii data or binary data as input
  * and outputs the data in binary or ascii format to a binary file. The files contain 
  * data that can be used to display an image in an image processing application like GIMP.
  * 
  * The main function provides the entry into the function. Arugments are passed to it through a command line terminal.
  * After initialising all the required variables, a check for the correct number of arguments is made.
  * If the number of arguments specified are greater than five or less than four, the program displays 
  * a usage statement and exits. If the option or the output type is not entered correctly, a message is outputted
  * to the terminal which specifies the valid options and the valid output types, and the program exits. 
  * 
  * The program has a file imageFileIO.cpp which has function definitions that handle all the input and output for 
  * the program. Below is a brief description of what each function in imageFileIO.cpp does: <br>
  * 
  * <b>openInputFile</b> - opens the file passed to the function as a binary file. Returns true or false depending on 
  * whether the file opened. <br>
  * 
  * <b>readMagicNum</b> - reads the magic number at the top of the file. Calls the functions readFileP3 or readFileP6 for the 
  * magic numbers P3 and P6 respectively. If it is none of the above numbers, then a message for invalid magic number is 
  * outputted and we exit the program. <br>
  * 
  * <b>readFileP3</b> - reads all the image data from the input file in ascii and stores it into the structure passed to 
  * the function. <br>
  * 
  * <b>readFileP6</b> - reads all the image data from the input file in binary and stores it into the structure passed to 
  * the function. <br> 
  * 
  * <b>outputP3</b> - outputs the image data stored in the structure in ascii format to the output file "basename.ppm". <br> 
  * 
  * <b>outputP6</b> - outputs the image data stored in the structure in binary format to the output file "basename.ppm". <br>
  * 
  * <b>outputGrayP2</b> - outputs the image data stored in the structure in ascii format to the output file "basename.pgm". <br>
  * 
  * <b>outputGrayP5</b> - outputs the image data stored in the structure in binary format to the output file "basename.pgm" <br>
  * 
  * <b>outputUsage</b> - outputs the usage statement to the terminal if there are incorrect arugments, wrong options, or wrong <br>
  *                      output type that was was specified.
  * 
  * If there are only four arguments, input and output is performed using above functions. The ".ppm" extension specifies that 
  * the file being read is in a binary format. <br>
  * 
  * However, if the number of arugments is five, that means an option was specified in the command line arguments. This is where 
  * we use the functions in imageOperations.cpp to make changes to the <br>image data stored in the structure. Below is a brief 
  * description of what each function in imageOperations.cpp does: <br>
  * 
  * <b>rotateClockwise</b> - rotates the image clockwise.  
  * 
  * <b>rotateCounterClockwise</b> - rotates the image counter clockwise. 
  * 
  * <b>flipX</b> - flips the image on the X axis. 
  * 
  * <b>flipY</b> - flips the image on the Y axis. 
  * 
  * <b>convertGrayScale</b> - converts the image to grayscale.
  * 
  * <b>convertSepia</b> - antiques an image.
  * 
  * We can only supply one option at a time. These functions rely heavily on dynamic memory allocation and freeing up memory
  * that is allocated to temporary arrays. <br>To handle functions that deal with memory, a file called memory.cpp has been 
  * created. Below are the functions defined in memory.cpp: 
  * 
  * <b>alloc2D</b> - allocates 2D dynamic arrays and returns the pointer to these arrays. Returns nullptr if memory failed 
  * to allocate. 
  * 
  * <b>free2D</b> - frees up the memory that was allocated to a pointer. 
  * 
  * <b>copy2D</b> - has two 2D dynamic arrays passed to the function as arguments. 
  * The function copies each element from the second array into the first array.
  * 
  * Once the conversion to the image is applied (if specified), then the same procedure to output the image is followed. 
  * If the --grayscale option was specified as the second argument, then the outputGrayP2 or outputGrayP5 functions are
  * called which output the image data in ascii and binary respectively. A P2 magic number for a grayscale means that it
  * contains ascii image data and a P5 magic number for a grayscale means that it contains binary image data. <br>
  * 
  * After the data is ouputted to the file, the free2D function is called to free up the memory allocated to the pointers 
  * img.redGray, img.green, and img.blue of the image structure. Both the input files and the output files are cleared 
  * for any error flags and then closed. The main function returns a zero to end the program.
  * 
  * 
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      None
  *
  * @par Usage:
    @verbatim
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
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  * @bug Unsure how the program may respond to a failed memory allocation.
  *      I have written the code to free up the memory and exit the program.
  *
  * 
  * @todo 
  *
  * @par Modifications and Development Timeline:
    
    Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/101066570/
    csc215s22programs/-/commits/main" target =_blank>
    Click Here.</a>
  *
  ***********************************************************************/


#include "netPBM.h"

  /** *********************************************************************
   * @author Jonathan Mascarenhas
   *
   * @par Description:
   * The main function is the starting point for the program. It will take either four 
   * or five arguments to execute the program. If there are four arguments, the first one 
   * is the command required to execute the program, the second is the output type, the 
   * third is the basename for the resulting image, and the fourth is the name of the 
   * binary input file. --ascii and --binary are the two possibilities for the output type.
   * 
   * If there are five arguments, then the second argument is called option. It specifies 
   * any modifications that can be made to the image before outputting it. --flipX, --flipY,
   * --rotateCW, --rotateCCW, --grayscale, and --sepia are the allowed options.
   * 
   * Main calls a function called readMagicNum which extracts the magic number of the file. This 
   * function calls more functions which end up storing the image data in the structure img of type
   * image. If there are four arguments, the output is stored as either ascii and binary as specified.
   * If there are five arguments, it means an option was specified. Main checks which option was specified
   * and accordingly applies one of the functions in imageOperations.cpp on the image data as required. 
   * Then the image is outputted in ascii or binary. outputGrayP2 and outputGrayP5 write to a .pgm file
   * which stores data in ascii and binary respectively. 
   * 
   * The memory allocated to the 2D arrays in the structure is freed up using the free2D function. Following
   * that, the input and output files are cleared of any error flags and then closed. Then the main function 
   * returns a zero to end the program.
   *
   *
   * @param[in] argc - the number of arguments from the command prompt.
   * @param[in] argv - a 2d array of characters containing the arguments.
   *
   * @returns 0 after successful completion of the program
   *
   * @verbatim
     see usage statement above.
     @endverbatim
   *
   ***********************************************************************/

int main(int argc, char** argv)
{
    //define all the variables here
    string filename;
    string option;
    string opType;
    ifstream fin;
    ofstream fout;
    string basename;

    //maximum pixel value
    int max_pix_val = 0;

    //strucutre to store information
    image img;

        
    //checking command line arguments
    if (argc != 4 && argc != 5)
    {
        outputUsage();
        exit(0);
    }

    //checking for valid command line options

    //valid command line options for five arguments
    if (argc == 5)
    {
        filename = argv[4];
        option = argv[1];

        //checking for valid options
        if (option != "--flipX" && option != "--flipY" && option != "--rotateCW" && option != "--rotateCCW" && option != "--grayscale" && option != "--sepia")
        {
            outputUsage();

            exit(0);
        }

        opType = argv[2];

        //checking for valid output types
        if (opType != "--ascii" && opType != "--binary")
        {

            outputUsage();
            exit(0);
        }

    }

    //valid command line arguments for four options
    else 
    {
        filename = argv[3];

        opType = argv[1];

        if (opType != "--ascii" && opType != "--binary")
        {

            outputUsage();

            exit(0);
        }
    }

    //getting the basename 
    if (argc == 4)
    {
        basename = argv[2];
    }

    else 
    {
        basename = argv[3];
    }

    
    //check file opening 
    if (!(openInputFile(fin, filename)))
    {
        cout << "Unable to open input file: " << filename << endl;
        exit(0);
    }


    //reading through the file
    readMagicNum(fin, img, max_pix_val);

    //outputing to required file
    if (argc == 4)
    {
        if (strcmp(argv[1], "--ascii") == 0)
        {
            
            outputP3(fout, img, basename, max_pix_val);
        }

        else
        {
            
            outputP6(fout, img, basename, max_pix_val);
        }
    }

    else 
    {
        //Applying the image operations

        //rotating clockwise
        if (strcmp(argv[1], "--rotateCW") == 0)
        {
            
            rotateClockWise(img);
        }

        //rotate counter clockwise
        else if (strcmp(argv[1], "--rotateCCW") == 0)
        {
            
            rotateCounterClockWise(img);
        }

        // flipX
        else if (strcmp(argv[1], "--flipX") == 0)
        {
           
            flipAxisX(img);
        }

        //flipY
        else if (strcmp(argv[1], "--flipY") == 0)
        {
            
            flipAxisY(img);
        }

        //sepia
        else if (strcmp(argv[1], "--sepia") == 0)
        {
            
            convertSepia(img);
        }

        //grayscale the only option left
        else
        {
            convertGrayScale(img);

        }

        //outputting
        // 
        //outputting to grayscale and ascii speciied 
        if (strcmp(argv[1], "--grayscale") == 0 && strcmp(argv[2], "--ascii") == 0)
        {
            
            outputGrayP2(fout, img, basename, max_pix_val);
        }

        //grayscale and binary is specified
        else if (strcmp(argv[1], "--grayscale") == 0 && strcmp(argv[2], "--binary") == 0)
        {

            
            outputGrayP5(fout, img, basename, max_pix_val);
        }        

        //just output ascii
        else if (strcmp(argv[2], "--ascii") == 0)
        {
            
            outputP3(fout, img, basename, max_pix_val);
        }

        //just output image as itself in binary
        else
        {
            
            outputP6(fout, img, basename, max_pix_val);
        }
    }

        
    //freeing up the memory
    free2D(img.redGray, img.rows);
    free2D(img.green, img.rows);
    free2D(img.blue, img.rows);

    //clear files and close
    fin.clear();
    fin.close();
    
    fout.clear();
    fout.close();

    return 0;
}
