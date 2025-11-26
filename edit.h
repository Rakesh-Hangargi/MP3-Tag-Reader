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



int my_strcmp(char* one, char* two) //Created my own strcmp function to handle null cases
{
    int end = 3;
    int start = 0;

    while (start <= end)
    {
        if (one[start] != two[start])
            return 1;
        start++;
    }
    return 0;
}

void edit(char* tag, char* name, char* arg)
{
    //Mapping each command to their respective tags
    char array[][5] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    char index[][3] = {"-t","-a","-A","-y","-c","-g"};

    int i=0;
    while (i<6)
    {
        if (!(strcmp(tag,index[i]))) //Tracking the index required to map from command to its respective tag
            break;
        i++;
    }

    if(i==6)
    {
        printf("ERROR : Invalid command/tag passed\n");
        exit(0);
    }

    int length = strlen(name);

    //Opening the source file in read mode, destination file in write mode
    FILE* tp = fopen("temp.mp3","wb");
    FILE* mp = fopen(arg,"rb");

    if (tp == NULL)
    {
        printf("ERROR : No file exists\n");
        exit(0);
    }
    if (mp == NULL)
    {
        printf("Error opening %s\n", arg);
        return;
    }

    FILE* dummy = fopen("reserved.mp3","wb");

    //Before modifying the main mp3 file storing its content into reserved mp3 file
    char tempchar;
    while((tempchar=fgetc(mp))!=EOF)
    {
        fputc(tempchar,dummy);
    }

    rewind(mp);

    //Copying this header of mp3 first
    char header[10];
    fread(header,1,10,mp);
    fwrite(header,1,10,tp);

    fseek(mp,10,SEEK_SET);
    fseek(tp,10,SEEK_SET);

    while (1)
    {
        //Iteratively checking and copying each tag and data into temp.mp3 until intended tag to edit is found

        char frameHeader[5];
        unsigned char sizeBytes[4];
        unsigned char flags[2];

    
        if (fread(frameHeader,1,4,mp) != 4)
            break;
        frameHeader[4] = '\0';

        if (fread(sizeBytes, 1,4,mp) != 4)
            break;

        int oldsize = (sizeBytes[0]<<24) | (sizeBytes[1]<<16) | (sizeBytes[2]<<8) | sizeBytes[3];

        if (fread(flags, 1, 2, mp) != 2)
            break;

        if (oldsize <= 0)
            break;

        char* old_content = (char*)malloc(oldsize);
        if (fread(old_content, 1, oldsize, mp) != oldsize)
        {
            free(old_content);
            break;
        }

        if (my_strcmp(frameHeader, array[i]) == 0)//Editing the desired tag
        {
             printf("Editing frame: %s\n", frameHeader);
             fwrite(frameHeader, 1, 4, tp);

            int new_size = length + 1;
             unsigned char newSizeBytes[4];
             newSizeBytes[0]=(new_size>>24) & 0xFF;
             newSizeBytes[1]=(new_size>>16) & 0xFF;
             newSizeBytes[2]=(new_size>>8) & 0xFF;
             newSizeBytes[3]=new_size&0xFF;
            fwrite(newSizeBytes,1,4,tp);

            fwrite(flags,1,2,tp);


            fwrite(old_content,1,1,tp);

  
            fwrite(name,1,length,tp);
        }
        else
        {
            fwrite(frameHeader,1,4,tp);

            unsigned char tmpSizeBytes[4];
            tmpSizeBytes[0]=(oldsize>>24)&0xFF;
            tmpSizeBytes[1]=(oldsize>>16)&0xFF;
            tmpSizeBytes[2]=(oldsize>>8)&0xFF;
            tmpSizeBytes[3]=oldsize&0xFF;
            fwrite(tmpSizeBytes,1,4,tp);

            fwrite(flags,1,2,tp);
            fwrite(old_content,1,oldsize,tp);
        }

        free(old_content);
    }

    //Copying the left out content after successfully modifying the tag
    char buf[1024];
    size_t n;
    while ((n=fread(buf,1,sizeof(buf),mp))>0)
        fwrite(buf,1,n,tp);

    fclose(mp);
    fclose(tp);
}


