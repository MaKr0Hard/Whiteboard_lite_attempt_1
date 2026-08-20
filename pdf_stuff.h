#ifndef PDF_STUFF_H
#define PDF_STUFF_H

#include <iostream>
#include <vector>
#include <stdexcept>

#include <mupdf/fitz.h>
#include <mupdf/pdf.h>


class PdfStuff {

public :
    PdfStuff();
    ~PdfStuff();
    unsigned char* getpixmapR();
    unsigned char* getpixmapG();
    unsigned char* getpixmapB();
    int getheight();
    int getwidth();

private:
    int width = 0;
    int height = 0;
    std::vector<unsigned char> R;
    std::vector<unsigned char> G;
    std::vector<unsigned char> B;
};

#endif
