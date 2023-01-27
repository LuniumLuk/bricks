#include "image.h"
#include <memory>
#include <cstring>

Image::Image(int w, int h)
    : width(w)
    , height(h) {
    int size = w * h * channel();
    data = new dataType[size];
    memset(data, 0, size * sizeof(dataType));
}
Image::~Image() {
    delete data;
}

void Image::fill(colorf const& color) {
    int size = width * height;
    for (int i = 0; i < size; ++i) {
        int offset = i * channel();
        data[offset + 0] = clamp(color.r, 0.0f, 1.0f) * 255;
        data[offset + 1] = clamp(color.g, 0.0f, 1.0f) * 255;
        data[offset + 2] = clamp(color.b, 0.0f, 1.0f) * 255;
    }
}

void Image::setPixel(int x, int y, colorf const& color, bool flip) {
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;
    int offset;
    if (flip) {
        offset = (x + (height - 1 - y) * width) * channel();
    }
    else {
        offset = (x + y * width) * channel();
    }
    data[offset + 0] = clamp(color.r, 0.0f, 1.0f) * 255;
    data[offset + 1] = clamp(color.g, 0.0f, 1.0f) * 255;
    data[offset + 2] = clamp(color.b, 0.0f, 1.0f) * 255;
}

void Image::drawLine(int2 const& v0, int2 const& v1, colorf const& color) {

    auto x0 = clamp(v0.x, 0, width - 1);
    auto x1 = clamp(v1.x, 0, width - 1);
    auto y0 = clamp(v0.y, 0, height - 1);
    auto y1 = clamp(v1.y, 0, height - 1);

    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy; 
    int e2;

    while (true) {
        setPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1) break;

        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}
