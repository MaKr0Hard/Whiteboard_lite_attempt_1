

#include "drawings.h"
#include <iup/iup_plus.h>
#include <cd.h>
#include <iup.h>
#include <cstdlib>
#include <iup.h>
#include <iupcontrols.h>
#include <cd.h>
#include <cstdio>
#include <vector>
extern "C" {
#include "drawings_utils.h"
#include "drawings_c.h"
}



Ihandle* cvas;
//cdCanvas *cdcan;
//Ihandle* iupcan;



std::vector <Point> last_points;
typedef struct {
    std::vector <Point> points;
    int width;
    unsigned char r;
    unsigned char g;
    unsigned char b;

} Stroke;
std::vector <Stroke> last_strokes;

void redraw() {
    for (int i = 0; i < last_points.size(); i++) {
        pointat(last_points[i].x, last_points[i].y);
    }
}

void point_at(int x, int y) {
    //printf("Mouse moved to (%d, %d)\n", x, y);
    Point point;
    point.x = x;
    point.y = y;
    last_points.push_back(point);
    pointat(x, y);
}

Drawings::Drawings(int argc, char** argv) : Iup::Vbox(IupVbox(NULL))
{
    cvas = canvas_box_create();
    //point_at(10, 10, );
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

void Drawings::draw_plus(long int colour) {
    change_colour_iup_canvas(colour);
    update_canvas();
}
