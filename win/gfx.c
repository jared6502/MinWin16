#include "gfx.h"

void putpixel(int x, int y, pixel p, bitmap dst)
{
	if (dst.width > 0 && dst.height > 0 && dst.data != 0)
	{
		if (x >= 0 && x < dst.width && y >= 0 && y < dst.height)
		{
			dst.data[y][x] = p;
		}
	}
}

void line(int x1, int y1, int x2, int y2, pixel p, bitmap dst)
{
	int i;
	int j;
	
	int xa;
	int xb;
	int ya;
	int yb;
	
	int dx;
	int dy;
	int dydx;
	
	//put points in correct order
	if (x1 > x2)
	{
		xa = x1;
		xb = x2;
	}
	else
	{
		xa = x2;
		xb = x1;
	}
	
	if (y1 > y2)
	{
		ya = y1;
		yb = y2;
	}
	else
	{
		ya = y2;
		yb = y1;
	}
	
	//get distances
	dx = xa - xb;
	dy = ya - yb;
	dydx = dy / dx
	
	//draw line
	for (i = 0; i < dx; i++)
	{
		for (j = 0; j < dydx; j++)
		{
			putpixel(xa + i, ya + j, p, dst);
			ya += j;
		}
	}
}

void putbitmap(int x, int y, bitmap src, bitmap dst)
{
	if (src.width > 0 && src.height > 0 && src.data != 0)
	{
		int i;
		int j;
		
		for (i = 0; i < src.height; i++)
		{
			for (j = 0; j < src.width; j++)
			{
				putpixel(x + j, y + i, data[j][i], dst);
			}
		}
	}
}