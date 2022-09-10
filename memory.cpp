/** *********************************************************************
 * @file
 *
 * @brief   Handles dynamic memory allocation for the program. 
 ***********************************************************************/

#include "netPBM.h"


 /** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * Takes a pointer to a pointer of datatype pixel, passed by reference, and the integer values of rows and columns as input. 
  * The function then creates a 1D array of pointers. It then checks whether the memory for this pointer has been 
  * allocated. Returns nullptr if not. The function then allocates another 1D array for each row of the previous 1D array of 
  * pointers that were created. A 2D array of rows x cols is created this way. If the allocation fails at any point 
  * while iterating through the loop an allocating memory, the free2D function is called which frees up the memory that was 
  * previously allocated. Following which the function returns nullptr. If all the memory allocations were successfull, 
  * the function returns the 2D array ptr of datatype pixel. 
  *
  * @param[in] rows - the number of rows.
  * @param[in] cols - the number of columns.
  *
  * @returns 2D dynamically allocated array of pixel datatype
  *
  * @par Example:
    @verbatim
    int rows = 3;
    int cols = 2;

    pixel **ptr = nullptr;

    ptr = alloc2D(rows, cols);

    //ptr is now a 2D array of 3 x 2
    
    @endverbatim

  ***********************************************************************/


pixel** alloc2D(int rows, int cols)
{
    int i;

    pixel** ptr = nullptr;
    ptr = new (nothrow) pixel * [rows];

    if (ptr == nullptr)
    {
        return nullptr;
    }

    for (i = 0; i < rows; i++)
    {
        ptr[i] = new (nothrow) pixel[cols];

        if (ptr == nullptr)
        {
            free2D(ptr, i);
            return nullptr;
        }
    }

    return ptr;

}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * Takes a pointer to a pointer of type pixel, and the integer value of the number of rows as input.
  * The function then verifies if the pointer points to any memory and returns if it does not. 
  * If the pointer does contain memory, it proceeds to iterate through every row and free up the memory that 
  * has been allocated using a for loop. At every iteration of the loop, it deletes the pointer that was created.
  * Finally, it deletes the entire pointer to the pointer.
  *
  * @param[in,out] ptr - the pointer to a pointer.
  * @param[in] rows - the number of rows.
  * 
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    int rows = 3;
    int cols = 2;

    pixel **ptr = nullptr;

    alloc2D(ptr, rows, cols);

    //ptr is now a 2D array of 3 x 2

    free2D(ptr, rows);

    //free2D frees up the memory that has been allocated to the array.

    @endverbatim

  ***********************************************************************/
void free2D(pixel **& ptr, int rows)
{
    int i = 0;
    if (ptr == nullptr)
    {
        return;
    }
        

    for (i = 0; i < rows; i++)
    {
        delete [] ptr[i];
    }
    
    delete [] ptr;

    
}


/** *********************************************************************
  * @author Jonathan Mascarenhas
  *
  * @par Description:
  * Takes two pointers of type pixel, and the integer values of the number of rows and columns as input.
  * The first pointer is passed by reference to the function while the second one is not. 
  * The pointers point to a 2D dynamically allocated arrays of the same dimensions. The loops iterate through 
  * each element of the 2D array and copy the data from the second 2D array ptr2 into the first 2D array ptr1. 
  *
  * @param[in,out] ptr1 - pointer to a pointer to be copied into.
  * @param[in] ptr2 - pointer to a pointer to copy from.
  * @param[in] rows - the number of rows.
  * @param[in] cols - the number of columns.
  *
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    int i,j;
    int rows = 3;
    int cols = 2;

    pixel **ptr1 = nullptr;
    pixel **ptr2 = nullptr;

    //allocating a 2D array for ptr1 and ptr2
    ptr1 = alloc2D(rows, cols);
    ptr2 = alloc2D(rows, cols);

    //generate data for ptr1
    for(i = 0; i<rows; i++)
    {
        for(j = 0; j<cols; j++)
        {
            ptr1[i][j] = 1;
        }
     }

    //copy data from ptr1 into ptr2
    copy2D(ptr2, ptr1, rows, cols);

    //ptr is now a 2D array of 3 x 2 with 1's 


    @endverbatim

  ***********************************************************************/
void copy2D(pixel**& ptr1, pixel**ptr2, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            ptr1[i][j] = ptr2[i][j];
        }
    }
}