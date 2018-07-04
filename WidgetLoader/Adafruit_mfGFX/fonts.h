/*
Multifont GFX library is adapted from Adafruit_GFX library by Paul Kourany
v1.0.0, May 2014 Initial Release
v1.0.1, June 2014 Font Compilation update
v1.0.2, Aug 2015 Added charWidth(char) function to return char width in pixels

Please read README.pdf for details
*/

//  fonts.h

#ifndef _fonts_h
#define _fonts_h

#include "Particle.h"

// Font selection descriptors - Add an entry for each new font and number sequentially
#define ARIAL_8 1
#define TEST 2
#define CALIBRI_48 3
#define CALIBRI_18 4
#define CALIBRI_24 5

#define FONT_START 0
#define FONT_END 1

struct FontDescriptor
{
	uint8_t width;	 // width in bits
	uint8_t height;	// char height in bits
	uint16_t offset; // offset of char into char array
};

// Font references - add pair of references for each new font
extern const uint8_t arial_8ptBitmaps[];
extern const FontDescriptor arial_8ptDescriptors[];

extern const uint8_t testBitmaps[];
extern const FontDescriptor testDescriptors[];

extern const uint8_t calibri_48ptBitmaps[];
extern const FontDescriptor calibri_48ptDescriptors[];

extern const uint8_t calibri_18ptBitmaps[];
extern const FontDescriptor calibri_18ptDescriptors[];

extern const unsigned char calibri_24ptBitmaps[];
extern const FontDescriptor calibri_24ptDescriptors[];

#endif