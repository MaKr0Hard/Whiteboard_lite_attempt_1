

#ifndef DRAWINGS_H
#define DRAWINGS_H

#include <iup_plus.h>
#include <cstdlib>
/**
 * @todo write docs
 */
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

};

#endif // DRAWINGS_H
