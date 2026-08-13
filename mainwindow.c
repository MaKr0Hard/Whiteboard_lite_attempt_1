

#include "mainwindow.h"
#include <iup/iup.h>

#include <stdlib.h>
#include <unistd.h>

Ihandle *btn_new;
int cs1;//Just too lazy to write closed state
int *cs1_ptr;
int argc_this;
char** argv_this;



void btn_new_cb() {
    int *cs2 = (int*)IupGetAttribute(btn_new, "CS");
    *cs2 = 2;
    IupExitLoop();
}

void btn_close_cb() {
    int *cs2 = (int*)IupGetAttribute(btn_new, "CS");
    *cs2 = 1;
    IupExitLoop();
}

int newwindow (int argc, char** argv, int* closed_state) {
    cs1_ptr = &cs1;
    IupOpen(&argc, &argv);
    Ihandle *list_of_files, *fill;
    Ihandle  *btn_open, *btn_close;
    Ihandle *dlg, *label;
    Ihandle *main_hbox, *vbox;
    Ihandle* toolbar;
    list_of_files = IupList(NULL);
    IupSetAttribute(list_of_files, "EXPAND", "YES");
    btn_new = IupButton("Nouveau fichier", NULL);
    btn_close = IupButton("Fermer", NULL);
    //IupSetAttribute(btn_close, "EXPAND", "YES");
    label = IupLabel("Bienvenue !");
    IupSetAttribute(btn_new, "CS", (char*)cs1_ptr);
    IupSetAttribute(btn_close, "CS", (char*)cs1_ptr);
    IupSetCallback(btn_close, "ACTION", (Icallback)btn_close_cb);
    IupSetCallback(btn_new, "ACTION", (Icallback)btn_new_cb);
    fill = IupFill();
    vbox = IupVbox(label, btn_new, fill, btn_close, NULL);
    main_hbox = IupHbox(vbox, list_of_files, NULL);
    dlg = IupDialog(main_hbox);
    IupSetAttribute(dlg, "TITLE", "Bienvenue !");

    IupShow(dlg);
    IupMainLoop();
    IupClose();
    return cs1;
}

