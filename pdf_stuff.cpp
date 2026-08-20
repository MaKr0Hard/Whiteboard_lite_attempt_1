#include "pdf_stuff.h"

#include <iostream>
#include <vector>
#include <stdexcept>

#include <mupdf/fitz.h>
#include <mupdf/pdf.h>
#include <raylib.h>
#include <thread>


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
        int page_number = 0;
        page = fz_load_page(ctx, doc, page_number);


        fz_matrix transform = fz_scale(1.0, 1.0);

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

                /*R.push_back(254);
                G.push_back(0);
                B.push_back(0);*/

            }
        }
        printf("width : %d\n", width);
        printf("height : %d\n", height);
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

std::vector<unsigned char> PdfStuff::getpixmapRvectr() { //TODO: make all this a little more nullptr safe
    return R;
}

std::vector<unsigned char> PdfStuff::getpixmapGvectr() {
    return G;
}

std::vector<unsigned char> PdfStuff::getpixmapBvectr() {
    return B;
}

int PdfStuff::getheight() {
    printf("heightt : %d\n", height);
    return height;
}

int PdfStuff::getwidth() {
    return width;
}

void PdfStuff::raylib_test() {
    raylib_stuff();

}

void PdfStuff::raylib_stuff() {
std::vector <unsigned char> pixels;
for (int i = 0; i < height * width; i++) {
    pixels.push_back(R[1]);
    pixels.push_back(G[1]);
    pixels.push_back(B[1]);
}

    Image img = {
        .data = pixels.data(),
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };

    Texture2D texture = LoadTextureFromImage(img);
    InitWindow(400, 600, "Test");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(texture, 50, 50, WHITE);
        EndDrawing();
    }
    UnloadTexture(texture);

    CloseWindow();
}



// This is where all the pdf stuuf will be (muPDF btw)
