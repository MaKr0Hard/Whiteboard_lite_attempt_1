#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H
#include <iup.h>
#include <cd.h>
#include <cdiup.h>

/**
 * Initialise l'environnement (force X11 sous Linux pour éviter les segfaults Wayland/GTK3).
 * À appeler au tout début du main avant IupOpen.
 */
int my_canvas_box_init_env(int* argc, char*** argv);

/**
 * Crée et retourne une IupVbox contenant le Canvas CD.
 * Le composant retourné peut être directement passé à IupAppend().
 */
Ihandle* my_canvas_box_create(void);

#endif
