

#ifndef DRAWINGS_C_H
#define DRAWINGS_C_H

typedef struct {
    int x;
    int y;
} Point;

/**
 * @todo write docs
 */
void point_at(int x, int y, long int colour, int width);
void redraw();
void newvec(long int colour, int width);
void redraw_plus();

void line_at_remember_last_point(int x, int y, long int colour, int width);

#endif // DRAWINGS_C_H

