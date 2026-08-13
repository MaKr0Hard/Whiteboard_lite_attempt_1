

#include "drawings.h"
#include <iup/iup_plus.h>
#include <cd.h>
#include <cdiup.h>
#include <iup.h>
#include <cstdlib>
#include <iup.h>
#include <iupcontrols.h>
#include <cd.h>
#include <cdiup.h>
extern "C" {
#include "drawings_utils.h"
}


//cdCanvas *cdcan;
//Ihandle* iupcan;

void redraw() {

}



Drawings::Drawings(int argc, char** argv) : Iup::Vbox(IupVbox(NULL))
{

    #if defined(__linux__) || defined(__unix__)
    setenv("GDK_BACKEND", "x11", 1);
    #endif
    //my_canvas_box_init_env(&argc, &argv);
    //Ihandle* some_box = my_canvas_box_create();
    //Ihandle *dbox;
    //dbox = mkdraw();
    //this->SetAttribute("SIZE", "200x100");
    //iupcan = IupCanvas(NULL);
    //IupSetAttribute(iupcan, "SIZE", "200x200");
    //cdcan = cdCreateCanvas(CD_IUP, iupcan);
    //cdCanvasForeground(cdcan, CD_BLUE);
    //cdCanvasClear(cdcan);
    //cdCanvasLineStyle(cdcan, CD_DASHED);
    //cdCanvasLine(cdcan, 1, 1, 10, 10);
    Ihandle *btn;
    btn = IupButton("What ?", NULL);
    //Ihandle* cvas = mkdraw();
    this->Append(btn);
    /*if (some_box != NULL) {
    this->Append(some_box);
    }*/
    //this->Append(iupcan);
    //this->Append(cvas);
    //this->Map();
}

Drawings::~Drawings()
{
    //delete cdcan;
}

