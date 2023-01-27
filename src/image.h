#ifndef _IMAGE_H
#define _IMAGE_H

#include <string>
#include "macro.h"

struct Image {
    using dataType = unsigned char;
    dataType *data;
    constexpr int channel() const { return 3; }
    int width, height;

    Image(int w, int h);
    ~Image();

    void fill(colorf const& color);
    void setPixel(int x, int y, colorf const& color, bool flip = true);
    
    /**
     * Rasterize a line using Bresenham algorithm.
     * - Input coordinates are in image space. 
     */
    void drawLine(int2 const& v0, int2 const& v1, colorf const& color);
};

#endif
