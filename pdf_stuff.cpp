#include "pdf_stuff.h"

#include <iostream>
#include <vector>
#include <stdexcept>

#include <mupdf/fitz.h>
#include <mupdf/pdf.h>



PdfStuff::PdfStuff()
{
    fz_context *ctx = nullptr;
    fz_document *doc = nullptr;
    fz_page *page = nullptr;
    fz_pixmap *pix = nullptr;

    // 1. Create a MuPDF context
    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!ctx) {
        std::cerr << "Failed to create context" << std::endl;
        //return 1;
    }

    // Register default document handlers (PDF, XPS, EPUB, etc.)
    fz_try(ctx) {
        fz_register_document_handlers(ctx);
    }
    fz_catch(ctx) {
        std::cerr << "Failed to register handlers" << std::endl;
        fz_drop_context(ctx);
        //return 1;
    }

    fz_try(ctx) {
        // 2. Open the PDF document
        doc = fz_open_document(ctx, "input.pdf");

        // 3. Load the desired page (0-indexed)
        int page_number = 1;
        page = fz_load_page(ctx, doc, page_number);


        fz_matrix transform = fz_scale(2.0, 2.0);

        fz_pixmap *pix = fz_new_pixmap_from_page_number(ctx, doc, page_number, transform, fz_device_rgb(ctx), 0);
        width = fz_pixmap_width(ctx, pix);
        height = fz_pixmap_height(ctx, pix);
        int n = fz_pixmap_components(ctx, pix);

        unsigned char *pixels = fz_pixmap_samples(ctx, pix);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * n;
                R.push_back(pixels[index]);
                G.push_back(pixels[index + 1]);
                B.push_back(pixels[index + 2]);


            }
        }
        fz_drop_pixmap(ctx, pix);
    } fz_always(ctx) {
        // 6. Clean up resources in reverse order
        if (pix) fz_drop_pixmap(ctx, pix);
        if (page) fz_drop_page(ctx, page);
        if (doc) fz_drop_document(ctx, doc);
        if (ctx) fz_drop_context(ctx);
    } fz_catch(ctx) {
        std::cerr << "Screw you" << std::endl;
    }
}

unsigned char* PdfStuff::getpixmapR() { //TODO: make all this a little more nullptr safe
    return R.data();
}

unsigned char* PdfStuff::getpixmapG() {
    return G.data();
}

unsigned char* PdfStuff::getpixmapB() {
    return B.data();
}

int PdfStuff::getheight() {
    return height;
}

int PdfStuff::getwidth() {
    return width;
}


// This is where all the pdf stuuf will be (muPDF btw)
