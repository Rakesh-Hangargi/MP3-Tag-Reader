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


void convert(int *num)
{
    unsigned char *ptr = (unsigned char*)num;
    unsigned char temp;

    temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;

    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}