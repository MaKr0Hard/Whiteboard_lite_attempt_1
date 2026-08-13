#ifndef MY_CANVAS_BOX_H
#define MY_CANVAS_BOX_H

#include <iup_plus.h>
#include <cd.h>
#include <cdiup.h>

class MyCanvasBox : public Iup::Vbox
{
public:
    MyCanvasBox();
    virtual ~MyCanvasBox();

    // Initialisation globale (à appeler une fois au début du main)
    static bool InitializeEnvironment(int* argc, char*** argv);

private:
    Iup::Canvas m_canvas;

    // Callbacks C++ reliés à IUP
    static int OnRedraw(Ihandle* ih);
    static int OnUnmap(Ihandle* ih);

    // Méthodes internes de rendu et nettoyage
    int DrawCanvas();
    int CleanupCanvas();
};

#endif // MY_CANVAS_BOX_H
