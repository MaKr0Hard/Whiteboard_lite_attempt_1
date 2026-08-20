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
    void raylib_test();
    std::vector<unsigned char> getpixmapRvectr();
    std::vector<unsigned char> getpixmapGvectr();
    std::vector<unsigned char> getpixmapBvectr();
    std::vector<unsigned char> R;
    std::vector<unsigned char> G;
    std::vector<unsigned char> B;
    int width = 0;
    int height = 0;
private:


    void raylib_stuff();
};

#endif
