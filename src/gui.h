#ifndef _GUI_H
#define _GUI_H

#include <string>
#include "macro.h"
#include "vector.h"
#include "platform.h"
#include "image.h"

colorf const __text_color   = { .9f, .9f, .9f };
colorf const __base_color   = { .3f, .3f, .3f };
colorf const __active_color = { .9f, .9f, .9f };
int const __tp = 1;

void fillRect(Image & image, int x, int y, int w, int h, colorf const& color);

void drawLineX(Image & image, int x, int y, int w, colorf const& color, int scale = 1);
void drawLineY(Image & image, int x, int y, int h, colorf const& color, int scale = 1);
void drawRect(Image & image, int x, int y, int w, int h, colorf const& color, int scale = 1);

void drawFont(Image & image, char c, int x, int y, colorf const& color, int scale = 1);
void drawText(Image & image, char const* text, int x, int y, colorf const& color, int scale = 1);

struct GUI {
    GUI(int _w, int _h, int _x, int _y, int _scale = 1, bool _flip = false)
        : width(_w)
        , height(_h)
        , x(_x)
        , scale(_scale)
        , flip(_flip) {
        y = _y - 13 * scale * (flip ? -1 : 1);
        oy = y;
    }

    void processMouseButtonEvent(LuGL::MOUSE_BUTTON button, bool pressed, float x, float y);
    void processMouseDragEvent(float x, float y);
    // Call after drawing every elements in each render loop.
    void tick();

    // GUI elements.
    void text(Image & image, char const* text);
    bool button(Image & image, char const* text);
    bool radioButton(Image & image, char const* text, bool active);
    void sliderFloat(Image & image, float * value, float min, float max, int length = 100);

    int width, height;
    int x, y, oy;
    int scale;
    bool flip;

private:
    float2 mouseLastPos;
    float2 mousePos;
    float2 mouseDelta;
    float2 mouseClick;
    bool  mouseButtonPressed = false;
    bool  mouseDragStart = false;
    bool  mouseClicked = false;
};

#endif
