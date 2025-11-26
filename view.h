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

void evaluate(FILE* fp,char* tag,char* content)
{
    //This function was created to make sure reading the tags and data is done effectively per tag

     char title[5];
    fread(title,sizeof(title)-1,1,fp);
    title[4]='\0';

          if((strcmp(title,tag))!=0)
    {
        printf("ERROR : Unsupported Tag\n");
        exit(0);
    }


     int size;
    fread(&size,sizeof(int),1,fp);

    //Converting the Big Endian data received from mp3 file to Little Endian data
    convert(&size);;

     fseek(fp,3,SEEK_CUR);

    fread(content,size-1,1,fp);
    content[size-1]='\0';


}

void view(char* argv)
{
    FILE* fp = fopen(argv,"r");
    if(fp==NULL)
    {
        printf("ERROR : No file exists\n");
        exit(0);
    }

    //Supporting tags for the project are being stored in array of strings
    char tag[6][5]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};



    char buffer[4];
    fread(buffer,sizeof(buffer)-1,1,fp);
    buffer[3]='\0';
   
    if((strcmp(buffer,"ID3"))!=0)
    {
        printf("Unsupported file\nInclude file with .mp3 extension\n");
        exit(0);
    }
    rewind(fp);
    fseek(fp,10,SEEK_CUR);


    
    char data[6][100];//This stores the entire data to be displayed on screen 

    for(int i=0;i<6;i++)
     {
        evaluate(fp,tag[i],data[i]);//Checking and storing data into data[6][100] array
     }

printf("\n--------------------------------------------------------------------\n");
printf("\t\tMP3 Tag Reader and Editor for ID3v2\n");
printf("--------------------------------------------------------------------\n");

printf("%-15s : %s\n", "Title", data[0]);
printf("%-15s : %s\n", "Artist Name", data[1]);
printf("%-15s : %s\n", "Album", data[2]);
printf("%-15s : %s\n", "Year", data[3]);
printf("%-15s : %s\n", "Composer", data[4]);
printf("%-15s : %s\n", "Comment", data[5]);

printf("--------------------------------------------------------------------\n");


    fclose(fp);

}

