#include "drawings_utils.h"
#include <stdio.h>
#include <stdlib.h>


// Callback de dessin du canevas
static int action_redraw_cb(Ihandle* canvas)
{
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "_CD_CANVAS");

    // Création paresseuse du canvas CD lors du premier affichage
    if (!cd_canvas)
    {
        cd_canvas = cdCreateCanvas(CD_IUP, canvas);
        if (!cd_canvas)
        {
            fprintf(stderr, "Erreur : Impossible de créer le canvas CD.\n");
            return IUP_DEFAULT;
        }
        IupSetAttribute(canvas, "_CD_CANVAS", (char*)cd_canvas);
    }

    // Rendu CD
    cdCanvasActivate(cd_canvas);
    cdCanvasClear(cd_canvas);

    cdCanvasForeground(cd_canvas, CD_BLUE);
    cdCanvasLine(cd_canvas, 10, 10, 150, 150);

    cdCanvasForeground(cd_canvas, CD_RED);
    cdCanvasRect(cd_canvas, 50, 50, 120, 120);

    cdCanvasForeground(cd_canvas, CD_GREEN);
    cdCanvasSector(cd_canvas, 200, 100, 60, 60, 0, 360);

    cdCanvasForeground(cd_canvas, CD_BLACK);
    cdCanvasText(cd_canvas, 10, 180, "Dessin C dans IupVbox");

    return IUP_DEFAULT;
}

// Callback de destruction pour libérer la mémoire du canvas CD
static int unmap_cb(Ihandle* canvas)
{
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "_CD_CANVAS");
    if (cd_canvas)
    {
        cdKillCanvas(cd_canvas);
        IupSetAttribute(canvas, "_CD_CANVAS", NULL);
    }
    return IUP_DEFAULT;
}

int my_canvas_box_init_env(int* argc, char*** argv)
{
    // Force le backend X11 sous Linux avant l'initialisation de GTK/IUP
    #if defined(__linux__) || defined(__unix__)
    //setenv("GDK_BACKEND", "x11", 1);
    #endif

    return IupOpen(argc, argv);
}

Ihandle* my_canvas_box_create(void)
{
    // 1. Création du Canvas IUP
    Ihandle* canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "RASTERSIZE", "300x200");
    IupSetAttribute(canvas, "EXPAND", "YES");

    // 2. Association des Callbacks
    IupSetCallback(canvas, "ACTION", (Icallback)action_redraw_cb);
    IupSetCallback(canvas, "UNMAP_CB", (Icallback)unmap_cb);

    // 3. Encapsulation dans une IupVbox
    Ihandle* vbox = IupVbox(canvas, NULL);

    return vbox;
}
