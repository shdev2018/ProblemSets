#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for correct input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *raw = argv[1];

    // open raw file for reading & check for errors
    FILE *rawdata = fopen(raw, "r");
    if (rawdata == NULL)
    {
        fprintf(stderr, "Could not open\n");
        return 2;
    }

    // allocate space for jpeg files
    unsigned char *buffer = (unsigned char *)malloc(512);

    // Initializations
    char filename[8];
    int n = 0;
    FILE *jpg = NULL;

    // operate until EOF
    while (fread(buffer, 1, 512, rawdata) == 512)
    {

        // check first 4 bytes of buffer for jpeg header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (n > 0)
            {
                // close previous ouput file
                fclose(jpg);
            }

            // create outfile, name it, open it
            sprintf(filename, "%03i.jpg", n);

            jpg = fopen(filename, "w");

            n++;

        }

        if (n > 0)
        {
            // write buffer into outfile
            fwrite(buffer, 512, 1, jpg);
        }

    }

    // free malloc
    free(buffer);

    // close input file
    fclose(rawdata);

    // success
    return 0;


}


