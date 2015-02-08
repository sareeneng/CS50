/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece by factor of f
 Input into program is ./resize f infile outfile
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember factor and filenames
    float f = atof(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if(f==0)
    {
        printf("Please enter a valid factor value.\n");
        return 5;
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inbf;
    fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inbi;
    fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 || 
        inbi.biBitCount != 24 || inbi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    
    //make copies of input file header and info header into the output file header and info header
    //then will modify values as appropriate
    BITMAPFILEHEADER outbf = inbf;
    BITMAPINFOHEADER outbi = inbi;
    
    //Things that need to change in outbf: bfSize only
    //Things that need to change in outbi: biWidth, biHeight, biSizeImage
    outbi.biWidth = inbi.biWidth*f;
    outbi.biHeight = inbi.biHeight*f;
        
    // determine padding of input file for scanlines
    int inPadding =  (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (outbi.biWidth*sizeof(RGBTRIPLE)) % 4) % 4;
    
    outbi.biSizeImage = (outbi.biWidth+outPadding)*-outbi.biHeight*3;
    outbf.bfSize = outbi.biSizeImage + outbf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

//Maybe what we can do is generate a scan line for each line that needs to be copied
// For example, suppose f = 3
// If we look at the top-left pixel, there will end up being 9 copies of that pixel
// Three in the top row, three in the second, and three in the third
// So we could do a for loop that iterates from 0-->f, generating a line
// and then write that line to the output file.

for(int i=0, inbiHeight = abs(inbi.biHeight);i<inbiHeight;i++)  //For each line in the infile
{
    //First let's generate an array of triples, equal to width of file, size = outbi.biWidth
    RGBTRIPLE tripleArray[outbi.biWidth];

    int counter=0;

    //First generate the line to be copied multiple times
    //Iterate over inBiWidth, and copy it into the line array f times
    for(int j=0; j<inbi.biWidth; j++)
    {
        RGBTRIPLE triple;
        fread(&triple, sizeof(RGBTRIPLE),1,inptr);
        for(int k=0; k<f; k++)
        {
            tripleArray[counter]=triple; //This generates f copies of the triple
            counter++;    
        }
    }
    
    for(int j=0; j<f; j++)
    {
        for(int k=0; k<outbi.biWidth; k++)
            fwrite(&tripleArray[k], sizeof(RGBTRIPLE), 1, outptr);  //Write a line
        for(int k=0; k<outPadding; k++)
            fputc(0x00 ,outptr);        //Write the padding
    }
    
    fseek(inptr, inPadding, SEEK_CUR);
}

/*    
    // iterate over infile's scanlines
    for (int i = 0, inbiHeight = abs(inbi.biHeight); i < inbiHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < inbi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < outPadding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
*/

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
