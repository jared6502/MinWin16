#ifndef __GFX_H__
#define __GFX_H__

typedef struct
{
	int r;
	int g;
	int b;
	int a;
} pixel;

typedef struct
{
	int width;
	int height;
	pixel *data
} bitmap;

#endif
