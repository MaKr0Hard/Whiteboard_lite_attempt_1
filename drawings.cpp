

#include "drawings.h"
#include <iup/iup_plus.h>
#include <cd.h>
#include <iup.h>
#include <cstdlib>
#include <iup.h>
#include <iupcontrols.h>
#include <cd.h>

extern "C" {
#include "drawings_utils.h"
}


Ihandle* cvas;
//cdCanvas *cdcan;
//Ihandle* iupcan;

Drawings::Drawings(int argc, char** argv) : Iup::Vbox(IupVbox(NULL))
{
    cvas = canvas_box_create();
    this->Append(cvas);

}

Drawings::~Drawings()
{
    //delete cdcan;
}

void Drawings::setColour(int r, int g, int b) {

}

void Drawings::setColour(char* rgb){

}

/*void Drawings::draw_plus() {
    action_redraw_cb_plus();
}*/
