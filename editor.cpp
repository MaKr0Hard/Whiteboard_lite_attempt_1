
#include <stdlib.h>
#include "editor.h"
//#include <iup/iup_plus.h>
#include "drawings.h"
//#include "MyCanvasBox.h"
extern "C" {
#include "drawings_utils.h"
}
#include <cdiup.h>
#include <vector>
#include <string.h>
#include <cstdio>

Drawings *d;

Ihandle* create_a_colr_from_image(int w, int h, int r, int g, int b){
    std::vector <unsigned char> pixx;
    unsigned char pix[w * h * 3]; //all the pixels
    for (int i = 0; i < (w * h); i++) {
        pix[i * 3] = r;
        pix[i * 3 + 1] = g;
        pix[i * 3 + 2] = b;

    }
    return IupImage(w, h, pix);
}

Ihandle* create_a_colr_from_image_from_string(int w, int h, char* col) {
    Ihandle* handle;
    int r;
    int g;
    int b;
    int i = 0; //spaces
    int j = 0; //letters
    int k = 0; //letters in current word
    char character;
    char string[10] = "       ";
    while (i < 3) {
        character = col[j];
        if (character == ' ') {
            switch (i) {
                default:
                puts("WTF\n");
                break;
                case 0:
                r = atoi(string);
                break;
                case 1:
                g = atoi(string);
                break;
                case 2:
                b = atoi(string);
                break;

            }

            strcpy(string, "       ");
            k = 0;
            i++;
        } else {
            string[j] = character;
        }
        j++;
        k++;

    }
    handle = create_a_colr_from_image(w, h, r, g, b);
    return handle;
} //TODO : Fix

static int colr_cb(Ihandle *ih) {
    //exit(0);
    char* col_code = (char*)malloc(strlen(IupGetAttribute(ih, "COLOURCODE")) + 1);
    strcpy(col_code, IupGetAttribute(ih, "COLOURCODE"));

    return IUP_DEFAULT;
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




int Editor::neweditor(int argc, char** argv)
{

    IupOpen(&argc, &argv);
    //cdInitContextPlus();
    Ihandle *dlg, *main_vbox, *menu_bar;
    Ihandle *file_menu, *item_quit;
    Ihandle *subm1;
    Ihandle* btn;
    Ihandle *db_hb;
    Iup::Hbox *colours = new Iup::Hbox;
    std::vector <Ihandle *> all_colour_btns;
#define ACB all_colour_btns


    all_colour_btns.push_back(IupButton("Rouge", NULL));
    all_colour_btns.push_back(IupButton("Vert", NULL));
    all_colour_btns.push_back(IupButton("Bleu", NULL));
    all_colour_btns.push_back(IupButton("Noir", NULL));
    all_colour_btns.push_back(IupButton("Orange", NULL));
    all_colour_btns.push_back(IupButton("Jaune", NULL));
    all_colour_btns.push_back(IupButton("Violet", NULL));
    all_colour_btns.push_back(IupButton("Blanc", NULL));
    all_colour_btns.push_back(IupButton("Bleu clair", NULL));
    all_colour_btns.push_back(IupButton("Gris", NULL));
    //char colr[25] = "255 0 0";
    Ihandle* colrr = create_a_colr_from_image(48, 48, 254, 254, 0);
    IupSetAttribute(ACB[0], "COLOURCODE", "255 0 0");
    IupSetAttributeHandle(ACB[0], "IMAGE", colrr);
    IupSetAttribute(ACB[1], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[2], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[3], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[4], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[5], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[6], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[7], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[8], "COLOURCODE", "255 0 0");
    IupSetAttribute(ACB[9], "COLOURCODE", "255 0 0");

    for (int i = 0; i < all_colour_btns.size(); i++) {
        colours->Append(all_colour_btns[i]);
    }
    IupSetCallback(all_colour_btns[0], "ACTION", (Icallback)colr_cb);



    d = new Drawings(argc, argv);

    item_quit = IupItem("Quitter", NULL);

    IupSetCallback(item_quit, "ACTION", (Icallback)quit_cb);
    file_menu = IupMenu(item_quit, NULL);
    subm1 = IupSubmenu("Fichier", file_menu);
    menu_bar = IupMenu(subm1, NULL);

    main_vbox = IupVbox(colours->GetHandle(), d->GetHandle(),  NULL); //DONE

    dlg = IupDialog(main_vbox);
    IupSetAttributeHandle(dlg, "MENU", menu_bar);
    IupShow(dlg);
    IupMainLoop();
    IupClose();
    return EXIT_SUCCESS;
}

