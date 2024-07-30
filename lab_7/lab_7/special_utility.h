#ifndef SPECIAL_UTILITY_H
#define SPECIAL_UTILITY_H

enum Mode
{
    DRAW_FIGURE = 1,
    DRAW_RECT
};

struct Segment
{
    int x0;
    int y0;
    int x1;
    int y1;
};

struct Cutter
{
    int x0;
    int y0;
    int x1;
    int y1;
};

#endif // SPECIAL_UTILITY_H
