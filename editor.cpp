
#include <stdlib.h>
#include "editor.h"
//#include <iup/iup_plus.h>
#include "drawings.h"
#include "MyCanvasBox.h"
extern "C" {
#include "drawings_utils.h"
}
Editor::Editor()
{

}

Editor::~Editor()
{

}

void quit_cb() {
    exit(0);
}

void detached_cb() {

}

int Editor::neweditor(int argc, char** argv)
{
#if defined(__linux__) || defined(__unix__)
    setenv("GDK_BACKEND", "x11", 1);
#endif

    IupOpen(&argc, &argv);
    Ihandle *dlg, *main_vbox, *menu_bar;
    Ihandle *file_menu, *item_quit;
    Ihandle *subm1;
    Ihandle* btn;
    Ihandle *db_hb;

    Drawings *d = new Drawings(argc, argv);
    btn = IupButton(NULL, NULL);

    Ihandle* box = my_canvas_box_create();

    IupSetAttribute(btn, "BGCOLOR", "255 0 0");
    item_quit = IupItem("Quitter", NULL);
    IupSetCallback(item_quit, "ACTION", (Icallback)quit_cb);
    file_menu = IupMenu(item_quit, NULL);
    subm1 = IupSubmenu("Fichier", file_menu);
    menu_bar = IupMenu(subm1, NULL);
    main_vbox = IupVbox(btn, d->GetHandle(), box, NULL); //TODO :fix that ugly segfault when appending
    dlg = IupDialog(main_vbox);
    IupSetAttributeHandle(dlg, "MENU", menu_bar);
    IupShow(dlg);
    IupMainLoop();
    IupClose();
    return EXIT_SUCCESS;
}

