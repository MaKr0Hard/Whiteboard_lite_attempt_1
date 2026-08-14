#include "drawings_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "drawings_c.h"

Ihandle* canvas;
cdCanvas* cd_canvas;
long int cv_color = 0; //short for canvas colour
//long int cv_color = 0;
int test = 0;
int newvec_already_done = 0;
int first_point = 1;
int width_stroke = 0;

void change_colour_iup_canvas(long int clr) {
    cv_color = clr;
    cdCanvasSetForeground(cd_canvas, cv_color);
}

void set_canvas_colour(long int clr) {
    cv_color = clr;
    cdCanvasSetForeground(cd_canvas, cv_color);
}

void set_width_stroke (int width) {
    width_stroke = width;
}

void lineat(int x1, int y1, int x2, int y2, long int colour) {
    int height;
    cdCanvasSetForeground(cd_canvas, colour);
    cdCanvasLineWidth(cd_canvas, width_stroke);
    cdCanvasGetSize(cd_canvas, NULL, &height, NULL, NULL);
    cdCanvasLineJoin(cd_canvas, CD_CIRCLE);
    int new_y1 = height - y1 - 1;
    int new_y2 = height - y2 - 1;
    cdCanvasLine(cd_canvas, x1, new_y1, x2, new_y2);
}

void clear_the_cvas() {
    cdCanvasClear(cd_canvas);
}

int resize_cb(Ihandle *ih) {
    if (test != 0) {
        clear_the_cvas();
    }
return IUP_DEFAULT;
}

void pointat(int x, int y, long int colour) {
    int height;
    cdCanvasGetSize(cd_canvas, NULL, &height, NULL, NULL);
    cdCanvasSetForeground(cd_canvas, colour);
    cdCanvasMarkSize(cd_canvas, width_stroke); /* Dot diameter in pixels */
    cdCanvasMarkType(cd_canvas, CD_CIRCLE); /* Solid dot style */

    int new_y = height - y - 1;
    cdCanvasMark(cd_canvas, x, new_y);
}

int motion_cb(Ihandle* ih, int x, int y, char* status) {


    if (iup_isbutton1(status)) {
        if (first_point == 1) {
            /*cdCanvasSetForeground(cd_canvas, cv_color);
            cdCanvasMarkSize(cd_canvas, 10); /* Dot diameter in pixels */
            /*cdCanvasMarkType(cd_canvas, CD_CIRCLE); /* Solid dot style */

            /*cdCanvasMark(cd_canvas, x, y);*/

            newvec(cv_color);
            point_at(x, y, cv_color);
            first_point = 0;
        } else {
            //nothing for now
            point_at(x, y, cv_color);
            first_point = 0;
        }

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
    long int cv_colour2 = cv_color;
    // Suite du dessin...
    cdCanvasActivate(cd_canvas);
    if (test == 0) {
    cdCanvasClear(cd_canvas);
    cdCanvasForeground(cd_canvas, cv_color);
    test++;
    }

    //cdCanvasLine(cd_canvas, 10, 10, 150, 150);

    // Si tu utilises CD_IUPDBUFFER, il faut quémander le swap à la fin :
    // cdCanvasFlush(cd_canvas);


    redraw_plus();
    //redraw();
    cv_color = cv_colour2;
    cdCanvasSetForeground(cd_canvas, cv_color); //TODO : Clean that mess
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
    IupSetCallback(canvas, "RESIZE_CB", (Icallback)resize_cb);
    newvec(cv_color);
    IupSetCallback(canvas, "ACTION", (Icallback)action_redraw_cb);
    IupSetCallback(canvas, "UNMAP_CB", (Icallback)unmap_cb);
    IupSetCallback(canvas, "MOTION_CB", (Icallback)motion_cb);

    // Ne pas oublier le NULL final pour IupVbox
    Ihandle* vbox = IupVbox(canvas, NULL);

    return vbox;
}

