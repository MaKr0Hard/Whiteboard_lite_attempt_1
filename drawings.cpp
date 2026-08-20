

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
#include <thread>
extern "C" {
#include "drawings_utils.h"
#include "drawings_c.h"
}
#include "pdf_stuff.h"


Ihandle* cvas;
//cdCanvas *cdcan;
//Ihandle* iupcan;
double blah = 1.0;

typedef struct { //TODO: Put thos into classes to be able to create more than one draw_widget
    std::vector <unsigned char> r;
    std::vector <unsigned char> g;
    std::vector <unsigned char> b;
    int width;
    int height;
} Background;

//std::vector <Point> last_points;
typedef struct {
    std::vector <Point> points;
    int width;
    long int colour;

} Stroke;
std::vector <Stroke> last_strokes;


typedef struct {
    std::vector <Stroke> last_strokes;
    Background background;
} Page;
Page page;

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

void redraw_strokes() { // a better redraw **MAGIC**
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

void redraw_bg() {
    /*for (int y = 0; y < page.background.height; ++y){
        for (int x = 0; x < page.background.width; x++) {
            if (((y * page.background.height + x) <= page.background.r.size())
                &&
                ((y * page.background.height + x) <= page.background.g.size())
                &&
                ((y * page.background.height + x) <= page.background.b.size())
            ) {
                //pixelat(x, y, page.background.r[y * page.background.height + x], page.background.g[y * page.background.height + x], page.background.b[y * page.background.height + x]);3
                pointat(x, y, cdEncodeColor(page.background.r[y * page.background.height + x], page.background.g[y * page.background.height + x], page.background.b[y * page.background.height + x]), 2);
            }
        }
    }*/
    putImage(page.background.width / blah , page.background.height, page.background.r.data(), page.background.g.data(), page.background.b.data(), 0, page.background.height, page.background.width, page.background.height, 0, 0, 0, 0);
}

void redraw_plus() {
    redraw_bg();
    redraw_strokes();
}

void redraw_plus_on_a_new_thread(){
    std::thread(redraw_plus);
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
    PdfStuff *s = new PdfStuff();
    cvas = canvas_box_create();
    //clear_the_cvas();
    //point_at(10, 10, );
    set_width_stroke(10);

    //update_canvas();
    //s->raylib_test();
    this->Append(cvas);
    //putImage(s->getwidth(), s->getheight(), s->getpixmapR(), s->getpixmapG(), s->getpixmapB(), 100, 100, 0, 0, 0, 0, 0, 0);
    std::vector<unsigned char> r = s->getpixmapRvectr();
    std::vector<unsigned char> g = s->getpixmapGvectr();
    std::vector<unsigned char> b = s->getpixmapBvectr();
    int pdf_height = s->getheight();
    int pdf_width = s->getwidth();
    page.background.width = pdf_width;
    page.background.height = pdf_height;

    for (int y = 0; y < pdf_height; ++y) {
        for (int x = 0; x < pdf_width; x++) {

            //pointat(x, y, cdEncodeColor(r[y * 297 + x], g[y * 297 + x], b[y * 297 + x]), 2);
            page.background.r.push_back(r[y * pdf_height +x]);
            page.background.g.push_back(g[y * pdf_height +x]);
            page.background.b.push_back(b[y * pdf_height +x]);

        }
    }


    update_canvas();
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

void Drawings::setblah(int balh) {
    blah = balh / 100;
    redraw_plus();
}
