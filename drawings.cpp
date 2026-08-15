

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



//std::vector <Point> last_points;
typedef struct {
    std::vector <Point> points;
    int width;
    long int colour;

} Stroke;
std::vector <Stroke> last_strokes;


void newvec(long int colour, int width) { // If you want to push_back info for a STROKE
    Stroke s;
    s.points = std::vector <Point> ({});
    s.colour = colour;
    s.width = width;
    last_strokes.push_back(s);
    //last_points = std::vector <Point> ({});
}

/*void redraw() {

    for (int i = 0; i < last_points.size(); i++) {
        pointat(last_points[i].x, last_points[i].y, 0);
    }
}*/

void redraw_plus() { // a better redraw **MAGIC**
    for (int i = 0; i < last_strokes.size(); i++) {
        Point p;
        p.x = last_strokes[i].points[0].x;
        p.y = last_strokes[i].points[0].y;
        for (int j = 0; j < last_strokes[i].points.size(); j++) {
                change_colour_iup_canvas(last_strokes[i].colour);
            if ((p.x == last_strokes[i].points[j].x) && (p.y == last_strokes[i].points[j].y))  {

                pointat(last_strokes[i].points[j].x, last_strokes[i].points[j].y, last_strokes[i].colour, last_strokes[i].width);
            } else {
                pointat(last_strokes[i].points[j].x, last_strokes[i].points[j].y, last_strokes[i].colour, last_strokes[i].width);
                lineat(p.x, p.y, last_strokes[i].points[j].x, last_strokes[i].points[j].y, last_strokes[i].colour, last_strokes[i].width);
                p.x = last_strokes[i].points[j].x;
                p.y = last_strokes[i].points[j].y;
            }
        }
    }
}

void point_at(int x, int y, long int colour, int width) { // If you want push_back info point by point
    //printf("Mouse moved to (%d, %d)\n", x, y);
    Point point;
    //change_colour_iup_canvas();
    point.x = x;
    point.y = y;
    //last_points.push_back(point);
    last_strokes[last_strokes.size() - 1].points.push_back(point);  // just .size() segfaults but with a " - 1 " it runs like fine whime
    pointat(x, y, colour, width);
}

void line_at_remember_last_point(int x, int y, long int colour, int width) { // If you want push_back info line by line
    //printf("Mouse moved to (%d, %d)\n", x, y);
    Point point;
    //change_colour_iup_canvas();
    point.x = x;
    point.y = y;
    //last_points.push_back(point);
    last_strokes[last_strokes.size() - 1].points.push_back(point);  // just .size() segfaults but with a " - 1 " it runs like fine whime
    pointat(x, y, colour, width);
    lineat(last_strokes[last_strokes.size() - 1].points[last_strokes[last_strokes.size() - 1].points.size() - 2].x, last_strokes[last_strokes.size() - 1].points[last_strokes[last_strokes.size() - 1].points.size() - 2].y, x, y, colour, width); //TODO : Make this a litte more NULL/nullptr safe
}

Drawings::Drawings(int argc, char** argv) : Iup::Vbox(IupVbox(NULL))
{
    cvas = canvas_box_create();
    //clear_the_cvas();
    //point_at(10, 10, );
    set_width_stroke(10);
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

void Drawings::setColour(long int colour) {
    set_canvas_colour(colour);

}

void Drawings::setWidth(int width) {
    set_width_stroke(width);
}

void Drawings::clear() {
    last_strokes = std::vector <Stroke> ({});
    newvec(0, 2);
    clear_the_cvas();
}
