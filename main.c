
/****************************************************************************************
 * Project Title   : MP3 Tag Reader
 * Author          : Rakesh Hangargi
 * Roll No         : 25021_240
 * Date            : 28/10/2025
 *
 * -------------------------------------------------------------------------------------
 * Project Description :
 * This project is designed to read and display metadata information from MP3 files,
 * commonly known as ID3 tags. The program extracts details such as the Title, Artist,
 * Album, Year, Genre, and Comments embedded within the MP3 file header.
 *
 * The MP3 Tag Reader provides a command-line interface that allows the user to:
 *   - View specific tag details of an MP3 file.
 *   - Edit tag information (optional, if implemented).
 *   - Verify the presence of ID3 tags in the given MP3 file.
 *
 * The project helps in understanding:
 *   - File handling and binary data manipulation in C.
 *   - Working with ID3 tag structures and offsets.
 *   - Use of string manipulation and buffer handling.
 *
 * -------------------------------------------------------------------------------------
 * Note :
 * Ensure the input MP3 file contains ID3v2 tags for proper extraction of metadata.
 *
 ***************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "conversion.h"
#include "edit.h"
#include "view.h"

void validate(int argc,char** argv,int* flag);


int main(int argc,char* argv[])
{
     int flag=0;   //Using flag variable to check the status of the program for execution


    validate(argc,argv,&flag); // Validation part to check command line arguments based on syntax

    if(flag==0)
        return 0;
    else if(flag==1) //Setting flag=1 if the commands for view are passed in correct way
        view(argv[2]);
    else if(flag==2) // Setting flag=2 if the command for edit are passed i correct way
    {
        edit(argv[2],argv[3],argv[4]);
        remove("sample.mp3");
        rename("temp.mp3","sample.mp3");
        printf("File edited successfully...\nTo view previous file check reserved.mp3 file\n\n");
    }
    else
        return 0;

        return 0;
}


   