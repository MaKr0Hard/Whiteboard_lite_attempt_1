

#ifndef DRAWINGS_H
#define DRAWINGS_H

#include <iup_plus.h>
#include <cstdlib>
/**
 * @todo write docs
 */
//void point_at(int x, int y);

class Drawings : public Iup::Vbox
{
public:
    /**
     * Default constructor
     */
    Drawings(int argc, char** argv);
    //int mkdraw(int argc, char** argv);

    /**
     * Destructor
     */
    ~Drawings();
    void setColour(int r, int g, int b);
    void setColour(char* rgb);
    void setblah(int balh);
    //void draw_plus();
    void setColour(long int colour);
    void setWidth(int width);
    void clear();
/*private :
    static int motion_cb(Ihandle* ih, int x, int y, char* status);*/
};

#endif // DRAWINGS_H
