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
Ihandle* canvas_box_create(void);


#endif
