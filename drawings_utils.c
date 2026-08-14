#include "drawings_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "drawings_c.h"

Ihandle* canvas;
cdCanvas* cd_canvas;
long int cv_color; //short for canvas colour

void set_colour_canvas (long int col) {
        cv_color = col;
        cdCanvasForeground(cd_canvas, col);
}

void pointat(int x, int y) {
    int height;
    cdCanvasGetSize(cd_canvas, NULL, &height, NULL, NULL);
    cdCanvasSetForeground(cd_canvas, cv_color);
    cdCanvasMarkSize(cd_canvas, 10); /* Dot diameter in pixels */
    cdCanvasMarkType(cd_canvas, CD_CIRCLE); /* Solid dot style */

    int new_y = height - y - 1;
    cdCanvasMark(cd_canvas, x, new_y);
}

int motion_cb(Ihandle* ih, int x, int y, char* status) {
    int first_point = 1;

    if (iup_isbutton1(status)) {
        if (first_point == 1) {
            /*cdCanvasSetForeground(cd_canvas, cv_color);
            cdCanvasMarkSize(cd_canvas, 10); /* Dot diameter in pixels */
            /*cdCanvasMarkType(cd_canvas, CD_CIRCLE); /* Solid dot style */

            /*cdCanvasMark(cd_canvas, x, y);*/


            point_at(x, y);
        } else {
            //nothing for now
        }
        first_point = 0;
    } else {
        first_point = 1;
    }

    return IUP_DEFAULT;
}

void do_a_mark(int x, int y) {

}

int update_canvas() {
    IupUpdate(canvas);
    return IUP_DEFAULT;
}

void change_colour_iup_canvas(long int clr) {
    cv_color = clr;
}

static int action_redraw_cb(Ihandle* canvas)
{
    cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "_CD_CANVAS");

    if (cd_canvas == NULL)
    {
        // 1. Vérification cruciale : est-ce que le canvas IUP est bien mappé à l'écran ?
        if (!IupGetAttribute(canvas, "XWINDOW") && !IupGetAttribute(canvas, "HWND"))
        {
            // La fenêtre X11 native n'existe pas encore !
            // On sort sans créer CD, IUP relancera ACTION une fois affiché.
            return IUP_DEFAULT;
        }

        // 2. Création du canvas CD
        cd_canvas = cdCreateCanvas(CD_IUP, canvas);

        if (!cd_canvas)
        {
            // On tente le fallback avec le double buffer
            cd_canvas = cdCreateCanvas(CD_IUPDBUFFER, canvas);
        }

        if (!cd_canvas)
        {
            fprintf(stderr, "Erreur critique : cdCreateCanvas a renvoyé NULL.\n");
            return IUP_DEFAULT;
        }

        // Sauvegarde du pointeur dans les attributs IUP
        IupSetAttribute(canvas, "_CD_CANVAS", (char*)cd_canvas);
    }

    // Suite du dessin...
    cdCanvasActivate(cd_canvas);
    cdCanvasClear(cd_canvas);
    cdCanvasForeground(cd_canvas, cv_color);
    cdCanvasLine(cd_canvas, 10, 10, 150, 150);

    // Si tu utilises CD_IUPDBUFFER, il faut quémander le swap à la fin :
    // cdCanvasFlush(cd_canvas);

    return IUP_DEFAULT;
}

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


Ihandle* canvas_box_create(void)
{
    cv_color = CD_BLUE;
    canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "RASTERSIZE", "300x200");
    IupSetAttribute(canvas, "EXPAND", "YES");

    IupSetCallback(canvas, "ACTION", (Icallback)action_redraw_cb);
    IupSetCallback(canvas, "UNMAP_CB", (Icallback)unmap_cb);
    IupSetCallback(canvas, "MOTION_CB", (Icallback)motion_cb);

    // Ne pas oublier le NULL final pour IupVbox
    Ihandle* vbox = IupVbox(canvas, NULL);

    return vbox;
}

