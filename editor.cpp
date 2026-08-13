
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

Ihandle* create_a_colr_from_image(int w, int h, unsigned char r, unsigned char g, unsigned char b){
    std::vector <unsigned char> pixx(w * h * 3);
    //unsigned char pix[w * h * 3]; //all the pixels
    /*for (int i = 0; i < (w * h); i++) {
        pix[i * 3] = r;
        pix[i * 3 + 1] = g;
        pix[i * 3 + 2] = b;

    }*/ //TODO : find a c way to get this working cuz std::vector is heavvy

    for (size_t i = 0; i < pixx.size(); i += 3) {
        pixx[i]     = r;
        pixx[i + 1] = g;
        pixx[i + 2] = b;
    }
    return IupImageRGB(w, h, pixx.data());
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
//I don't think I'll ever nee this, I'll come up with my own stuff

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



typedef struct {
    Ihandle* btn;
    Colour col;
} Col_btn;

Col_btn colbtn (Ihandle *btn, int r, int g, int b) {
    Col_btn cbtn;
    cbtn.btn = btn;
    cbtn.col.R = r;
    cbtn.col.G = g;
    cbtn.col.B = b;
    return cbtn;
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
    std::vector <Col_btn> all_colour_btns;
#define ACB all_colour_btns.btn

    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 255, 0, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 255, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 0, 255));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 0, 0));
    //all_colour_btns.push_back(IupButton("Orange", NULL));
    /*all_colour_btns.push_back(IupButton("Jaune", NULL));
    all_colour_btns.push_back(IupButton("Violet", NULL));
    all_colour_btns.push_back(IupButton("Blanc", NULL));
    all_colour_btns.push_back(IupButton("Bleu clair", NULL));
    all_colour_btns.push_back(IupButton("Gris", NULL));*/
    //char colr[25] = "255 0 0";

    //IupSetAttribute(all_colour_btns[0].btn, "COLOURCODE", "255 0 0");



    for (int i = 0; i < all_colour_btns.size(); i++) {
        Ihandle* colrr = create_a_colr_from_image(24, 24, all_colour_btns[i].col.R, all_colour_btns[i].col.G, all_colour_btns[i].col.B);
        IupSetAttributeHandle(all_colour_btns[i].btn, "IMAGE", colrr);
        colours->Append(all_colour_btns[i].btn);
    }
    IupSetCallback(all_colour_btns[0].btn, "ACTION", (Icallback)colr_cb);



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

