// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // read scale
    int scale = (int)atoi(argv[1]);

    // ensure correct scale input
    if (scale < 1 || scale > 100)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // determine old padding for scanlines
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Mark file pointer
    int current_pos = (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

    // store old height & width
    int o_biWidth = bi.biWidth;
    int o_biHeight = abs(bi.biHeight);

    // resize bi.biWidth
    bi.biWidth = bi.biWidth * scale;

    // resize bi.biHeight
    bi.biHeight = bi.biHeight * scale;

    // determine new padding for scanlines
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // resize bi.biSizeImage (info header) - number of bytes required for sructure (all bar header files)
    bi.biSizeImage = ((bi.biWidth * 3) * abs(bi.biHeight)) + (new_padding * abs(bi.biHeight));

    // resize bf.bfsize (file header) - total size of file in bytes
    bf.bfSize = bi.biSizeImage + (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    int n = 0;

    // iterate over infile's scanlines
    for (int i = 0; i < o_biHeight; i++)
    {
        // repeat rows
        for (int j = 0; j < scale; j++)
        {
            // back to beginning of row
            fseek(inptr, current_pos + n, SEEK_SET);

            // iterate over pixels in scanline
            for (int k = 0; k < o_biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write n RGB triples to outfile
                for (int l = 0; l < scale; l++)
                {

                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Write padding
            for (int m = 0; m < new_padding; m++)
            {
                fputc(0x00, outptr);
            }

        }

        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        n = n + ((o_biWidth * 3) + old_padding);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
