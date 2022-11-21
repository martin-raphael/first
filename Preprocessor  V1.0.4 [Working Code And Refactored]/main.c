#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* substring(char*, int, int);

int main(int argc, char *argv[])
{
    char fileName[20];
    char fileName2[20];
    char noblanksfile[20]="noblanks.c";
    char nocommentsfile[20]="nocomments.c";
    char finalout[20]="finalout.c";
    char line[256];

    printf("Ensure your file is next to the main.c file before typing it below... \n\n");
    printf("Kindly Enter The Name of the file (Add The Extension e.g  test.c ): \n");
    printf("_______________________________________________________________________\n");
    scanf("%s", &fileName);
    printf("\nThe Name of the file is %s and contains the following : \n",fileName);

    printFile(fileName);
    printf("\n...........\n");
    removeBlankLines(fileName);
    removeComments(noblanksfile);
    macroExpansion(nocommentsfile);

    printf("\n\n\n\nThank You For Your Patience :) \n Here's Your Clean File:\n_____________________________________________________________________\n");

    printFile(finalout);


    return 0;
}
void printFile(char fileName[20])
{

    FILE *fp;
    fp=fopen(fileName,"r");
    char line[256];
    while(fgets(line,sizeof(line),fp))
    {

        printf("%s",line);

    }
    fclose(fp);

}

void removeBlankLines(char fileName[20])
{


    FILE *file;
    FILE *outFile;
    char line[256];
    char outFileName[]="noblanks.c";


    //logic for removing blank lines
    file=fopen(fileName,"r");
    outFile=fopen(outFileName,"w");
    while(fgets(line,sizeof(line),file))
    {

        if(strlen(line)!=1)
        {

            fputs(line,outFile);
        }
    }
    fclose(file);
    fclose(outFile);


}
void removeComments(char fileName[20])
{

    FILE *file;
    FILE *outFile;
    FILE *outFile2;
    char line[256];
    char outFileName[]="nocomments.c";
    char outFileName2[]="nocomments2.c";



    //logic for removing comments
    file=fopen(fileName,"r");
    outFile=fopen(outFileName,"w");
    outFile2=fopen(outFileName2,"w");
    while(fgets(line,sizeof(line),file))
    {

        if(!(((line[0]=='/')&&(line[1]=='/'))||(((line[0]=='/')&&(line[1]=='*'))||(line[0]=='*'))))
        {

            fputs(line,outFile);
            fputs(line,outFile2);
        }
    }

    fclose(file);
    fclose(outFile);
    fclose(outFile2);
}
void macroExpansion(char fileName[20])
{
    FILE *file;
    FILE *file2;

    char line[256];

    char *p;
    char *split;
    //logic for macro expanding
    file=fopen(fileName,"r");
    file2=fopen("nocomments2.c","r");

    //outFile=fopen(outFileName,"w");
    while(fgets(line,sizeof(line),file))
    {
        //split the line into variables

        if(line[0]=='#'&&line[1]=='d'&&line[2]=='e'&&line[3]=='f'&&line[4]=='i')
        {
            p = substring(line, strlen("#define "),strlen(line) );
            split= strtok(p," ");


            char splitted[2][256];
            int len=0;
            while (split != NULL)
            {

                if(split!=NULL&&len==0)
                {

                    strcpy(splitted[len],split);
                    len=1;


                }
                else
                {
                    strcpy(splitted[++len],split);

                }
                //printf ("%s\n",splitted[0]);
                split = strtok (NULL, " ");
            }

            char macroHead[256];
            strcpy (macroHead, splitted[0]);


            char macroBody[256];
            strcpy (macroBody, splitted[2]);
            //loop over the entire file replacing (expanding) to a new file
            iterateFile(file2,macroHead,macroBody,line);


        }


    }


    fclose(file);
    fclose(file2);

}
void iterateFile(FILE *file2,char macroHead[],char macroBody[],char line)
{
    FILE *outFile;
    FILE *isFileThere;
    char line2[256];
    char temporary[100];
    char *ch;
    char outFileName[]="out.c";
    //checking if files exist first to preserve the done changes
    if ((isFileThere= fopen("out.c", "r")))
    {
        fclose(isFileThere);
        outFile=fopen("finalout.c","w");
        file2=fopen(outFileName,"r");
        printf("******%s*****\n",macroBody);
        rewind(file2);
        while(fgets(line2,sizeof(line2),file2))
        {
            if(!(line2[0]=='#'&&line2[1]=='d'&&line2[2]=='e'&&line2[3]=='f'&&line2[4]=='i'))
            {
                strcpy(temporary,line2);


                for(int i = 0; i < strlen(line2)-1; i++)
                {
                    ch=temporary[i];

                    //printf("%i\n",i);

                    //printf("%s",line2);

                    //printf("%i :::It'll work just %c\n",i,ch);



                    if(ch==macroHead[0]&&temporary[i+1]==macroHead[1])
                    {

                        fputs(macroBody,outFile);
                    }
                    else if(ch==macroHead[1]&&temporary[i-1]==macroHead[0])
                    {
                        continue;
                    }
                    else
                    {
                        fputc(ch,outFile);
                    }


                }
                fputc('\n',outFile);


            }


        }

    }
    else
    {

        outFile=fopen(outFileName,"w");
        printf("******%s*****\n",macroBody);
        rewind(file2);
        while(fgets(line2,sizeof(line2),file2))
        {
            if(!(line2[0]=='#'&&line2[1]=='d'&&line2[2]=='e'&&line2[3]=='f'&&line2[4]=='i'))
            {
                strcpy(temporary,line2);

                //printf("Monitor The Lines______________:%c\n",temporary);
                for(int i = 0; i < strlen(line2)-1; i++)
                {
                    ch=temporary[i];

                    //printf("%i\n",i);

                    //printf("%s",line2);

                    //printf("%i :::It'll work just %c\n",i,ch);



                    if(ch==macroHead[0]&&temporary[i+1]==macroHead[1])
                    {

                        fputs(macroBody,outFile);
                    }
                    else if(ch==macroHead[1]&&temporary[i-1]==macroHead[0])
                    {
                        continue;
                    }
                    else
                    {
                        fputc(ch,outFile);
                    }


                }
                fputc('\n',outFile);


            }


        }
    }

    fclose(outFile);


}
char *substring(char *string, int position, int length)
{
    char *p;
    int c;

    p = malloc(length+1);

    if (p == NULL)
    {
        printf("Unable to allocate memory.\n");
        exit(1);
    }

    for (c = 0; c < length; c++)
    {
        *(p+c) = *(string+position-1);
        string++;
    }

    *(p+c) = '\0';

    return p;
}

