#pragma once
#ifndef		__TEXTURES_H_
#define		__TEXTURES_H_

///////////////////              BMP               //////////////////
// magic number "BM"
#define			BITMAP_ID			('B' + ('M'<<8))
// header byte type for RLE
#define			RLE_COMMAND			0
#define			RLE_ENDOFLINE		0
#define			RLE_ENDOFBITMAP		1
#define			RLE_DELTA			2

#define			BI_OS2				-1

int LoadFileBMP(char *filename, unsigned char **pixels, int *width, int *height, bool flipvert);
///////////////////              PCX               //////////////////
#pragma warning( disable : 4103 ) // used #pragma pack to change alignment
// --------------------------------------------
// PCXHEADER - pcx header structure.
// --------------------------------------------
#pragma pack(1)
typedef struct tagPCXHEADER
{
	unsigned char	manufacturer;		// manufacturer
	unsigned char	version;			// version
	unsigned char	encoding;			// encoding type
	unsigned char	bitsPerPixel;		// number of bits per pixel

	unsigned short	x, y;				// ...
	unsigned short	width, height;		// dimensions
	unsigned short	horzRes, vertRes;	// horisontal and vertical screen resolutions

	unsigned char	*palette;			// color palette
	unsigned char	reserved;			// reserved
	unsigned char	numColorPlanes;		// number of planes

	unsigned short	bytesPerScanLine;	// byte per line
	unsigned short	paletteType;		// palette type
	unsigned short	horzSize, vertSize;	// ...

	unsigned char	padding[54];		// ...

} PCXHEADER, *PPCXHEADER;

#pragma pack(4)
int LoadFilePCX( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert );
///////////////////              TGA              //////////////////
#pragma warning( disable : 4103 ) // used #pragma pack to change alignment
// --------------------------------------------
// TGAHEADER - targa header.
// --------------------------------------------
#pragma pack(1)
typedef struct tagTGAHEADER
{
	unsigned char	id_lenght;			// size of the structure
	unsigned char	color_map_type;		// must be equal to 0
	unsigned char	image_type;			// image compression type

	short int		cm_first_entry;		// colormap_origin (toujours 0)
	short int		cm_length;			// colormap_length (toujours 0)
	unsigned char	cm_size;			// colormap_size (toujours 0)

	short int		is_xorigin;			// lower left X coordinate (always 0)
	short int		is_yorigin;			// lower left Y coordinate (always 0)

	short int		is_width;			// image width (in pixels)
	short int		is_height;			// image height (in pixels)

	unsigned char	is_pixel_depth;		// number of bits per pixel: 16, 24, 32
	unsigned char	is_image_descriptor;// 24 bits = 0x00; 32 bits = 0x80
} TGAHEADER, *PTGAHEADER;
#pragma pack(4)
// --------------------------------------------
// BGRAQUAD - 32 bits pixel
// --------------------------------------------
typedef struct tagBGRAQUAD			// rgbt
{
	unsigned char	bgraBlue;		// blue
	unsigned char	bgraGreen;		// green
	unsigned char	bgraRed;		// red
	unsigned char	bgraAlpha;		// alpha

} BGRAQUAD, *PBGRAQUAD;
int LoadFileTGA( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert );
/////////////////////////////////////////////////////////////////////
unsigned int LoadTexture(char *filename);

#endif //__TEXTURES_H_