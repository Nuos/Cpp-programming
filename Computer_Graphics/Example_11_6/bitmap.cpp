/*
 * Windows BMP file reader
 *
 * Written by Michael Sweet.
 *
 * Modification by Mike Chantler:
 * Old '... LoadDIBitmap(const...' function header replaced by new loadBMP header without const
 */


#include "stdafx.h"
#include "bitmap.h"

void *loadBMP(char *filename,    BITMAPINFO **info)    {
  //BITMAPINFO **info;
  FILE             *fp;            /* Open file pointer */
  void             *bits;          /* Bitmap pixel bits */
  long             bitsize,        /* Size of bitmap */
                   infosize;       /* Size of header information */
  BITMAPFILEHEADER header;         /* File header */

 /*
  * Try opening the file; use "rb" mode to read this *binary* file.
  */

  if ((fp = fopen(filename, "rb")) == NULL)
    return (NULL);

 /*
  * Read the file header and any following bitmap information�
  */

  if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
  {
   /*
    * Couldn't read the file header - return NULL�
    */

    fclose(fp);
    return (NULL);
  };

  if (header.bfType != 'MB') /* Check for BM reversed� */
  {
   /*
    * Not a bitmap file - return NULL�
    */

    fclose(fp);
    return (NULL);
  };
  infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
  if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
  {
   /*
    * Couldn't allocate memory for bitmap info - return NULL�
    */

    fclose(fp);
    return (NULL);
  };

  if (fread(*info, 1, infosize, fp) < infosize)
  {
   /*
    * Couldn't read the bitmap header - return NULL�
    */

    free(*info);
    fclose(fp);
    return (NULL);
  };

 /*
  * Now that we have all the header info read in, allocate memory for the
  * bitmap and read *it* in�
  */

  if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
    bitsize = ((*info)->bmiHeader.biWidth *
               (*info)->bmiHeader.biBitCount + 7) / 8 *
        abs((*info)->bmiHeader.biHeight);

  if ((bits = malloc(bitsize)) == NULL)
  {
   /*
    * Couldn't allocate memory - return NULL!
    */

    free(*info);
    fclose(fp);
    return (NULL);
  };

  if (fread(bits, 1, bitsize, fp) < bitsize)
  {
   /*
    * Couldn't read bitmap - free memory and return NULL!
    */

    free(*info);
    free(bits);
    fclose(fp);
    return (NULL);
  };

 /*
  * OK, everything went fine - return the allocated bitmap�
  */

  fclose(fp);
  return (bits);
}

//Writing the .BMP File
//
//As they say in the car repair manuals, �Installation is the reverse of removal.� To write a .BMP file, you simply add a BITMAPFILEHEADER structure to the bitmap in memory and write it to disk. Listing 11-10 is the SaveDIBitmap function.
//
//Listing 11-10 SaveDIBitmap function

int
SaveDIBitmap(char       *filename, /* I - File to save to */
             BITMAPINFO *info,     /* I - Bitmap information */
             void       *bits)     /* I - Bitmap pixel bits */
{
  FILE             *fp;            /* Open file pointer */
  long             size,           /* Size of file */
                   infosize,       /* Size of bitmap info */
                   bitsize;        /* Size of bitmap pixels */
  BITMAPFILEHEADER header;         /* File header */

 /*
  * Try opening the file; use "wb" mode to write this *binary* file.
  */

  if ((fp = fopen(filename, "wb")) == NULL)
    return (-1);

  if (info->bmiHeader.biSizeImage == 0)/* Figure out the bitmap size */
    bitsize = (info->bmiHeader.biWidth *
               info->bmiHeader.biBitCount + 7) / 8 *
      abs(info->bmiHeader.biHeight);
  else
    bitsize = info->bmiHeader.biSizeImage;

  infosize = sizeof(BITMAPINFOHEADER);
  switch (info->bmiHeader.biCompression)
  {
    case BI_BITFIELDS :
        infosize += 12; /* Add 3 RGB doubleword masks */
        if (info->bmiHeader.biClrUsed == 0)
          break;
    case BI_RGB :
        if (info->bmiHeader.biBitCount > 8 &&
            info->bmiHeader.biClrUsed == 0)
          break;
    case BI_RLE8 :
    case BI_RLE4 :
        if (info->bmiHeader.biClrUsed == 0)
          infosize += (1 << info->bmiHeader.biBitCount) * 4;
        else
          infosize += info->bmiHeader.biClrUsed * 4;
        break;
  };

  size = sizeof(BITMAPFILEHEADER) + infosize + bitsize;

 /*
  * Write the file header, bitmap information, and bitmap pixel data�
  */

  header.bfType      = 'MB'; /* Non-portable� sigh */
  header.bfSize      = size;
  header.bfReserved1 = 0;
  header.bfReserved2 = 0;
  header.bfOffBits   = sizeof(BITMAPFILEHEADER) + infosize;
  if (fwrite(&header, 1, sizeof(BITMAPFILEHEADER), fp) <
          sizeof(BITMAPFILEHEADER))
  {
   /*
    * Couldn't write the file header - return�
    */

    fclose(fp);
    return (-1);
  };

  if (fwrite(info, 1, infosize, fp) < infosize)
  {
   /*
    * Couldn't write the bitmap header - return�
    */

    fclose(fp);
    return (-1);
  };

  if (fwrite(bits, 1, bitsize, fp) < bitsize)
  {
   /*
    * Couldn't write the bitmap - return�
    */

    fclose(fp);
    return (-1);
  };

 /*
  * OK, everything went fine - return�
  */

  fclose(fp);
  return (0);
}


//============== END OF BIT MAP LOADER CODE ============================ END OF BIT MAP LOADER CODE ====================================
