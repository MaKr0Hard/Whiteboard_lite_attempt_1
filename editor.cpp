
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

Ihandle* create_a_colr_from_image_from_string(int w, int h, char* col) { // This shit now useless when delete ?
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

static int slider_moved_cb(Ihandle *ih) {

    char width_char[30];
    strcpy(width_char, IupGetAttribute(ih, "VALUE"));
    int width = atoi(width_char);
    Ihandle* textview = IupGetAttributeHandle(ih, "TEXTVIEW");
    char title[20];
    if (textview != NULL) {
    sprintf(title, "%d", width);
    IupSetAttribute(textview, "TITLE", title);
    }
    //printf("%d\n", width);
    d->setWidth(width);
    return IUP_DEFAULT;
}

static int colr_cb(Ihandle *ih) {
    //exit(0);
    //char* col_code = (char*)malloc(strlen(IupGetAttribute(ih, "COLOURCODE")) + 1);
    //strcpy(col_code, IupGetAttribute(ih, "COLOURCODE")); //ABSOLUT KRAP
    Colour *col = (Colour*)IupGetAttribute(ih, "COLOURCODE");
    if (col != NULL) {
        Colour col_no_ptr = *col;
        unsigned char r = col_no_ptr.R;
        unsigned char g = col_no_ptr.G;
        unsigned char b = col_no_ptr.B;
        //IupMessage("Tiens, tiens...", "Le dévelopeur a fait une boulette");
        d->setColour(cdEncodeColor(r, g, b));
    } else {
        IupMessage("Tiens, tiens...", "Le dévelopeur a fait une boulette");
        return IUP_DEFAULT;
    }
    return IUP_DEFAULT;
}

static int clear_cb(Ihandle *ih) {
    d->clear();
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
    Ihandle *edit_menu, *item_clear;
    Ihandle *subm1, *subm2;
    Ihandle* btn;
    Ihandle *db_hb;
    Ihandle *slider, *textview_sli;
    Ihandle *toolbar;
    Ihandle *widthselector;
    Iup::Hbox *colours = new Iup::Hbox;
    std::vector <Col_btn> all_colour_btns;
#define ACB all_colour_btns.btn

    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 255, 0, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 255, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 0, 255));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 0, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 255, 125, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 255, 255, 0));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 110, 0, 185));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 255, 255, 255));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 0, 255, 255));
    all_colour_btns.push_back(colbtn(IupButton(NULL, NULL), 127, 127, 127));
    //char colr[25] = "255 0 0";





    for (int i = 0; i < all_colour_btns.size(); i++) {
        Ihandle* colrr = create_a_colr_from_image(24, 24, all_colour_btns[i].col.R, all_colour_btns[i].col.G, all_colour_btns[i].col.B);
        IupSetAttributeHandle(all_colour_btns[i].btn, "IMAGE", colrr);
        IupSetAttribute(all_colour_btns[i].btn, "COLOURCODE", (char*)&all_colour_btns[i].col);
        IupSetCallback(all_colour_btns[i].btn, "ACTION", (Icallback)colr_cb);
        colours->Append(all_colour_btns[i].btn);
    }
    slider = IupVal(IUP_HORIZONTAL);
    textview_sli = IupLabel(NULL);     // Stands for textview slider
    IupSetAttribute(slider, "MIN", "1");
    IupSetAttribute(slider, "MAX", "100");
    IupSetAttribute(slider, "SIZE", "150x1");
    IupSetCallback(slider, "VALUECHANGED_CB", (Icallback)slider_moved_cb);
    IupSetAttributeHandle(slider, "TEXTVIEW", textview_sli);
    //TODO : Add a drop btn to choose precision or type number out yourself

    widthselector = IupHbox(slider, textview_sli, NULL);
    toolbar = IupHbox(colours->GetHandle(), widthselector, NULL);
    d = new Drawings(argc, argv);


    item_quit = IupItem("Quitter", NULL);
    IupSetCallback(item_quit, "ACTION", (Icallback)quit_cb);
    file_menu = IupMenu(item_quit, NULL);
    subm1 = IupSubmenu("Fichier", file_menu);

    item_clear = IupItem("Effacer tout", NULL);
    IupSetCallback(item_clear, "ACTION", (Icallback)clear_cb);
    edit_menu = IupMenu(item_clear, NULL);
    subm2 = IupSubmenu("Éditer", edit_menu);

    menu_bar = IupMenu(subm1, subm2, NULL);

    main_vbox = IupVbox(toolbar, d->GetHandle(),  NULL); //DONE

    dlg = IupDialog(main_vbox);
    IupSetAttributeHandle(dlg, "MENU", menu_bar);
    IupShow(dlg);
    IupMainLoop();
    IupClose();
    return EXIT_SUCCESS;
}

