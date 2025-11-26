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
 
 ***************************************************************************************/




#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 void validate(int argc,char** argv,int* flag)
 {
    if(argc==1)
    {
        printf("ERROR: Too few arguments\nPass any of these commands\n");
        printf("To view: ./a.out option filename\n");
        printf("To edit: ./a.out option tag_option New_Name file_name\n");
        printf("For help: ./a.out -help\n");
        exit(0);
    }
    else if(argc==2)
    {
        if(!(strcmp(*(argv+1),"-help")))
        {
            printf("\n-t\tModifies a Title tag");
            printf("\n-T\tModifies a Track tag");
            printf("\n-a\tModifies an Artist tag");
            printf("\n-A\tModifies an Album tag");
            printf("\n-y\tModifies a Year tag");
            printf("\n-c\tModifies a Comment tag");
            printf("\n-g\tModifies a Genre tag");
            printf("\n-h\tDisplays this help info");
            printf("\n-v\tPrints version info");
            exit(0);
        }
        else if(!(strcmp(*(argv+1),"-v")))
        {
            printf("ERROR: Enter the file name followed by -v to view to details\n");
            exit(0);
        }
        else if(!(strcmp(*(argv+1),"-e")))
        {
            printf("ERROR: To edit a mp3 file....Pass the following command:\n");
            printf("ex: ./a.exe -e -option new_name file.mp3\n");
            exit(0);
        }
        else
        {
            printf("\nERROR : Invalid commands being passed");
            exit(0);
        }
    }
    else if(argc==3)
    {
      if(!(strcmp(*(argv+1),"-v")))
        {
            if(strstr(*(argv+2),".mp3")==NULL)
            {
                printf("\n ERROR : Only .mp3 extensions allowed to view\n");
                exit(0);
            }
            else
            {
                *flag=1;

                return;
            }
        }
        else
        {
                printf("Pass the arguments in valid format\n");
                printf("To view: ./a.out option filename\n");
                printf("To edit: ./a.out option tag_option New_Name file_name\n");
                printf("For help: ./a.out -help\n");
                exit(0);
        }
    }
    else if(argc==4)
    {
        printf("ERROR : Invalid number of arguments passed\n");
        printf("\nTo view: pass 3 arguments => (ex:./a.exe -v file.mp3) \n");
        printf("To edit pass 5 arguments => (ex: ./a.exe -e -type new_name file.mp3)\n");
        printf("To get the help pass => ./a.exe -help\n");
        exit(0);
    }
    else if(argc==5)
    {
        if(strcmp(*(argv+1),"-e")!=0)
        {
            printf("\nERROR: -e command is required to edit the file\n");
            exit(0);
        }
        else
        {
            if(!(strcmp(*(argv+2),"-t")) || !(strcmp(*(argv+2),"-T")) || !(strcmp(*(argv+2),"-a")) || 
               !(strcmp(*(argv+2),"-A")) || !(strcmp(*(argv+2),"-y")) || !(strcmp(*(argv+2),"-c")) )
               {

                    *flag=2;
               }
               else
               {
                    printf("To edit : Pass valid command to edit the mp3 file\n");
                    printf("To get the help pass => ./a.exe -help\n");
               }
        }

    }
    else
    {
        if(argc>=6)
        {
            printf("ERROR: Too many arguments passed\n");
            printf("To view : Pass 3 arguments\n");
            printf("To edit : Pass 5 arguments\n");
        }
        else
        {
            printf("ERROR: Few arguments passed\n");
            printf("To view : Pass 3 arguments\n");
            printf("To edit : Pass 5 arguments\n");

        }
    }

}
