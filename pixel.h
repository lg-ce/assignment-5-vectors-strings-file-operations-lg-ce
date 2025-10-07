#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>

struct _pixel
{
  float r;
  float g;
  float b;
  int x;
  int y;
};
typedef struct _pixel Pixel;

#endif

