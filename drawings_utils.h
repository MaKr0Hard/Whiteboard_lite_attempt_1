#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H
#include <iup.h>
#include <cd.h>
#include <cdiup.h>
typedef struct {
    int R;
    int G;
    int B;
} Colour;

/**
 * Crée et retourne une IupVbox contenant le Canvas CD.
 * Le composant retourné peut être directement passé à IupAppend().
 */
//int action_redraw_cb_plus();
int update_canvas();
void change_colour_iup_canvas(long int clr);
void do_a_mark(int x, int y);
Ihandle* canvas_box_create(void);
void pointat(int x, int y);
void set_colour_canvas (long int col);
void lineat(int x1, int y1, int x2, int y2);
void set_width_stroke (int width);
void set_canvas_colour(long int clr);

#endif
