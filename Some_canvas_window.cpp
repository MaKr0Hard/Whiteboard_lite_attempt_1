#include "MyCanvasBox.h"
#include <cstdlib>
#include <iostream>

bool MyCanvasBox::InitializeEnvironment(int* argc, char*** argv)
{
    // Force le backend X11 sous Linux avant toute initialisation GTK/IUP
    #if defined(__linux__) || defined(__unix__)
    setenv("GDK_BACKEND", "x11", 1);
    #endif

    if (IupOpen(argc, argv) == IUP_ERROR)
    {
        std::cerr << "Erreur : Impossible d'initialiser IUP." << std::endl;
        return false;
    }
    return true;
}

MyCanvasBox::MyCanvasBox() : Iup::Vbox(IupVbox(NULL))
{
    // Configuration du canevas
    m_canvas.SetAttribute("RASTERSIZE", "300x200");
    m_canvas.SetAttribute("EXPAND", "YES");

    // Définition des callbacks
    m_canvas.SetCallback("ACTION", (Icallback)OnRedraw);
    m_canvas.SetCallback("UNMAP_CB", (Icallback)OnUnmap);

    // Association du pointeur C++ à l'élément canvas
    m_canvas.SetAttribute("_CPP_INSTANCE", (char*)this);

    // Ajout du canevas à la Vbox (hérité de IUP::Vbox)
    this->Append(m_canvas);
}

MyCanvasBox::~MyCanvasBox()
{
}

int MyCanvasBox::OnRedraw(Ihandle* ih)
{
    MyCanvasBox* instance = (MyCanvasBox*)IupGetAttribute(ih, "_CPP_INSTANCE");
    if (instance)
    {
        return instance->DrawCanvas();
    }
    return IUP_DEFAULT;
}

int MyCanvasBox::OnUnmap(Ihandle* ih)
{
    MyCanvasBox* instance = (MyCanvasBox*)IupGetAttribute(ih, "_CPP_INSTANCE");
    if (instance)
    {
        return instance->CleanupCanvas();
    }
    return IUP_DEFAULT;
}

int MyCanvasBox::DrawCanvas()
{
    Ihandle* ih_canvas = m_canvas.GetHandle();
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(ih_canvas, "_CD_CANVAS");

    // Création paresseuse lors du premier affichage
    if (!cd_canvas)
    {
        cd_canvas = cdCreateCanvas(CD_IUP, ih_canvas);
        if (!cd_canvas)
        {
            std::cerr << "Erreur : Échec de la création du canvas CD." << std::endl;
            return IUP_DEFAULT;
        }
        IupSetAttribute(ih_canvas, "_CD_CANVAS", (char*)cd_canvas);
    }

    // Rendu CD
    cdCanvasActivate(cd_canvas);
    cdCanvasClear(cd_canvas);

    cdCanvasForeground(cd_canvas, CD_BLUE);
    cdCanvasLine(cd_canvas, 10, 10, 150, 150);

    cdCanvasForeground(cd_canvas, CD_RED);
    cdCanvasRect(cd_canvas, 50, 50, 120, 120);

    cdCanvasForeground(cd_canvas, CD_GREEN);
    cdCanvasSector(cd_canvas, 200, 100, 60, 60, 0, 360);

    cdCanvasForeground(cd_canvas, CD_BLACK);
    cdCanvasText(cd_canvas, 10, 180, "Dessin dans IupVbox");

    return IUP_DEFAULT;
}

int MyCanvasBox::CleanupCanvas()
{
    Ihandle* ih_canvas = m_canvas.GetHandle();
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(ih_canvas, "_CD_CANVAS");

    if (cd_canvas)
    {
        cdKillCanvas(cd_canvas);
        IupSetAttribute(ih_canvas, "_CD_CANVAS", NULL);
    }
    return IUP_DEFAULT;
}
